precision highp float;
#define M_PI 3.1415926535897932384626433832795
#define EPSI 0.001f

struct		Ray
{
	vec3	dir;
	vec3	pos;
};

struct		Hit
{
	float	dist;
	vec3	color;
	vec3	norm;
	vec3	pos;
	vec4	data;
};

struct	Coupe
{
	vec3	pos;
	vec3	rot;
};

struct	Obj
{
	vec3	data;	//type, mat, size
	vec3	pos;
	vec3	dir;
	vec3	color;
};



Obj		create_obj(vec3 data, vec3 pos, vec3 dir, vec3 color)
{
	Obj		new;

	new.data = data;
	new.pos = pos;
	new.dir = dir;
	new.color = color;
	return (new);
}

/* Découpe de sphère */

bool decoupe(vec3 centre, vec3 inter, Coupe c, Coupe c2)
{
	float d = (c.rot.x * c.pos.x + c.rot.y * c.pos.y + c.rot.z * c.pos.z) * -1;

	if (c.rot.x * inter.x + c.rot.y * inter.y + c.rot.z * inter.z + d > 0)
		return(true);

	float d2 = (c2.rot.x * c2.pos.x + c2.rot.y * c2.pos.y + c2.rot.z * c2.pos.z) * -1;

	if (c2.rot.x * inter.x + c2.rot.y * inter.y + c2.rot.z * inter.z + d > 0)
		return(true);

	return(false);
}

/* Intersection rayon / plan */

void plane(vec3 norm, vec3 pos, vec3 color, vec4 data, Ray r, inout Hit h)
{
	float t = (dot(norm,pos) - (dot (norm, r.pos))) / dot (norm, r.dir);

	if (t < EPSI)
		return;

	if (t < h.dist) {
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.color = color;
		h.norm = (faceforward (norm, norm, r.dir));
		h.data.y = data.y;
	}
}

/* Intersection rayon / plan limité (obsolete on le fera en mesh) */

void planel (vec3 norm, vec3 pos, vec3 rot, vec3 color, float ar, Ray r, inout Hit h) {
	//norm = norm + rot;
	float t = (dot(norm,pos) - (dot (norm, r.pos))) / dot (norm, r.dir);
	Hit tmp = h;

	if (t < EPSI)
		return;

	if (t < h.dist) {
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.color = color;
		h.norm = (faceforward (norm, norm, r.dir));
	}
	if (h.pos.x > pos.x + ar/2 || h.pos.x < pos.x - ar/2  || h.pos.y > pos.y + ar/2 || h.pos.y < pos.y - ar/2 || h.pos.z > pos.z + ar/2 || h.pos.z < pos.z - ar/2)
		h = tmp;
}

/* Intersection rayon / sphère */

void sphere (vec3 pos, vec3 color, vec4 data, Ray r, inout Hit h) {
	vec3 d = r.pos - pos;

	float a = dot (r.dir, r.dir);
	float b = dot (r.dir, d);
	float c = dot (d, d) - data.x * data.x;

	float g = b*b - a*c;

	if (g < EPSI)
		return;

	float t = (-sqrt (g) - b) / a;
	//	Coupe coupe;
	//	coupe.pos = vec3(1,2,-6);
	//	coupe.rot = vec3(0,1,0);

	//	Coupe coupe2;
	//	coupe2.pos = vec3(1,-2,-6);
	//	coupe2.rot = vec3(0,-1,0);

	if (t < 0) //|| decoupe(pos, h.pos, coupe, coupe2))
		return;

	if (t < h.dist) {
		h.dist = t + EPSI;
		h.pos = r.pos + r.dir * h.dist;
		h.color = color;
		h.norm = (h.pos - pos);
		h.data.y = data.y;
	}
	return;
}

/* intersection rayon / cylindre */

void cyl (vec3 v, vec3 dir, vec3 color, vec4 data, Ray r, inout Hit h) {
	vec3 d = r.pos - v;

	vec3 dire = normalize(dir);
	float a = dot(r.dir,r.dir) - pow(dot(r.dir, dire), 2);
	float b = 2 * (dot(r.dir, d) - dot(r.dir, dire) * dot(d, dire));
	float c = dot(d, d) - pow(dot(d, dire), 2) - data.y * data.y;
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
		vec3 temp = dire * (dot(r.dir, dire) * h.dist + dot(r.pos - v, dire));
		vec3 tmp = h.pos - v;
		h.color = color;
		h.norm = tmp - temp;
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

/* Fonction du calcul de l'intersection entre un rayon et un cone */
void cone(vec3 v, vec3 dir,vec3 color,vec4 data, Ray r, inout Hit h) {
	vec3 d = r.pos - v;

	vec3 dire = normalize(dir);
	float a = dot(r.dir, r.dir) - (1 + pow(tan(data.y), 2)) * pow(dot(r.dir, dire), 2);
	float b = 2 * (dot(r.dir, d) - (1 + pow(tan(data.y), 2)) * dot(r.dir, dire) * dot(d , dire));
	float c = dot(d, d) - (1 + pow(tan(data.y), 2)) * pow(dot(d, dire), 2);

	float g = b*b - 4*a*c;

	if (g <= 0)
		return ;

	float t1 = (-sqrt(g) - b) / (2*a);
	//float t2 = (sqrt(g) - b) / (2*a);

	if (t1 < EPSI)
		return ;

	if (t1 < h.dist){
		h.dist = t1 ;
		h.pos = r.pos + r.dir * h.dist;
		vec3 temp = (dire * (dot(r.dir, dire) * h.dist + dot(r.pos - v, dire))) * (1 + pow(tan(data.y), 2));
		vec3 tmp = h.pos - v;
		h.color = color;
		h.norm = tmp - temp;
	}
	/*else if (t2 > 0){
	  h.dist = t2;
	  h.pos = r.pos + r.dir * h.dist;
	  vec3 temp = (rot * (dot(r.dir, rot) * h.dist + dot(r.pos - v, rot))) * (1 + pow(tan(f), 2));
	  vec3 tmp = h.pos - v;
	  h.color = color;
	  h.norm = temp - tmp;
	  }*/
}

/* Fonction du calcul de l'intersection entre un rayon et un cube (manque la rotation) */
void cube(vec3 pos, vec3 rot, vec3 color, vec4 data, Ray r, inout Hit hit)
{
	r.dir -= r.pos;
	r.pos += rot;
	r.dir += r.pos;
	planel(vec3(0, 0, 1),vec3(pos.x,pos.y,pos.z - data.x/2),rot,color, data.x, r, hit);
	planel(vec3(0, 0, 1),vec3(pos.x,pos.y,pos.z + data.x/2),rot,color,data.x, r, hit);
	planel(vec3(0, 1, 0),vec3(pos.x,pos.y - data.x/2,pos.z),rot,color,data.x, r, hit);
	planel(vec3(0, 1, 0),vec3(pos.x,pos.y + data.x/2,pos.z),rot,color,data.x, r, hit);
	planel(vec3(1, 0, 0),vec3(pos.x - data.x/2,pos.y,pos.z),rot,color,data.x, r, hit);
	planel(vec3(1, 0, 0),vec3(pos.x + data.x/2,pos.y,pos.z),rot,color,data.x, r, hit);
}

Hit		scene(Ray r)
{
	int i = -1;
	Hit		hit;
	hit.dist = 1e20;
	hit.color = vec3(0,0,0);
	sphere(vec3(15, 5, -10), vec3(0,0,0), vec4(4,1,0,0),s r, hit );
	sphere(vec3(8, 9, -30), vec3(0,1,0), vec4(4,0.7,0,0), r, hit);
	sphere(vec3(15, 15, -45), vec3(1,0,0), vec4(4,0,0,0), r, hit);
	sphere(vec3(20, 30, -50), vec3(1,0.6,0), vec4(4,0,0,0), r, hit);
	cyl(vec3(100, -125, 245), vec3(2.8,0.7,0.4), vec3(1,0,0), vec4(0,0,0,0), r, hit);
	cyl(vec3(30, -55, -25), vec3(3,0.7,0.8), vec3(1,0,0.8), vec4(12,0,0,0), r, hit);
	cyl(vec3(75, -50, -160), vec3(15,5,0.4), vec3(0.2,0.5,0.5), vec4(9,0,0,0), r, hit);
	plane(vec3(1,1,0),vec3(1,1,-6),vec3(1,0.8,0), vec4(0,0,0,0), r, hit);
	plane(vec3(0,1,0),vec3(50,-280,-30),vec3(1,1,1),vec4(0,0,0,0), r, hit);
	//sphere(vec3(51, 51, 51), vec3(1,1,1), 0.5, r, hit);
	//sphere(vec3(16, 16, -24), vec3(1,1,1), 0.5, r, hit);
	//cube(vec3(5, 15, -25), vec3(0,0,0), vec3(0,1,1), 4, r, hit);
	//Obj(vec3(3,0,0.2), vec3(0, 15, -6),vec3(1,0,0),vec3(1,1,0)));
	//Obj(vec3(0,0,0), vec3(0, 18, -10), vec3(0,0,0), vec3(0,0,0));
	//Obj(vec3(0,0,0), vec3(15, 15, -25), vec3(0,0,0), vec3(0,0,0));
	//Obj(vec3(0,0,0), vec3(45, 20, 25), vec3(0,0,0), vec3(0,0,0)));

	//sphere(vec3(0, 18, -11),vec3(255,255,255),0.5, r, hit);
	//sphere(vec3(15, 15, -24),vec3(255,255,255),0.5, r, hit);
	//sphere(vec3(45, 20, 25),vec3(255,255,255),0.5, r, hit);

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
	shadow.pos = pos;
	shad = scene(shadow);
	if (shad.dist < h.dist)
	//if (shad.dist < h.dist - EPSI * h.dist)
		return (true);
	return (false);
}

float			reflexion(Hit h, vec3 d, vec3 pos)
{
   Ray reflexion;
   Hit ref;

   reflexion.dir = h.norm;
   reflexion.pos = h.pos;
 	ref = scene(reflexion);
	vec3 v1 = h.pos - ref.pos;
	vec3 v3 = v1 * v1;
	vec3 d2 = normalize(v1);
  if (ref.dist < h.dist)
  	return (dot(d2, ref.norm));
   return (0);
}

/* Définition de l'effet de la lumière sur les objets présents */
float		light(vec3 pos, Ray r, Hit h)
{
	vec3 v1 = pos - h.pos;
	vec3 v3 = v1 * v1;
	vec3 d = normalize(v1);

	float ambient = 0.20;
	float	lambert = 0.0;
	h.dist = sqrt(v3.x + v3.y + v3.z);
	if (shadows(h.pos, d, h))
		return (ambient);
	lambert = limit(dot(h.norm, d), 0.0, 1.0);
	lambert += ambient;
	return (lambert);
}

/* Création d'un rayon */
vec3	raytrace(vec3 ro, vec3 rd)
{
	vec3		color = vec3(0,0,0);
	vec3		lum = vec3(0,0,0);
	vec3		lumref = vec3(0,0,0);
	vec3		lumref2 = vec3(0,0,0);
	Ray			r;
	Ray			ref;
	Hit			h;
	Hit			h2;
	float 		a = 0.0;
	float 		b = 0.0;
	int			i = -1;
	r.dir = rd;
	r.pos = ro;
	h = scene(r);
	ref.dir = h.norm;
	ref.pos = h.pos;
	h2 = scene(ref);
	lum = h.color * (light(vec3(15, 15, -25), r, h));
	lumref = h2.color * light(vec3(15, 15, -25), r, h2) * h.data.y;
	ref.dir = h2.norm;
	ref.pos = h2.pos;
	h2 = scene(ref);
	lumref2 = h2.color * light(vec3(15, 15, -25), r, h2) * h.data.y;
	if (h.dist < 1e20)
		lum = (lum + lumref + lumref2) / 3;
	//lum += light(vec3(50, 50, 50), r, h);
color = lum;
	return color;
}

void		mainImage(vec2 coord)
{
	vec2	uv = (coord / iResolution) * 2 - 1;
	vec3	cameraPos = iMoveAmount.xyz + vec3(0, 5, -17);
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
