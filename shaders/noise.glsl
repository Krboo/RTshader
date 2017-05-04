float	damier(vec2 uv)
{
	return mod(floor(10 * uv.x) + floor(10 * uv.y), 2.0);
}

float	brick(vec2 uv)
{
	return 	smoothstep(0.4, 0.5, max(abs(fract(8.0 * uv.x - 0.5 * mod(floor(8.0 * uv.y), 2.0)) - 0.5), abs(fract(8.0 * uv.y) - 0.5)));
}

float rand(vec2 n)
{ 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float	noise(vec2 p)
{
	p *= 4;
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);

	float	res = mix(	mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
			mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}

float movingNoise(vec2 p)
{
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);

	float	res = mix(	mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
			mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return 10 * sin(iGlobalTime * 10 * res*res);
}

float	fbmNoise(vec2 x)
{
	return sin(1.5*x.x)*sin(1.5*x.y);
}

float fbm6( vec2 p )
{
	float f = 0.0;
	f += 0.500000*(0.5+0.5*noise( p )); p = p*2.02;
	f += 0.250000*(0.5+0.5*noise( p )); p = p*2.03;
	f += 0.125000*(0.5+0.5*noise( p )); p = p*2.01;
	f += 0.062500*(0.5+0.5*noise( p )); p = p*2.04;
	f += 0.031250*(0.5+0.5*noise( p )); p = p*2.01;
	f += 0.015625*(0.5+0.5*noise( p ));
	return f/0.96875;
}

float	smoothNoise(vec2 uv)
{
	return (fbmNoise(uv * 10) - .5f) / 1.f;
}

float	fbm(vec2 uv)
{
	return fbm6(uv * 2 + vec2(iGlobalTime));
}

void normalNoise(inout vec3 norm, vec2 uv)
{
	norm += vec3(smoothNoise(uv + vec2(2, 2)), smoothNoise(uv), smoothNoise(uv + vec2(-2, -2)));
}

void normalMovingNoise(inout vec3 norm, vec2 uv)
{
	norm += vec3(noise(uv));
}

void normalFBM(inout vec3 norm, vec2 uv)
{
	norm += vec3(fbm(uv));
}
