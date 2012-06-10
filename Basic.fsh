#version 120

void main()
{
//  gl_FragColor = vec4(1.0,1.0,0.0,1.0);
    gl_FragColor = vec4(sin(0.03*gl_FragCoord[0]),
    			sin(0.03*gl_FragCoord[1]),
			sin(0.03*gl_FragCoord[2]),
			1.0);
}
