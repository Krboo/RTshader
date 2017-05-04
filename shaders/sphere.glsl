void sphere (vec3 pos, vec3 rot, float data, Coupes coupe, Material mat, Ray r, inout Hit h){
	vec3 d = r.pos - pos;
	bool dec = false;
	bool dec1 = false;
	float a = dot (r.dir, r.dir);
	float b = dot (r.dir, d);
	float c = dot (d, d) - data * data;

	float g = b*b - a*c;

	if (g < EPSI)
		return;

	float t = (-sqrt (g) - b) / a;
	float t1 = (sqrt (g) - b) / a;

	vec3 inter = r.pos + r.dir * t;
	vec3 inter1 = r.pos + r.dir * t1;

	if (coupe.nsl > 0)
	{
		dec = decoupe(pos, rot, inter, coupe);
		dec1 = decoupe(pos, rot, inter1, coupe);
	}
	if (t > EPSI && t < h.dist && !dec) {
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.mat = mat;
		vec3 n = normalize(h.pos - pos);
		n = rotate(n, rot, 1);
		h.uv = vec2(atan(n.x, n.z) / (M_PI) + 0.5, -(n.y * 0.5 + 0.5));
		h.norm = h.pos - pos;
		h.inside = false;
		h.color_effect = mat.color_effect;
		h.normal_effect = mat.normal_effect;
		return;
	}

	if ((t < EPSI || dec) && !dec1){
		if (t1 > EPSI && t1 < h.dist){
			h.dist = t1;
			h.pos = r.pos + r.dir * h.dist;
			h.norm = -1 * (h.pos - pos);
			vec3 n = normalize(h.pos - pos);
			n = rotate(n, rot, 1);
			h.uv = vec2(atan(n.x, n.z) / (2 * M_PI) + 0.5, -(n.y * 0.5 + 0.5));
			h.mat = mat;
			h.inside = true;
			h.color_effect = mat.color_effect;
			h.normal_effect = mat.normal_effect;
		}
		return;
	}
}
