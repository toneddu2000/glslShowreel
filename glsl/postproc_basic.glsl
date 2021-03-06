!!ver 130
!!samps screen=0
#include "sys/defs.h"
// normal render to texture postprocessing shader..nothing fancy..use this as starting point for cool shaders
varying vec2 texcoord;
#ifdef VERTEX_SHADER
void main ()
{
	gl_Position = ftetransform();
	texcoord = v_texcoord.xy;
}
#endif
#ifdef FRAGMENT_SHADER
void main ()
{
	vec4 normalColor = texture2D(s_screen, texcoord.xy);
	gl_FragColor = normalColor;
}
#endif
