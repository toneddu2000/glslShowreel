!!ver 330
!!cvarf glsl_time
!!cvarf glsl_seasize
!!permu FOG
// 	author: David Hoskins.
//	https://www.shadertoy.com/view/MdlXz8
// 	Water turbulence effect by joltz0r 2013-07-04, improved 2013-07-07
#include "sys/fog.h"
#ifdef VERTEX_SHADER
attribute vec2 v_texcoord;
varying vec2 v_edge;
void main(void)
{
  gl_Position = ftetransform();
  v_edge = v_texcoord.xy;
}
#endif

#ifdef FRAGMENT_SHADER
varying vec2 v_edge;
uniform float cvar_glsl_time;
uniform float cvar_glsl_seasize;
#define TAU 6.28318530718
#define MAX_ITER 5

void main( void )
{
	float time = cvar_glsl_time * .5+23.0;
	vec2 texres = vec2(cvar_glsl_seasize,cvar_glsl_seasize);
    // uv should be the 0-1 uv of texture...
	vec2 uv = v_edge.xy / texres.xy;
    vec2 p = mod(uv*TAU, TAU)-250.0;
	vec2 i = vec2(p);
	float c = 1.0;
	float inten = .005;
	for (int n = 0; n < MAX_ITER; n++) {
		float t = time * (1.0 - (3.5 / float(n+1)));
		i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
		c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
	}
	c /= float(MAX_ITER);
	c = 1.17-pow(c, 1.4);
	vec3 colour = vec3(pow(abs(c), 8.0));
    colour = clamp(colour + vec3(0.0, 0.35, 0.5), 0.0, 1.0);
	gl_FragColor = vec4(colour, 1.0);
	#ifdef FOG
	gl_FragColor = fog4(gl_FragColor);
	#endif
}
#endif