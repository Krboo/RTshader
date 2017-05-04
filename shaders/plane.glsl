void plane (vec3 rot, vec3 pos, float data, Coupes coupe, Material mat, Ray r, inout Hit h) {
	vec3 norm = normalize(rot);
	bool	dec = false;
	Hit hit = h;
	norm = normalize(norm);
	float t = (dot(norm,pos) - (dot (norm, r.pos))) / dot (norm, r.dir);
	Hit tmp = h;
	vec3 plus = pos + data/2;
	vec3 moin = pos - data/2;

	if (t < EPSI)
		return;

	vec3	inter = r.pos + r.dir * t;

	if (coupe.nsl > 0)
		dec = decoupe(pos, rot, inter, coupe);

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
	if (data == 0)
		return;
	else if(h.pos.x > plus.x || h.pos.x < moin.x || h.pos.y > plus.y || h.pos.y < moin.y || h.pos.z > plus.z || h.pos.z < moin.z)
		h = tmp;
}
