void disk (vec3 norm, vec3 pos, float data, Material mat, Ray r, inout Hit h) {
	norm = normalize(norm);
	float t = (dot(norm,pos) - (dot (norm, r.pos))) / dot (norm, r.dir);
	Hit tmp = h;

	if (t < EPSI)
		return;

	if (t < h.dist) {
		h.dist = t;
		h.pos = r.pos + r.dir * h.dist;
		h.norm = faceforward(norm, norm, r.dir);
    	h.mat = mat;
		vec3	u = vec3(norm.y, norm.z, -1 * norm.x);
		vec3	v = cross(u, norm);
		h.uv = vec2(dot(h.pos, u), dot(h.pos, v));
		h.color_effect = mat.color_effect;
		h.normal_effect = mat.normal_effect;
  	}

  	if (data == 0)
		return;

  	vec3 sous = pos - h.pos;
	float dist = sous.x * sous.x + sous.y * sous.y + sous.z * sous.z;

	if(dist > data || dist < data / 3)
		h = tmp;
}
