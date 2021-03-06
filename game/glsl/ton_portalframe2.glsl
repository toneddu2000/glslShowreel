!!ver 330
!!cvarf glsl_time
//	author: Antonio "toneddu2000" Latronico
//	placed under cc0 public domain license
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
uniform float cvar_glsl_time;//time set in a cvar!!
vec3 start = vec3(0.912,0.161,0.003);
vec3 end = vec3(1.000,0.697,0.139);

void main() {
	vec3 color = vec3(0.0);
    color = mix(start, end, abs(sin(cvar_glsl_time))); 
	gl_FragColor = vec4(color,1.0);
}
#endif