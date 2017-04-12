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

void sphere (vec3 pos, float data, Material mat, Ray r, inout Hit h) {
	vec3 d = r.pos - pos;

	float a = dot (r.dir, r.dir);
	float b = dot (r.dir, d);
	float c = dot (d, d) - data * data;

	float g = b*b - a*c;

	if (g < EPSI)
		return;

	float t = (-sqrt (g) - b) / a;

	if (t < 0)
		return;

	if (t < h.dist) {
		h.dist = t + EPSI;
		h.pos = r.pos + r.dir * h.dist;
		h.norm = (h.pos - pos);
		h.mat = mat;
	}
	return;
}

void  torus2(vec3 pos, vec2 data, Material mat, Ray ray,inout Hit hit)
{
  float a = data.x;
  float b = data.y;

}

void  torus(vec3 pos, vec2 data, Material mat, Ray ray,inout Hit hit)
{
  float RCarre = data.x * data.x;
	float rCarre = data.y * data.y;

	float m = dot(ray.pos,ray.pos);
	float n = dot(ray.pos,ray.dir);

	float k = (m - rCarre - RCarre)/2.0;
	float a = n;
	float b = n * n + RCarre * ray.dir.z * ray.dir.z + k;
	float c = k * n + RCarre * ray.pos.z * ray.dir.z;
	float d = k * k + RCarre * ray.pos.z * ray.pos.z - RCarre * rCarre;

	float p = -3.0 * a * a     + 2.0 * b;
	float q = 2.0 * a * a * a   - 2.0 * a * b   + 2.0 * c;
	float r = -3.0 * a * a * a * a + 4.0 * a * a * b - 8.0 * a * c + 4.0 * d;
	p /= 3.0;
	r /= 3.0;
	float Q = p * p + r;
	float R = 3.0 * r * p - p * p * p - q * q;

	float h = R * R - Q * Q * Q;
	float z = 0.0;
	if(h < 0.0)
	{
		float sQ = sqrt(Q);
		z = p - 2.0 * sQ * cos(acos(R / (sQ * Q)) / 3.0);
	}
	else
	{
		float sQ = pow(sqrt(h) + abs(R), 1.0 / 3.0);
		z = p - sign(R) * abs(sQ + Q / sQ);

	}
	float d1 = z - 3.0 * p;
	float d2 = z * z - 3.0 * r;

	if(abs(d1) < EPSI)
	{
		if(d2 < 0.0)
      return;
		d2 = sqrt(d2);
	}
	else
	{
		if(d1 < 0.0)
      return;
		d1 = sqrt(d1/2.0);
		d2 = q/d1;
	}

  float result = 0.0;

	h = d1 * d1 - z + d2;
	if (h > EPSI)
	{
		h = sqrt(h);
		float t1 = -1 * d1 - h - a;
		float t2 = -1 * d1 + h - a;
		if(t1 > 0.0)
      result = t1;
		else if(t2 > 0.0)
      result = t2;
	}

	h = d1 * d1 - z - d2;
	if (h > EPSI)
	{
		h = sqrt(h);
		float t1 = d1 - h - a;
		float t2 = d1 + h - a;
		if(t1 > 0.0)
      result = t1;
		else if(t2 > 0.0)
      result = t2;
	}
  if (result < EPSI)
    return;
  if (result < hit.dist){
    hit.dist = result;
    hit.pos = ray.pos + ray.dir * hit.dist;
    hit.norm = normalize(hit.pos*(dot(hit.pos,hit.pos)- data.y*data.y - data.x*data.x*vec3(1.0,1.0,-1.0)));
    hit.mat = mat;
  }
}

Hit		scene(Ray r)
{
	int i = -1;
	Hit		hit;
	hit.dist = 1e20;
	hit.mat.texture = vec4(0,0,0,0);
  sphere(vec3(6, 14, -1), 5, Material(vec4(1,0,0,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(1,1,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,0,0,0)), r, hit );
  torus(vec3(3,12,-1), vec2(1,0.7), Material(vec4(1,0,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,1,1,1), vec4(0,0,0,0), vec4(0,0,0,0), vec4(0,0,0,0)), r, hit);
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
	//if (shadows(h.pos, d, h))
	//	return (color);
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
	while (++i < 5)
	{
	h = h2;
	ref.dir = h.norm;
	ref.pos = h.pos;
	h2 = scene(ref);
	on_off = on_off * h.mat.reflection.x;
	reflect += light(pos, ref, h2) * on_off;
	}
	return (lambert + reflect);
}


/* Création d'un rayon */
vec3	raytrace(vec3 ro, vec3 rd)
{
	Ray			r;
	Hit			h;
	vec3		pos_lum = vec3(15,15,-25);
	vec3		pos_lum2 = vec3(100, 75, 0);
	vec3		color = vec3(0,0,0);

  r.dir = rd;
	r.pos = ro;
	h = scene(r);
	color = calc_light(pos_lum, r, h);
	color += calc_light(pos_lum2, r, h);
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
