float		limit(float value, float min, float max)
{
	return (value < min ? min : (value > max ? max : value));
}

vec3      refraction(vec3 dir, vec3 norm, float r)
{
  	float k = 1.0 - r * r * (1.0 - dot(norm, dir) * dot(norm, dir));
  	vec3 ref;

  	if (k < 0.0)
      	ref = vec3(0);
  	else
      	ref = r * dir - (r * dot(norm, dir) + sqrt(k)) * norm;
  	return (ref);
}

vec4		shadows(vec3 pos, vec3 d, vec3 color_light, Hit h)
{
	if (iShadow == 0)
		return vec4(.5);
	Ray		shadow;
	Hit		shad;
	float t;
	float ret = 1;
	vec3 color = color_light / 255;
	float transparency = 0;

	shadow.dir = d;
	shadow.pos = pos + d * EPSI;
	shad = scene(shadow);
	t = shad.dist;
	while (t < h.dist + EPSI)
	{
		transparency = atlas_fetch(shad.mat.texture, shad.uv).w;
		shadow.pos = shad.pos + d * EPSI;
		ret *= 1 - transparency;
		color += atlas_fetch(shad.mat.texture, shad.uv).xyz * transparency;
		shad = scene(shadow);
		t += shad.dist;
		if (ret == 0)
			return (vec4(0));
	}
	return (vec4(color.x,color.y,color.z,ret));
}

/* Définition de l'effet de la lumière sur les objets présents */
vec3		light(vec3 pos, vec3 light_color, Ray r, Hit h)
{
	vec3 v1 = pos - h.pos;
	vec3 v3 = v1 * v1;
	vec3 d = normalize(v1);
  	float coef = 0;
  	vec3 color = vec3(0);
  	vec3 col = atlas_fetch(h.mat.texture, h.uv).xyz;
  	vec3 bump = atlas_fetch(h.mat.bump, h.uv).xyz;
  	vec3 spec = vec3(1);
	vec3 specularColor = vec3(0);
	float specu = 0;

	h.dist = sqrt(v3.x + v3.y + v3.z);
	if (h.dist > 1e20)
		return (color);
	if (!h.inside)
		h.norm = normalize(normalize(h.norm) + bump);
	if (h.normal_effect == 1)
		normalNoise(h.norm, h.uv);
	else if (h.normal_effect == 2)
		normalMovingNoise(h.norm, h.uv);
	else if (h.normal_effect == 3)
		normalFBM(h.norm, h.uv);
 	coef = (limit(dot(h.norm, d), 0.0, 1.0));
	color = coef * col;
	vec3 v = d - h.norm * (2 * dot(h.norm, d));
	float t = dot(v, r.dir);
	if (t > 0)
		specu = pow(t, 16)  *  atlas_fetch(h.mat.specular, h.uv).x;
	if (specu > EPSI && atlas_fetch(h.mat.texture, h.uv).w == 1)
		coef += specu;
	vec4 s = shadows(h.pos, d,light_color, h);
	return (((color + s.xyz) * coef / 2) * s.w);
}

vec3	 calc_color(Ray r, vec3 pos_light, vec3 light_color, float intensity)
{
  	Hit h;
  	float   reflection;
  	float   opacity;
  	int     i = -1;
  	float   limit = 1;
  	vec3    color_hit = vec3(0);
  	vec3    color = vec3(0);
	float refrac;

	light_color *= (intensity / 10);
	//light_color /= 2;;
  	while (++i < 10)
  	{
		h.dist = 0;
    	h = scene(r);

    	reflection = atlas_fetch(h.mat.reflection, h.uv).x;
    	opacity = atlas_fetch(h.mat.texture, h.uv).w;

    	color_hit = atlas_fetch(h.mat.texture, h.uv).xyz * opacity;

		color += light(pos_light, light_color, r, h) * limit;
    	color += iAmbient * color_hit * limit;
		//color *= opacity;

    	if (opacity < 1)
    	{
			refrac = atlas_fetch(h.mat.refraction, h.uv).x * 10;
			if (refrac > 1)
				r.dir = refraction(r.dir, h.norm , (1 / refrac));
			r.pos = h.pos + r.dir * EPSI;
			limit *= (1 - opacity);
			if (limit < 0.1)
				return color;
		}
    	else if (reflection > 0)
    	{
        	r.dir = normalize(r.dir - 2.0 * dot(normalize(h.norm), r.dir) * normalize(h.norm));
			r.pos = h.pos + r.dir * EPSI;
			limit *= reflection;
			if (limit < 0.1)
				return color;
    	}
    	else
    	{
    		if (h.color_effect == 0)
        		return (color);
        	else if (h.color_effect == 1)
        		return (color * damier(h.uv));
        	else if (h.color_effect == 2)
        		return (color * brick(h.uv));
        	else if (h.color_effect == 3)
        		return (color * noise(h.uv));
        	else if (h.color_effect == 4)
        		return (color * movingNoise(h.uv));
        	else
        		return (color * fbm(h.uv));
    	}
  	}
}
