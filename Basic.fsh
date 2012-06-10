#version 120

uniform int width;
uniform int height;
uniform int frameCounter;

float f(vec3 p)
{
//	vec3 bla = mod(p,500);
	float sphere =  distance(p,vec3(150+100*sin(frameCounter*0.01),150+100*cos(frameCounter*0.008),-80))-100;
	float sky = distance(p,vec3(0)) -100;
	sky = 10000000;
	float d;
	d = min(sphere,sky);
	return d;
}

vec4 march(vec3 p, vec3 dir)
{
	float d;
	float p1;
	float p2;
	float p3;
	for(int i=0; i<6;i++)
	{
		d = f(p);
		if(d>0.91||d<-0.91)
		{
			p = p + d*dir*1;
		}
		else
		{
			//richtiger ansatz, aber noch kleiner fehler. unten drunter nochmal in richtig
//			p1 = f(p+vec3(1,0,0));
//			p2 = f(p+vec3(0,1,0));
//			p3 = f(p+vec3(0,0,1));
			//berechnung normale
			float e = 0.001;
			vec3 n = vec3(f(p + vec3(e, 0, 0)) - f(p - vec3(e, 0, 0)), f(p + vec3(0, e, 0)) - f(p - vec3(0, e, 0)), f(p + vec3(0, 0, e)) - f(p - vec3(0, 0, e)));
			n = normalize(n);
			float c = dot(n,-dir);
			return vec4(c,c,c,1);
//			return vec4(1);
		}
	}
	return vec4(0.1,0.1,0.3,1);
}

void main()
{
//  gl_FragColor = vec4(1.0,1.0,0.0,1.0);
//    gl_FragColor = vec4(sin(0.03*gl_FragCoord[0]),
//    			sin(0.03*gl_FragCoord[1]),
//			sin(0.03*gl_FragCoord[2]),
//			1.0);
    gl_FragColor = march(vec3(gl_FragCoord),vec3(0,0,-1));
}
