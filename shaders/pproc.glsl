vec3	sepia(vec3 color)
{
	vec3	col = vec3(	clamp(color.r * 0.393 + color.g * 0.769 + color.b * 0.189, 0.0, 1.0)
		 			  , clamp(color.r * 0.349 + color.g * 0.686 + color.b * 0.168, 0.0, 1.0)
		 			  , clamp(color.r * 0.272 + color.g * 0.534 + color.b * 0.131, 0.0, 1.0));
		return col;
}

vec3	black_white(vec3 color)
{
	float	t = max(color.r, max(color.g, color.b));
	return vec3(t, t, t);
}

vec3	nightvision(vec3 color)
{
	float	t = max(max(color.r, color.g), color.b);
	return vec3(0.0, t, 0.0);
}

vec3	vignetting(vec3 color, vec2 coord)
{
	vec2	pos = coord;
	float	len = length(pos);
	float	vignette = smoothstep(0.9, 0.9 - 0.45, len);
	color = mix(color, color * vignette, 0.5);
	return color;
}

