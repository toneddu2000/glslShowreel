!!ver 130
//	author: lezard //https://blog.sovapps.com/author/lezard/
//	https://blog.sovapps.com/play-with-shaders-black-and-white-part-1/
!!samps screen=0
#include "sys/defs.h"
varying vec2 texcoord;
#ifdef VERTEX_SHADER
void main ()
{
	gl_Position = ftetransform();
	texcoord = v_texcoord.xy;
}
#endif
#ifdef FRAGMENT_SHADER
varying vec3 graycol;
uniform vec4 tint = vec4(1,1,1,1);

void main ()
{
	vec4 normalColor = texture2D(s_screen, texcoord.xy);
    float gray = 0.299*normalColor.r + 0.587*normalColor.g + 0.114*normalColor.b;
    gl_FragColor = vec4(gray, gray, gray, normalColor.a);
}
#endif
