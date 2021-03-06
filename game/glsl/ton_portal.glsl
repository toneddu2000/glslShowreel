!!ver 330
!!cvarf glsl_time
!!permu FOG
#include "sys/fog.h"
// 	'Warp Speed'
// 	author: David Hoskins 2013. 
//	https://www.shadertoy.com/view/Msl3WH#
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
#define TAU 6.28318530718
#define MAX_ITER 5
void main( void )
{
	float time = (cvar_glsl_time+29.) * 60.0;
    float s = 0.0, v = 0.0;
	vec2 uv = (v_edge.xy) * 2.0 - 1.0;
	float t = time*0.005;
	uv.x = (uv.x) + sin(t) * 0.5;
	float si = sin(t + 2.17); // ...Squiffy rotation matrix!
	float co = cos(t);
	uv *= mat2(co, si, -si, co);
	vec3 col = vec3(0.0);
	vec3 init = vec3(0.25, 0.25 + sin(time * 0.001) * 0.4, floor(time) * 0.0008);
	for (int r = 0; r < 100; r++) {
		vec3 p = init + s * vec3(uv, 0.143);
		p.z = mod(p.z, 2.0);
		for (int i=0; i < 10; i++)	p = abs(p * 2.04) / dot(p, p) - 0.75;
		v += length(p * p) * smoothstep(0.0, 0.5, 0.9 - s) * .002;
		// Get a purple and cyan effect by biasing the RGB in different ways...
		col +=  vec3(v * 0.8, 1.1 - s * 0.5, .7 + v * 0.5) * v * 0.013;
		s += .01;
	}
	gl_FragColor = vec4(col, 1.0);
	#ifdef FOG
	gl_FragColor = fog4(gl_FragColor);
	#endif
}
#endif