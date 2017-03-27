#define M_PI 3.1415926535897932384626433832795
#define EPSI 0.01

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
		Coupe coupe;
		coupe.pos = vec3(1,2,-6);
		coupe.rot = vec3(0,1,0);

		Coupe coupe2;
		coupe2.pos = vec3(1,-2,-6);
		coupe2.rot = vec3(0,-1,0);

		if (t < EPSI) //|| decoupe(pos, h.pos, coupe, coupe2))
				return;

    if (t < h.dist) {
        h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
				h.color = color;
        h.norm = (h.pos - pos);
    }
}

/* intersection rayon / cylindre */

void cyl (vec3 v, vec3 dir, vec3 color, float f, Ray r, inout Hit h) {
    vec3 d = r.pos - v;

    dir = normalize(dir);
    float a = dot(r.dir,r.dir) - pow(dot(r.dir, dir), 2);
    float b = 2 * (dot(r.dir, d) - dot(r.dir, dir) * dot(d, dir));
    float c = dot(d, d) - pow(dot(d, dir), 2) - pow(f, 2);

    float g = b*b - 4*a*c;

    if (g < EPSI)
        return;

    float t1 = (-sqrt(g) - b) / (2*a);
    //float t2 = (sqrt(g) - b) / (2*a);

	if (t1 < EPSI)
		return ;

    if (t1 > EPSI && t1 < h.dist){
        h.dist = t1;
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

    if (g < 0)
        return;

    float t1 = (-sqrt(g) - b) / (2*a);
    //float t2 = (sqrt(g) - b) / (2*a);

	if (t1 < EPSI)
		return ;

    if (t1 < h.dist){
        h.dist = t1;
        h.pos = r.pos + r.dir * h.dist;
        vec3 temp = (dir * (dot(r.dir, dir) * h.dist + dot(r.pos - v, dir))) * (1 + pow(tan(f), 2));
        vec3 tmp = h.pos - v;
				h.color = color;
        h.norm = tmp - temp;
        }
    /*else if (t2 > 0 && t2 < h.dist){
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

Hit		scene(Ray r)
{
    Hit		hit;
    
    hit.dist = 1e20;
    hit.color = vec3(0,0,0);
    
    cone(vec3(0, 15, -6),vec3(1,0,0),vec3(1,1,0),M_PI * 15/180, r, hit);
    cyl(vec3(10, -15, -45),vec3(1,0,0),vec3(0.8,0.7,0.4),2, r, hit);
    cyl(vec3(30, -55, -25),vec3(1,0,0.8),vec3(0.8,0.7,0.8),12, r, hit);
    cyl(vec3(75, -30, -10),vec3(15,6,4),vec3(0.9,0,0.4),5, r, hit);
   	plane(vec3(1,1,0),vec3(1,1,-6),vec3(1,0.8,0), r, hit);
   	plane(vec3(1,1,0),vec3(1,1,-6),vec3(1,0.8,0), r, hit);
    sphere(vec3(0, 9, -10),vec3(0,0,1),4, r, hit);
    sphere(vec3(8, 9, -30),vec3(0,1,0),4, r, hit);
    sphere(vec3(10, 10, -40),vec3(1,0,0),4, r, hit);
    sphere(vec3(-40, 30, -40),vec3(1,0,0),4, r, hit);
    //planel(vec3(0, 0, 1),vec3(0,0,-2),vec3(1,0,0),vec3(1,0,0),2, r, hit);
    //cube(vec3(0,20,-2),vec3(1,0,0),2,r,hit);
    
    /* Position de la lumière */
    sphere(vec3(0, 18, -11),vec3(255,255,255),0.5, r, hit);
   	sphere(vec3(15, 15, -24),vec3(255,255,255),0.5, r, hit);
   	sphere(vec3(45, 20, 25),vec3(255,255,255),0.5, r, hit);
    
    return hit;
}

float		limit(float value, float min, float max)
{
	return (value < min ? min : (value > max ? max : value));
}

bool			shadows(vec3 pos, vec3 d, Hit h)
{
	Ray		shad;
	Hit		shadow;

	shad.dir = -d;
	shad.pos = pos;
	shadow = scene(shad);
	if (shadow.dist < h.dist - (EPSI * h.dist ))
		return (true);
	return (false);	
}

float			reflexion(Hit h, vec3 d)
{
	Ray rec;

	rec.dir = h.norm;
	rec.pos = h.pos;

	Hit ref = scene(rec);
	if (ref.dist < h.dist - (EPSI * h.dist))
		return (dot(d, ref.norm));
	return (0);
}


/* Définition de l'effet de la lumière sur les objets présents */
float		light(vec3 pos, Ray r, Hit h)
{
	vec3 v1 = pos - h.pos;
	vec3 v3 = v1 * v1;
	vec3 d = normalize(v1);
	float ref;

	h.dist = sqrt(v3.x + v3.y + v3.z);
//	ref = (reflexion(h, d));
//	if (ref != 0)
//		return (ref);
	if (shadows(pos, d, h) == true)
		return (0.15);
	float lambert = dot(d, h.norm);
	return (limit(lambert, 0.15, 1));
}

/* Création d'un rayon */
vec3	raycast(vec3 ro, vec3 rd)
{
	vec3		color = vec3(0,0,0);
	Ray			r;
	Hit			h;
	float 		l1;
	float 		l2;
	float 		l3;


	r.dir = rd;
	r.pos = ro;
	h = scene(r);
	l1 = light(vec3(0,18,-10), r, h);
	l2 = light(vec3(15, 15, -25), r, h);
	l3 = light(vec3(45, 20, 25), r, h);
	//color = h.color * limit(light(vec3(0,18,-10), r, h), 0.15, 1);
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

	float	fov = 1.5;
	vec3	forw = normalize(iForward);
	vec3	right = normalize(cross(forw, vec3(0, 1, 0)));
	vec3	up = normalize(cross(right, forw));
	vec3	rd = normalize(uv.x * right + uv.y * up + fov * forw);
	fragColor = vec4(raycast(cameraPos, rd), 1);
}
