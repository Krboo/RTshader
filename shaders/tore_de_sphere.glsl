void tore_de_sphere(vec3 pos, vec3 rot, float data, Material mat, Ray r,inout Hit h)
{
  vec3 initial = pos + data * vec3(0,0,1);
  Coupes c;
  Hit hit = h;
  r.pos = rotate(r.pos - pos, rot, 1);
	r.dir = rotate(r.dir, rot, 1);
  int i = -1;

  while (++i<250)
  {
    sphere(initial,vec3(0),data,c,mat,r,h);
    initial = rotate(initial,vec3(10,0,10),1);
  }
  if (h.dist != hit.dist){
		h.pos = rotate(h.pos, rot, 0);
		h.pos += pos;
		h.norm = rotate(h.norm, rot, 0);
	}
}
