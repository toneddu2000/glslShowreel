!!ver 330
!!samps screen=0
!!cvarf glsl_bloomthres
!!cvarf glsl_bloomintensity
//	author: mAlk 
//	https://www.shadertoy.com/view/Ms2Xz3
varying vec2 texcoord;
#ifdef VERTEX_SHADER
attribute vec2 v_texcoord;
void main(void)
{
	gl_Position = ftetransform();
	texcoord = v_texcoord.xy;
}
#endif
#ifdef FRAGMENT_SHADER
uniform float cvar_glsl_bloomthres;
uniform float cvar_glsl_bloomintensity;

vec4 BlurColor (in vec2 Coord, in sampler2D Tex, in float MipBias)
{
	vec2 res = vec2(0.5,0.5);
	vec2 TexelSize = MipBias/res.xy;
    
    vec4  Color = texture(Tex, Coord, MipBias);
    Color += texture(Tex, Coord + vec2(TexelSize.x,0.0), MipBias);    	
    Color += texture(Tex, Coord + vec2(-TexelSize.x,0.0), MipBias);    	
    Color += texture(Tex, Coord + vec2(0.0,TexelSize.y), MipBias);    	
    Color += texture(Tex, Coord + vec2(0.0,-TexelSize.y), MipBias);    	
    Color += texture(Tex, Coord + vec2(TexelSize.x,TexelSize.y), MipBias);    	
    Color += texture(Tex, Coord + vec2(-TexelSize.x,TexelSize.y), MipBias);    	
    Color += texture(Tex, Coord + vec2(TexelSize.x,-TexelSize.y), MipBias);    	
    Color += texture(Tex, Coord + vec2(-TexelSize.x,-TexelSize.y), MipBias);    

    return Color/9.0;
}

void main() {
	float thres = cvar_glsl_bloomthres;
    float intens = cvar_glsl_bloomintensity;
    float blursize = 0.5;
    vec2 uv = (texcoord.xy);
    vec4 Color = texture(s_screen, uv);
    vec4 highlight = clamp(BlurColor(uv, s_screen, blursize)-thres,0.0,1.0)*1.0/(1.0-thres);
    gl_FragColor = 1.0-(1.0-Color)*(1.0-highlight*intens); //Screen Blend Mode	
}
#endif