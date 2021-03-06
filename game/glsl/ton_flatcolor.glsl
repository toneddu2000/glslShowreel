!!ver 330
//author: Antonio "toneddu2000" Latronico
//placed under cc0 public domain license
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
void main() {
	gl_FragColor = vec4(vec3(0,0,1),1.0);
	#ifdef GREENLIGHT
		gl_FragColor = vec4(vec3(0.248,0.840,0.293),1.0);
	#endif
	#ifdef GREENDARK
		gl_FragColor = vec4(vec3(0.115,0.390,0.136),1.0);
	#endif
	#ifdef AZURE
		gl_FragColor = vec4(vec3(0.666,0.823,0.912),1.0);
	#endif
	#ifdef RED
		gl_FragColor = vec4(vec3(0.910,0.081,0.116),1.0);
	#endif
	#ifdef WHITE
		gl_FragColor = vec4(vec3(1,1,1),1.0);
	#endif
	#ifdef GREYDARK
		gl_FragColor = vec4(vec3(0.330,0.340,0.340),1.0);
	#endif
}
#endif