!!ver 330
!!cvarf glsl_time
!!cvarf glsl_skysize
!!permu FOG
//	author: CaliCoastReplay
// 	https://www.shadertoy.com/view/Ml3Gzs
//	Adapted from  :  https://www.shadertoy.com/view/Md3SzB
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
uniform float cvar_glsl_time;//time set in a cvar!!
uniform float cvar_glsl_skysize;

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    
	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


float hash21(vec2 p)
{
	float h = dot(p,vec2(127.1,311.7));
	
    return  -1.+2.*fract(sin(h)*43758.5453123);
}

vec2 hash22(vec2 p)
{
    p = p*mat2(127.1,311.7,269.5,183.3);
	p = -1.0 + 2.0 * fract(sin(p)*43758.5453123);
	
	return sin(p*6.283 + cvar_glsl_time/4.0);
}

float perlin_noise(vec2 p)
{
	vec2 pi = floor(p);
	vec2 pf = p-pi;
	vec2 w = pf*pf*(3.-2.*pf);
	float f00 = dot(hash22(pi+vec2(.0,.0)),pf-vec2(.0,.0));
	float f01 = dot(hash22(pi+vec2(.0,1.)),pf-vec2(.0,1.));
	float f10 = dot(hash22(pi+vec2(1.0,0.)),pf-vec2(1.0,0.));
	float f11 = dot(hash22(pi+vec2(1.0,1.)),pf-vec2(1.0,1.));
	float xm1 = mix(f00,f10,w.x);
	float xm2 = mix(f01,f11,w.x);
	float ym = mix(xm1,xm2,w.y); 
	
	return ym;
}

float noise(vec2 p)
{
	p *= 4.;
	float a = 1., r = 0., s=0.;

	for (int i=0; i<9; i++) {
	  r += a*perlin_noise(p); s+= a; p *= 2.00; a*=.57;
	}

	return r/s;///(.1*3.);
}


vec3 sphereProject(vec2 plane)
{
	vec3 r;
	plane.x -= 0.55;
	plane.y -= 0.35;
	float denom = (1.0 + plane.x*plane.x + plane.y*plane.y);
	r.x = (2.0*plane.x)/denom;    
	r.y = (2.0*plane.y)/denom;
	r.z = (1.0 - plane.x*plane.x+plane.y*plane.y)/denom;

	return r*1.2;
}

void main( void )
{
	vec2 uv = v_edge.xy / cvar_glsl_skysize * 0.6;
    
    //vec3 sphere = sphereProject(uv);
    //uv = sphere.xy/2.1;
    vec2 uv2 = uv + vec2(0.12253 + cvar_glsl_time/210.0,0.73483-cvar_glsl_time/90.3);
    vec2 uv3 = uv + vec2(0.34646 - cvar_glsl_time/150.3,0.46436 - cvar_glsl_time/180.4);
    vec2 uv4 = uv + vec2(0.98398 - cvar_glsl_time/34.5,0.11242 + cvar_glsl_time/100.7);
    float f = noise(uv)/1.0;
    f+= noise(uv3)/2.45;
    f+= noise(uv4)/0.7;
    f = f*0.35+0.55;
    vec3 lightColor = vec3(0.719,0.719,1.0);	
    vec3 color = vec3(lightColor*f);
    vec3 hsv = rgb2hsv(color);
    hsv.z += 0.5;
    float cloudCoverFactor = 0.01; 
    hsv.z *= hsv.z * hsv.z * sqrt(hsv.z)* 2.01 * (cloudCoverFactor + 0.91);
    bool deblue = false;
	if (hsv.z > 2.75)
    {
        hsv.z =4.7 - hsv.z/2.11;
        hsv.z -= 0.559;
        deblue = true;
    }
    else{
        hsv.z -= 0.041;
    }
    hsv.y *= 2.2;
    hsv.z -= 0.01;
    color = hsv2rgb(hsv);
   	if (deblue){
        color.z = color.y = color.x * .91;
        color.x -= 0.07;
    }
	gl_FragColor = vec4(color,1.0);
	#ifdef FOG
	gl_FragColor = fog4(gl_FragColor);
	#endif
}
#endif