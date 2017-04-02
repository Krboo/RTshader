#define M_PI 3.1415926535897932384626433832795
#define EPSI 0.0001f

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

void plane(vec3 norm, vec3 pos, vec3 color, Ray r, inout Hit h)
{
	float t = (dot(norm,pos) - (dot (norm, r.pos))) / dot (norm, r.dir);

	if (t < EPSI)
		return;

	if (t < h.dist) {
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.color = color;
		h.norm = (faceforward (norm, norm, r.dir));
	}
}

/* Intersection rayon / plan limité (obsolete on le fera en mesh) */

void planel (vec3 norm, vec3 pos, vec3 pent, vec3 color, float ar, Ray r, inout Hit h) {
	float t = (dot(norm,pos) - dot (norm, r.pos)) / dot (norm, r.dir);
	h.pos = r.pos + r.dir * t;

	if (t < 0 || h.pos.x > pos.x + ar/2 || h.pos.x < pos.x - ar/2  || h.pos.y > pos.y + ar/2 || h.pos.y < pos.y - ar/2 || h.pos.z > pos.z + ar/2 || h.pos.z < pos.z - ar/2)
		return;

	if (t < h.dist) {
		h.dist = t;
		h.color = color;
		h.norm = (faceforward (norm, norm, r.dir));
	}
}

/* Intersection rayon / sphère */

void sphere (vec3 pos, vec3 color, float f, Ray r, inout Hit h) {
	vec3 d = r.pos - pos;

	float a = dot (r.dir, r.dir);
	float b = dot (r.dir, d);
	float c = dot (d, d) - f * f;

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
	}
	return;
}

/* intersection rayon / cylindre */

void cyl (vec3 v, vec3 dir, vec3 color, float f, Ray r, inout Hit h) {
	vec3 d = r.pos - v;

	dir = normalize(dir);
	float a = dot(r.dir,r.dir) - pow(dot(r.dir, dir), 2);
	float b = 2 * (dot(r.dir, d) - dot(r.dir, dir) * dot(d, dir));
	float c = dot(d, d) - pow(dot(d, dir), 2) - pow(f, 2);

	float g = b*b - 4*a*c;

	if (g < 0)
		return;

	float t1 = (-sqrt(g) - b) / (2*a);
	//float t2 = (sqrt(g) - b) / (2*a);

	if (t1 < 0)
		return ;

	if (t1 >= EPSI && t1 < h.dist){
		h.dist = t1 - EPSI;
		h.pos = r.pos + r.dir * h.dist;
		vec3 temp = dir * (dot(r.dir, dir) * h.dist + dot(r.pos - v, dir));
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
void cone(vec3 v, vec3 dir,vec3 color,float f, Ray r, inout Hit h) {
	vec3 d = r.pos - v;

	dir = normalize(dir);
	float a = dot(r.dir, r.dir) - (1 + pow(tan(f), 2)) * pow(dot(r.dir, dir), 2);
	float b = 2 * (dot(r.dir, d) - (1 + pow(tan(f), 2)) * dot(r.dir, dir) * dot(d , dir));
	float c = dot(d, d) - (1 + pow(tan(f), 2)) * pow(dot(d, dir), 2);

	float g = b*b - 4*a*c;

	if (g <= 0)
		return ;

	float t1 = (-sqrt(g) - b) / (2*a);
	//float t2 = (sqrt(g) - b) / (2*a);

	if (t1 < 0) 
		return ;

	if (t1 < h.dist){ 
		h.dist = t1 ;
		h.pos = r.pos + r.dir * h.dist;
		vec3 temp = (dir * (dot(r.dir, dir) * h.dist + dot(r.pos - v, dir))) * (1 + pow(tan(f), 2));
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

/* Fonction du calcul de l'intersection entre un rayon et un cube (obselete on le fera en mesh) */
void cube(vec3 pos, vec3 pent, float c, Ray r, inout Hit hit)
{
	planel(vec3(0, 0, 1),vec3(pos.x,pos.y,pos.z - c/2),pent,vec3(1,0,0),2, r, hit);
	planel(vec3(0, 0, 1),vec3(pos.x,pos.y,pos.z + c/2),pent,vec3(1,0,0),2, r, hit);
	planel(vec3(0, 1, 0),vec3(pos.x,pos.y - c/2,pos.z),pent,vec3(0,1,0),2, r, hit);
	planel(vec3(0, 1, 0),vec3(pos.x,pos.y + c/2,pos.z),pent,vec3(0,1,0),2, r, hit);
	planel(vec3(1, 0, 0),vec3(pos.x - c/2,pos.y,pos.z),pent,vec3(0,0,1),2, r, hit);
	planel(vec3(1, 0, 0),vec3(pos.x + c/2,pos.y,pos.z),pent,vec3(0,0,1),2, r, hit);
	hit.pos = hit.pos + vec3(2,0,0);
}

Hit		scene(Ray r, Obj[10] l)
{
	int i = 10;
	Hit		hit;
	hit.dist = 1e20;
	hit.color = vec3(0,0,0);
	
	while (--i > -1)
	{
		if (l[i].data.x == 0)
			sphere(l[i].pos, l[i].color, l[i].data.z, r, hit);
		else if (l[i].data.x == 1)
			cyl(l[i].pos, l[i].dir, l[i].color, l[i].data.z, r, hit);
		else if(l[i].data.x == 2)
			plane(l[i].pos, l[i].dir, l[i].color, r, hit);
		else if(l[i].data.x == 3)
			cone(l[i].pos, l[i].dir, l[i].color, l[i].data.z, r, hit);
	}
		
	//cube(vec3(0,20,-2),vec3(1,0,0),2,r,hit);

	//sphere(vec3(0, 18, -11),vec3(255,255,255),0.5, r, hit);
	//sphere(vec3(15, 15, -24),vec3(255,255,255),0.5, r, hit);
	//sphere(vec3(45, 20, 25),vec3(255,255,255),0.5, r, hit);

	return hit;
}

float		limit(float value, float min, float max)
{
	return (value < min ? min : (value > max ? max : value));
}

bool			shadows(vec3 pos, vec3 d, Hit h, Obj l[10])
{
	Ray		shadow;
	Hit		shad;

	shadow.dir = d;
	shadow.pos = pos + EPSI;
	shad = scene(shadow, l);
	if (shad.dist < h.dist)
		return (true);
	return (false);	
}
/*
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
   if (ref.dist < h.dist )//- (EPSI * h.dist))
  		return (dot(d2, ref.norm));
   return (0);
}
*/
/* Définition de l'effet de la lumière sur les objets présents */
float		light(vec3 pos, Ray r, Hit h, Obj l[10])
{
	vec3 v1 = pos - h.pos;
	vec3 v3 = v1 * v1;
	vec3 d = normalize(v1);
	float lambert ;
	float ref ;
	h.dist = sqrt(v3.x + v3.y + v3.z);
	if (shadows(h.pos , d, h, l))
		return (0.15);
	//ref = reflexion(h, d, pos);
	//if (ref != 0)
	//	return (ref);
	lambert = limit(dot(d, h.norm), 0.15, 1.0);
	return (lambert);
}

/*OBJ : data (type/material/size) + pos + dir + color */
Obj[10]		map(void)
{
	Obj	l[10];
	l[0] = Obj(vec3(0,0,4), vec3(15, 5, -10), vec3(0,0,0), vec3(0,0,1));
	l[1] = Obj(vec3(0,0,4), vec3(8, 9, -30), vec3(0,0,0), vec3(0,1,0));
	l[2] = Obj(vec3(0,0,4), vec3(15, 15, -45), vec3(0,0,0), vec3(1,0,0));
	l[3] = Obj(vec3(0,0,4), vec3(40, 90, 100), vec3(0,0,0), vec3(1,0,0));
	l[4] = Obj(vec3(1,0,2), vec3(100, -125, 245), vec3(2.8,0.7,0.4), vec3(1,1,0));
	l[5] = Obj(vec3(1,0,12), vec3(30, -55, -25), vec3(3,0.7,0.8), vec3(1, 0, 0.8));
	l[6] = Obj(vec3(1,0,9), vec3(75, -50, -160), vec3(15,5,0.4), vec3(0.2,0.5,0.5));
	l[7] = Obj(vec3(2,0,0), vec3(1,1,0),vec3(1,1,-6),vec3(1,0.8,0));
	l[8] = Obj(vec3(2,0,0), vec3(0,1,0),vec3(50,-280,-30),vec3(0.5,0.8,0));
	l[9] = Obj(vec3(3,0,0.2), vec3(0, 15, -6),vec3(1,0,0),vec3(1,1,0));
	return (l);
}

/* Création d'un rayon */
vec3	raytrace(vec3 ro, vec3 rd)
{
	vec3		color = vec3(0,0,0);
	Ray			r;
	Hit			h;
	float 		l1;
	float 		l2;
	float 		l3;

	Obj l[] = map();
	r.dir = rd;
	r.pos = ro;
	h = scene(r, l);
	l1 = light(vec3(0,18,-10), r, h,l);
	l2 = light(vec3(15, 15, -25), r, h,l);
	l3 = light(vec3(45, 20, 25), r, h,l);
	color = h.color * ((l1 + l2 + l3) / 3);
	return color;
}


void		mainImage(vec2 coord)
{
	vec2	uv = (coord / iResolution) * 2 - 1;
	vec3	cameraPos = iMoveAmount.xyz + vec3(0, 5, -17);
	vec3	cameraDir = vec3(0,0,0);
	vec3	col;

	uv.x *= iResolution.x / iResolution.y;
	//Obj l[] = map();
	float	fov = 1.5;
	vec3	forw = normalize(iForward);
	vec3	right = normalize(cross(forw, vec3(0, 1, 0)));
	vec3	up = normalize(cross(right, forw));
	vec3	rd = normalize(uv.x * right + uv.y * up + fov * forw);
	fragColor = vec4(raytrace(cameraPos, rd), 1);
}
