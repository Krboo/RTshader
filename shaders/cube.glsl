void cube(vec3 pos, vec3 rot, float data, Material mat, Ray r, inout Hit hit)
{
	Hit h;
	h = hit;
	Coupes c;
	r.pos = rotate(r.pos - pos, rot, 1);
	r.dir = rotate(r.dir, rot, 1);
	plane(vec3(0, 0, 1),vec3(0,0,data/2), data, c, mat, r, hit);
	plane(vec3(0, 0, 1),vec3(0,0,-data/2), data, c, mat, r, hit);
	plane(vec3(0, 1, 0),vec3(0,data/2,0), data, c, mat, r, hit);
	plane(vec3(0, 1, 0),vec3(0,-data/2,0), data, c, mat, r, hit);
	plane(vec3(1, 0, 0),vec3(data/2,0,0), data, c, mat, r, hit);
	plane(vec3(1, 0, 0),vec3(-data/2,0,0), data, c, mat, r, hit);
	if (h.dist != hit.dist){
		hit.pos = rotate(hit.pos, rot, 0);
		hit.pos += pos;
		hit.norm = rotate(hit.norm, rot, 0);
	}
}
