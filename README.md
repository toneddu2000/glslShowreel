# glslShowreel
![Project Logo](/project.png)
 Mini example about how to use GLSL shaders on FTEQW engine
Youtube video: https://youtu.be/BMtCqBOdkeU


## What?
glslShowreel started as a tutorial on InsideQC forums to show how to create a 3d scene entirely with code, with no models, nor textures, and, moreover, to demonstrate the power of FTEQW game engine OpenGL backend. The project is writte in client side only Quake C(csqc) language.

## Navigate the demo
Left mouse button: toggle GLSL post processing on/off
Mouse wheel: loop through all the glsl effects loaded.
I embedded 6 GLSL post processing effects, but, of course, editing the src, the possibilities are endless.
WASD keys and mouse to move, as usual
KNOWN ISSUES: when fired up and clicked with left mouse button, a checker image shows up: just scroll the mouse wheel to change the effect and the game will be back to normal

## Why?
There's not really an answer, since the forums at InsideQC became unusable, and since someone asked about the source code, I'll post it here.
I decided to update the code to permit people to use it with no hassle, since the engine code changed A LOT regarding glsl syntax respect the one posted on InsideQC

## A little in depth
FTEQW exposes to qc developers the possibility to interact with screen between a frame and another. That can be done in client side in the CSQC_UpdateView() function. Is it possible to intercept glsl drawing frame through the ```
setproperty(VF_RT_DESTCOLOUR, "");
setproperty(VF_RT_SOURCECOLOUR, "mycolorbuffer");
```
combo, setting the color and depth buffer(the depth buffer is used to store depth informations about how far objects are in screen space) and then draw them trough the drawpic() function. The drawpic function is just a simple function that draws 2d textures on screen, in this case the textures are rendertotexture 2dsamples.
The fx.c file is the one that describes how to play with glsl effects

## glsl syntax
respect other engines the syntax of glsl files is quite identical. There are 2 #IFDEF blocks that identify vertex and fragment blocks. The only main difference is the use of 2d samplers. To create, for example, a 2d Sampler where to store screen texture, you have to type, at the beginning, after the !!ver keyword(used to identify the version of glsl file), the sampler like this
```
!!ver 330
!!samps screen=0
```
in this case you'll be able to use s_screen as the first 2d sampler (order matters). Then this order need to be replicated in the scripts/shaderfile.shader with the syntax
```
shadername
{
	program glslfilename (without path name or .glsl extension)
	affine
	{
		map $sourcecolour
	}
}
```
Since order matters, if you want to store color buffer AND depth buffer, you shader block must be written like this:
```
shadername
{
	program glslfilename
	affine
	{
		map $sourcecolour
	}
	{
		map $sourcedepth
	}
}
```
if you want to ignore depth test use the nodepthtest keyword after the map command
```
shadername
{
	program glslfilename (without path name or .glsl extension)
	affine
	{
		map $sourcecolour
		nodepthtest
	}
}
```
## How to run the demo
For Windows users, I'll leave the fteqwgl.exe and the fteqccgui.exe in the project, so that, if you want to fire it immediately, you can just click on the fteqwgl_VERSION.exe (I'll put here the most updated version atm)
For editing source code, you have to edit the .c files in the src folder, and then recompile them with the fteqccgui.exe included. It's GUI based and it's very straightforward.
For Linux users, you can build your own version of FTEQW game engine at
https://sourceforge.net/p/fteqw/code/HEAD/tree/trunk/engine/
launch it and then press shift + ESC to show console and then type compile and hit enter to recompile all the source code (remember: if you use the compile command, src files must be located in the src folder)

## Sounds
Sounds at the moment are disabled. If you want to enable them, just uncomment #define 	USESOUNDS in defscustom.c and create some sounds for water, wind,etc, and put them in the sounds folder(I won't upload the sounds I created because I'm not sure about their licenses)

## License warning
All the src code is created by me and release under MIT license, but every glsl shader file belongs to its author with ITS OWN LICENSE (usally not permissive for commercial purpose, you've been warned).
Here all the authors with link to file:

Overcast Sky
author: CaliCoastReplay
https://www.shadertoy.com/view/Ml3Gzs

Warp Speed
author: David Hoskins 2013.
https://www.shadertoy.com/view/Msl3WH#

Synthetic aperture
author: FabriceNeyret2
https://www.shadertoy.com/view/ldlSzX#

Tileable Water Caustic
author: David Hoskins
https://www.shadertoy.com/view/MdlXz8

Post Processing effect: ASCII
author: mattdesl
https://www.npmjs.com/package/glsl-ascii-filter#float-asciifilter-vec3-color-vec2-uv-float-pixelsize

Post Processing effect: Black&White
author: lezard
https://blog.sovapps.com/play-with-shaders-black-and-white-part-1/

Post Processing effect: Bloom
author: mAlk 
https://www.shadertoy.com/view/Ms2Xz3

Post Processing effect: Barrel Blur Chroma
author: hornet
https://www.shadertoy.com/view/XssGz8

Post Processing effect: Fast, Small-Radius GPU Median Filter
author: Morgan McGuire
http://graphics.cs.williams.edu/papers/MedianShaderX6/

Post Processing effect: GLSL depth of field (used as Motion Blur)
author: martins upitis
http://devlog-martinsh.blogspot.it/2011/10/glsl-depth-of-field-with-bokeh-v2.html