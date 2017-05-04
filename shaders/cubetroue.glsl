void planet(vec3 norm, vec3 pos, float data, Coupes coupe, Material mat, Ray r, inout Hit h) {
	norm = normalize(norm);
	float t = (dot(norm,pos) - (dot (norm, r.pos))) / dot (norm, r.dir);
	Hit tmp = h;
	vec3 plus = pos + data/2 + EPSI;
	vec3 moin = pos - data/2 - EPSI;

	if (t < EPSI)
		return;

	if (t < h.dist) {
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.norm = faceforward(norm, norm, r.dir);
    h.mat = mat;
		vec3	u = vec3(norm.y, norm.z, -1 * norm.x );
		vec3	v = cross(u, norm);
		h.uv = vec2(dot(h.pos, u), dot(h.pos, v));
		h.color_effect = mat.color_effect;
		h.normal_effect = mat.normal_effect;
  }
	if(((h.pos.x > plus.x || h.pos.x < moin.x) || ((h.pos.y > plus.y || h.pos.y < moin.y)) || ((h.pos.z > plus.z || h.pos.z < moin.z))) || !((h.pos.x > plus.x / 2 || h.pos.x < moin.x / 2) || ((h.pos.y > plus.y / 2 || h.pos.y < moin.y / 2)) || ((h.pos.z > plus.z / 2 || h.pos.z < moin.z / 2))))
		h = tmp;
}


void cubetroue(vec3 pos, vec3 rot, float data, Material mat, Ray r, inout Hit hit)
{
	Hit h;
	h = hit;
	Coupes c;
	r.pos = rotate(r.pos - pos, rot, 1);
	r.dir = rotate(r.dir, rot, 1);
	planet(vec3(0, 0, 1),vec3(0,0,data/2), data, c, mat, r, hit);
	planet(vec3(0, 0, 1),vec3(0,0,-data/2), data, c, mat, r, hit);
	planet(vec3(0, 1, 0),vec3(0,data/2,0), data, c, mat, r, hit);
	planet(vec3(0, 1, 0),vec3(0,-data/2,0), data, c, mat, r, hit);
	planet(vec3(1, 0, 0),vec3(data/2,0,0), data, c, mat, r, hit);
	planet(vec3(1, 0, 0),vec3(-data/2,0,0), data, c, mat, r, hit);
	if (h.dist != hit.dist){
		hit.pos = rotate(hit.pos, rot, 0);
		hit.pos += pos;
		hit.norm = rotate(hit.norm, rot, 0);
	}
}
