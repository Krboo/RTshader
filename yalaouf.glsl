#define EPSILONE	0.01f
#define	M_PI		3.14159265359	

// Strcuture pour les rayons, la lumière, les collisions et les objets.
struct	Ray
{
	vec3	dir;
	vec3	pos;
};

struct	Light
{
	vec3	dir;
	vec3	pos;
};

struct	Hit
{
	float		dist;
	vec3		norm;
	vec3		pos;
	vec3		color;
	vec2		uv;
};

struct			Sphere
{
	vec3		pos;
	vec3		color;
	float		radius;
};

struct			Plane
{
	vec3		pos;
	vec3		norm;
	vec3		color;
};

struct	Cylinder
{
	vec3	pos;
	vec3	dir;
	vec3	color;
	float	radius;
};

struct	Cone
{
	vec3	pos;
	vec3	dir;
	vec3	color;
	float	angle;
};


float	limit(float value, float minv, float maxv)
{
	return (value < minv ? minv : (value > maxv ? maxv : value));
}

void	iSphere(Sphere s, Ray r, inout Hit h) //Intersection Sphere - Rayon
{
	vec3	dist = r.pos - s.pos;
	float	a = dot(r.dir, r.dir);
	float	b = dot(r.dir, dist);
	float	c = dot(dist, dist) - (s.radius * s.radius);
	float	delta = b * b - a * c;
	if (delta < EPSILONE)
		return ;
	float	t = (-sqrt(delta) -b) / a;
	if (t < 0)
		return ;
	if (t < h.dist)
	{
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.color = s.color;
		h.norm = (h.pos - s.pos);
		vec3	n = normalize(h.pos - s.pos);
		h.uv = vec2(-(0.5 + (atan(n.z, n.x)) / (M_PI)),
					(0.5 - asin(n.y)) / M_PI);
	}
}

void	iPlane(Plane p, Ray r, inout Hit h)//Intersection Plan - Rayon
{
	float	t = (dot(p.norm, p.pos) - dot(p.norm, r.pos)) / dot(p.norm, r.dir);
	if (t < EPSILONE)
		return ;
	if (t < h.dist)
	{
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.color = p.color;
		h.norm = faceforward(p.norm, p.norm, r.dir);
		vec3	u = vec3(p.norm.y, p.norm.z, -p.norm.x);
		vec3	v = cross(u, p.norm);
		h.uv = vec2(dot(h.pos, u), dot(h.pos, v));
	}
}

void	iCylinder(Cylinder cyl, Ray r, inout Hit h)
{
	vec3	d = r.pos - cyl.pos;
	cyl.dir = normalize(cyl.dir);
	float	a = dot(r.dir, r.dir) - pow(dot(r.dir, cyl.dir), 2);
	float	b = 2 * (dot(r.dir, d) - dot(r.dir, cyl.dir) * dot(d, cyl.dir));
	float	c = dot(d, d) - pow(dot(d, cyl.dir), 2) - pow(cyl.radius, 2);
	float	g = b * b - 4 * a * c;
	if (g < EPSILONE)
		return ;
	
	float 	t1 = (-sqrt(g) - b) / (2 * a);
	if (t1 < EPSILONE)
		return ;
	if (t1 > EPSILONE && t1 < h.dist)
	{
		h.dist = t1 - EPSILONE;
		h.pos = r.pos + r.dir * h.dist;
		vec3	temp = cyl.dir * (dot(r.dir, cyl.dir) * h.dist + dot(r.pos - cyl.pos, cyl.dir));
		vec3	tmp = h.pos - cyl.pos;
		h.color = cyl.color;
		h.norm = tmp - temp;
		vec3	d = h.pos - (cyl.pos * r.dir);
		h.uv = vec2(-(0.5 + (atan(d.z, d.x) / (M_PI * 0.25))), -((d.y / M_PI) - floor(d.y / M_PI)));
	}
}

void	iCone(Cone co, Ray r, inout Hit h)
{
	vec3	d = r.pos - co.pos;
	co.dir = normalize(co.dir);
	float	a = dot(r.dir, r.dir) - (1 + pow(tan(co.angle), 2)) * pow(dot(r.dir, co.dir), 2);
	float	b = 2 * (dot(r.dir, d) - (1 + pow(tan(co.angle), 2)) * dot(r.dir, co.dir) * dot(d, co.dir));
	float	c = dot(d, d) - (1 + pow(tan(co.angle), 2)) * pow(dot(d, co.dir), 2);
	float	g = b * b - 4 * a * c;
	if (g <= 0)
		return ;

	float t1 = (-sqrt(g) - b) / (2 * a);
	if (t1 < EPSILONE)
		return ;
	if (t1 < h.dist)
	{
		h.dist = t1;
		h.pos = r.pos + r.dir * h.dist;
		vec3	temp = (co.dir * (dot(r.dir, co.dir) * h.dist + dot(r.pos - co.pos, co.dir))) * (1 + pow(tan(co.angle), 2));
		vec3	tmp = h.pos - co.pos;
		h.color = co.color;
		h.norm = tmp - temp;
		vec3	d = normalize(h.pos - co.pos);
		h.uv = vec2(-(0.5 + (atan(h.norm.z, h.norm.x) / (M_PI * 2))), (h.norm.y /  M_PI) - floor(h.norm.y / M_PI));
	}
}

Hit		Scene(Ray r)
{
	Hit	h;
	h.dist = 1e20;
	h.color = vec3(0, 0, 0);

	Sphere		s = Sphere(vec3(20, 3, 0), vec3(0.3,0.4, 0.8), 5);
	Cylinder	cyl = Cylinder(vec3(0, 0, 0), vec3(0, 1, 0), vec3(0.5, 0.8, 0.2), 5);
	Plane		p = Plane(vec3(0, -5, 0), vec3(0, 1, 0), vec3(0.8, 0.3, 0.8));
	Cone		co = Cone(vec3(-20, 3, 0), vec3(0, 1, 0), vec3(0.8, 0.8, 0.4), M_PI * 15/180);

	iSphere(s, r, h);
	iCylinder(cyl, r, h);
	iPlane(p, r, h);
	iCone(co, r, h);
	return (h);
}

float	light(Light l, Ray r, Hit h)
{
	vec3	v1 = l.pos - h.pos;
	vec3	v3 = v1 * v1;
	vec3	dist = normalize(v1);
	float	lambert = dot(dist, h.norm);

	h.dist = sqrt(v3.x + v3.y + v3.z);
	return (limit(lambert, 0.15, 1));
}

vec4	raycast(vec3 ro, vec3 rd)
{
	vec4	color = vec4(0, 0, 0, 1);
	Ray		r;
	Hit		h;
	float	l1;
	Light	l = Light(vec3(0, 0, 0), vec3(0, 18, -10));

	r.dir = rd;
	r.pos = ro;
	h = Scene(r);
	l1 = light(l, r, h);
	if (color.xyz != vec3(0))
	{
		color.xyz = h.color * l1;
		return (color);
	}
	else
	{
		vec4 ctexture = texture(iChannel0, h.uv);
		return (ctexture);
	}
}

void	mainImage(vec2 FragCoord)
{
	vec2	uv = (FragCoord / iResolution) * 2 - 1;
	vec3	cameraPos = iMoveAmount.xyz + vec3(0, 5, -17);
	vec3	cameraDir = vec3(0, 0, 0);

	uv.x *= iResolution.x / iResolution.y;

	float	fov = 1.5;
	vec3	forward = normalize(iForward);
	vec3	right = normalize(cross(forward, vec3(0, 1, 0)));
	vec3	up = normalize(cross(right, forward));
	vec3	rd = normalize(uv.x * right + uv.y * up + fov * forward);
	fragColor = vec4(raycast(cameraPos,rd));
}
