//GLSL Showreel - created by Antonio "toneddu2000" Latronico and released under CC0 Public Domain license https://creativecommons.org/publicdomain/zero/1.0/
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