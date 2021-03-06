!!cvardf r_glsl_ascii_mono=0
!!cvarf r_pixelate
!!samps screen=0
#include "sys/defs.h"
varying vec2 texcoord;
#ifdef VERTEX_SHADER
void main()
{
	texcoord = v_texcoord.xy;
	gl_Position = ftetransform();
}
#endif
#ifdef FRAGMENT_SHADER
uniform vec2 e_sourcesize;
uniform float cvar_r_pixelate;
void main(void)
{
	float i = cvar_r_pixelate;
	float f = 4.0;
	vec2 uv = floor(texcoord.xy * e_sourcesize); //in pixels.
	vec2 pixuv = vec2(texcoord.x/cvar_r_pixelate,texcoord.y/cvar_r_pixelate);
	vec3 col = texture2D(s_screen, uv.xy).rgb; 
	gl_FragColor = vec4(col, 1.0);
}
#endif
