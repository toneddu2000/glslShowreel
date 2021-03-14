/*
MIT License

Copyright (c) [year] [fullname]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//camera
entity		camera;
vector		CAMERA_START_ORIGIN = [-400,0,165];
float		CAMERA_LIMIT_GROUND = 55;
float		CAMERA_LIMIT_SKY = 1200;
//fx
float		fxPostprocessDepth, fxPostprocessColor, fxGlslTimer, fxLoop;
string		fxName, fxTitle;
float		FX_TOTAL = 6;
//ui
float		uiMenu,uiMenuQuit,uiColorAlpha,uiFlashAlpha;
//portal
vector		PORTAL1_ORG = [0,0,150];
vector 		PORTAL2_ORG = [-2000,0,150];
//sounds
//#define 	USESOUNDS
#ifdef USESOUNDS
string		SOUND_SEA = "sounds/water.wav";
string		SOUND_SEAWAVE = "sounds/seawave.wav";
string		SOUND_PORTAL = "sounds/portal.wav";
string		SOUND_WIND = "sounds/wind_loop.wav";
string		SOUND_SWITCH = "sounds/switch.wav";
float		SOUND_VOL_SEA = 0.5;
float		SOUND_VOL_SEAWAVE = 0.85;
float		SOUND_VOL_WIND = 3.5;
float		SOUND_VOL_PORTAL = 6;
#endif