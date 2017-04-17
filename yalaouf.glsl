#define M_PI 3.1415926535897932384626433832795
#define EPSI 0.001f
#define AMBIENT 0.2

struct		Ray
{
	vec3	dir;
	vec3	pos;
};

struct Material
{
	vec4	texture;
	vec4	emission; //"a voir plus tard"
	vec4	transparency;
	vec4	reflection;
	vec4	refraction;
	vec4	bumpmap;
	vec4	specular;
};

struct		Hit
{
	float	dist;
	vec3	norm;
	vec3	pos;
	Material mat;
};

struct	Coupe
{
	float	dist;
	vec3	rot;
};

void plane (vec3 norm, vec3 pos, float data, Material mat, Ray r, inout Hit h) {
	norm = normalize(norm);
	float t = (dot(norm,pos) - (dot (norm, r.pos))) / dot (norm, r.dir);
	Hit tmp = h;
	vec3 plus = pos + data/2;
	vec3 moin = pos - data/2;

	if (t < EPSI)
		return;

	if (t < h.dist) {
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.norm = faceforward(norm, norm, r.dir);
    h.mat = mat;
  }
	if (data == 0)
		return;
	else if(h.pos.x > plus.x || h.pos.x < moin.x || h.pos.y > plus.y || h.pos.y < moin.y || h.pos.z > plus.z || h.pos.z < moin.z)
		h = tmp;
}

/* Découpe de sphère */
void decoupe(vec3 centre, vec3 inter, Coupe c, Coupe c2, Material m, Ray r, inout Hit h, inout bool bo)
{
	c2.rot = normalize(c2.rot);
	c.rot = normalize(c.rot);
	vec3 pos = centre + c.rot * c.dist;
	vec3 pos2 = centre + c2.rot * c2.dist;

	float d = (c.rot.x * pos.x + c.rot.y * pos.y + c.rot.z * pos.z) * -1;
	float d2 = (c2.rot.x * pos2.x + c2.rot.y * pos2.y + c2.rot.z * pos2.z) * -1;
	bo = false;

	if (c2.rot.x * inter.x + c2.rot.y * inter.y + c2.rot.z * inter.z + d2 > 0){
		plane(c2.rot, pos2, 0, m, r, h);
		bo = true;
	}
	if (c.rot.x * inter.x + c.rot.y * inter.y + c.rot.z * inter.z + d >= 0){
		plane(c.rot, pos, 0, m, r, h);
		bo = true;
	}
	return;
}

void sphere (vec3 pos, float data, Material mat, Ray r, inout Hit h) {
	vec3 d = r.pos - pos;

	Coupe co;
	co.rot = vec3(0,0,-1);
	co.dist = 4;

	Coupe co2;
	co2.rot = vec3(0,1,0);
	co2.dist = 1;

	float a = dot (r.dir, r.dir);
	float b = dot (r.dir, d);
	float c = dot (d, d) - data * data;

	float g = b*b - a*c;

	if (g < EPSI)
		return;

	float t = (-sqrt (g) - b) / a;
	vec3 inter = r.pos + r.dir * t;
	bool bo;
	decoupe(pos, inter, co, co2, mat, r, h, bo);

	if (t < 0 || bo)
		return;

	if (t < h.dist) {
		h.dist = t + EPSI;
		h.pos = r.pos + r.dir * h.dist;
		h.norm = (h.pos - pos);
		h.mat = mat;
	}
	return;
}

void cyl (vec3 v, vec3 dir, float data, Material mat, Ray r, inout Hit h) {
	vec3 d = r.pos - v;

	dir = normalize(dir);
	float a = dot(r.dir,r.dir) - pow(dot(r.dir, dir), 2);
	float b = 2 * (dot(r.dir, d) - dot(r.dir, dir) * dot(d, dir));
	float c = dot(d, d) - pow(dot(d, dir), 2) - data * data;
	float g = b*b - 4*a*c;

	if (g < 0)
		return;

	float t1 = (-sqrt(g) - b) / (2*a);
	//float t2 = (sqrt(g) - b) / (2*a);

	if (t1 < 0)
		return ;

	if (t1 < h.dist){
		h.dist = t1 - EPSI;
		h.pos = r.pos + r.dir * h.dist;
		vec3 temp = dir * (dot(r.dir, dir) * h.dist + dot(r.pos - v, dir));
		vec3 tmp = h.pos - v;
		h.norm = tmp - temp;
		h.mat = mat;
	}
	/*else if (t2 >= 0 && t2 < h.dist){
	  h.dist = t2;
	  h.pos = r.pos + r.dir * t2;
	  vec3 temp = rot * (dot(r.dir, rot) * h.dist + dot(r.pos - v, rot));
	  vec3 tmp = h.pos - v;
	  h.color = color;
	  h.norm = temp - tmp;
	  }*/
}

Hit		scene(Ray r)
{
	int i = -1;
	Hit		hit;
	hit.dist = 1e20;
	hit.mat.texture = vec4(0,0,0,0);
  sphere(vec3(6, 14, -1), 5, Material(vec4(1,0,0,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,1,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,0,0,0)), r, hit );

	cyl(vec3(0, 0, 0), vec3(0,0,1), 0.2, Material(vec4(0,0,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(1,1,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,0,0,0)), r, hit );
	cyl(vec3(0, 0, 0), vec3(1,0,0), 0.2, Material(vec4(1,0,0,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(1,1,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,0,0,0)), r, hit );
	cyl(vec3(0, 0, 0), vec3(0,1,0), 0.2, Material(vec4(0,1,0,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(1,1,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,0,0,0)), r, hit );

  return hit;
}

float		limit(float value, float min, float max)
{
	return (value < min ? min : (value > max ? max : value));
}

bool			shadows(vec3 pos, vec3 d, Hit h)
{
	Ray		shadow;
	Hit		shad;

	shadow.dir = d;
	shadow.pos = pos + h.norm * EPSI;
	shad = scene(shadow);
	if (shad.dist < h.dist)
		return (true);
	return (false);
}

/* Définition de l'effet de la lumière sur les objets présents */
vec3		light(vec3 pos, Ray r, Hit h)
{
	vec3 v1 = pos - h.pos;
	vec3 v3 = v1 * v1;
	vec3 d = normalize(v1);
	vec3 color;

  color = vec3(AMBIENT * vec3(h.mat.texture.xyz));
	h.dist = sqrt(v3.x + v3.y + v3.z);
	if (h.dist > 1e20)
		return (color);
	if (shadows(h.pos, d, h))
		return (color);
	color += (limit(dot(h.norm, d), 0.0, 1.0)) * vec3(h.mat.texture.xyz);
  return (color);
}

/* Définition de la light */
vec3		calc_light(vec3 pos, Ray ref, Hit h)
{
	Hit	h2 = h;
	vec3 lambert;
	vec3 reflect = vec3(0,0,0);
	vec3 ambient = vec3(h.mat.texture.xyz) * AMBIENT;
	int		i = 0;
	float on_off = 1;
	lambert = light(pos, ref, h);
	/*while (++i < 5)
	{
	h = h2;
	ref.dir = h.norm;
	ref.pos = h.pos;
	h2 = scene(ref);
	on_off = on_off * h.mat.reflection.x;
	reflect += light(pos, ref, h2) * on_off;
	}*/
	return (lambert + reflect);
}


/* Création d'un rayon */
vec3	raytrace(vec3 ro, vec3 rd)
{
	Ray			r;
	Hit			h;
	vec3		pos_lum = vec3(15,15,-25);
	vec3		color = vec3(0,0,0);

  r.dir = rd;
	r.pos = ro;
	h = scene(r);
	color = calc_light(pos_lum, r, h);
  return (color / 2);
}

void		mainImage(vec2 coord)
{
	vec2	uv = (coord / iResolution) * 2 - 1;
	vec3	cameraPos = iMoveAmount.xyz + vec3(0, 0, -10);
	vec3	cameraDir = vec3(0,0,0);
	vec3	col;

	uv.x *= iResolution.x / iResolution.y;
	float	fov = 1.5;
	vec3	forw = normalize(iForward);
	vec3	right = normalize(cross(forw, vec3(0, 1, 0)));
	vec3	up = normalize(cross(right, forw));
	vec3	rd = normalize(uv.x * right + uv.y * up + fov * forw);
	fragColor = vec4(raytrace(cameraPos, rd), 1);
}
