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
void CSQC_Init(float apilevel, string enginename, float engineversion)
{
	//create sun cvar
	registercvar("sun_intensity","0.2");
	registercvar("sun_height","1000");
	//create camera cvar
	registercvar("camera_speed","0.5");
	//create glsl cvars
	registercvar("glsl_time","0");
	registercvar("glsl_mousex","0");
	registercvar("glsl_mousey","0");
	registercvar("glsl_velx","0");
	registercvar("glsl_vely","0");
	registercvar("glsl_skysize","0.006");
	registercvar("glsl_seasize","0.0006");
	registercvar("glsl_seamove","1");
	registercvar("glsl_bloomthres","0.45");
	registercvar("glsl_bloomintensity","1.2");
	//camera
	camera = spawn();
	camera.movetype = MOVETYPE_FLY;
	setorigin(camera,CAMERA_START_ORIGIN);
	//glsl init
	fxName = "ppcolor";
	fxTitle = "None";
	//fog init
	localcmd("fog 0.12 0.95 0.95 1.2 0.65 1.5\n");
	//ui
	uiMenu = TRUE;
	uiMenuQuit = FALSE;
	uiColorAlpha = 1;
	uiFlashAlpha = 1;
	//sounds
	#ifdef USESOUNDS
	precache_sound(SOUND_SEA);
	precache_sound(SOUND_SEAWAVE);
	precache_sound(SOUND_PORTAL);
	precache_sound(SOUND_WIND);
	precache_sound(SOUND_SWITCH);
	sound(camera,CHAN_AUTO,SOUND_WIND,SOUND_VOL_WIND,0,0,SOUNDFLAG_FORCELOOP);
	sound(camera,CHAN_WEAPON,SOUND_SEA,SOUND_VOL_SEA,0,0,SOUNDFLAG_FORCELOOP);
	sound(camera,CHAN_ITEM,SOUND_SEAWAVE,SOUND_VOL_SEAWAVE,0,0,SOUNDFLAG_FORCELOOP);
	#endif
}

noref float CSQC_InputEvent(float evtype, float scanx, float chary, float devid)
{
	switch(evtype){
		case IE_KEYUP:
			if (scanx == K_MOUSE1){
				fxPostprocessColor = !fxPostprocessColor;
				if(fxPostprocessColor == TRUE){
					uiColorAlpha = 1;
				}
			}
			if (scanx == K_MOUSE2){
				fxPostprocessDepth = !fxPostprocessDepth;
			}
			if (scanx == K_MWHEELUP){
				#ifdef USESOUNDS
				if(fxPostprocessColor && !uiMenu){
					sound(camera,CHAN_VOICE,SOUND_SWITCH,SOUND_VOL_SEA,0);
				}
				#endif
				uiColorAlpha = 0;
				FX_PlayLoop();
			}
			if (scanx == K_ESCAPE){
				uiMenuQuit = FALSE;
			}
			//letter N
			if (scanx == 110){
				uiMenu = TRUE;
				uiMenuQuit = FALSE;
			}
			//letter Q
			if (scanx == 113){
				uiMenu = TRUE;
				uiMenuQuit = TRUE;
			}
			//letter Y
			if (scanx == 121){
				if(uiMenuQuit){
					localcmd("quit\n");
				}
			}
		break;
	}
	return FALSE;
}

void CSQC_Input_Frame()
{
	local float spd = cvar("camera_speed");
	
	if(!uiMenu){
		makevectors(input_angles);
		camera.angles = input_angles;
		camera.velocity = v_forward;
		camera.velocity *= input_movevalues_x * spd;
		if(camera.origin_z < CAMERA_LIMIT_GROUND){
			camera.origin_z = CAMERA_LIMIT_GROUND+5;
		}
		if(camera.origin_z > CAMERA_LIMIT_SKY){
			camera.origin_z = CAMERA_LIMIT_SKY-5;
		}
		if(vlen(PORTAL1_ORG - camera.origin)<150){
			#ifdef USESOUNDS
			sound(camera,CHAN_VOICE,SOUND_PORTAL,SOUND_VOL_PORTAL,0);
			#endif
			uiFlashAlpha = 1;
			camera.origin = PORTAL2_ORG + [350,0,0];
		}
		if(vlen(PORTAL2_ORG - camera.origin)<150){
			#ifdef USESOUNDS
			sound(camera,CHAN_VOICE,SOUND_PORTAL,SOUND_VOL_PORTAL,0);
			#endif
			uiFlashAlpha = 1;
			camera.origin = PORTAL1_ORG + [-350,0,0];
		}
		
	}
	if(cvar("glsl_seamove")==TRUE){
		if(camera.velocity_x == 0 && camera.velocity_y == 0 && camera.velocity_z == 0){
			camera.origin_z += 0.1 * sin(time * 1);
		}
	}
}

float CSQC_ConsoleCommand(string strMessage)
{
	tokenize(strMessage);
	switch(argv(0))
	{
		case "togglemenu":
			uiMenu = !uiMenu;
			return TRUE;
		break;
	}
	return FALSE;
}

void CSQC_UpdateView(float vwidth, float vheight, float notmenu)
{	
	clearscene();
	//fx set vars
	FX_GlslGetUniformByCvars();
	//view properties
	setviewprop(VF_DRAWWORLD,FALSE);
	//setviewprop(VF_SCREENPSIZE,[vwidth,vheight,0]);
	setviewprop(VF_SIZE,[vwidth,vheight,0]);
	setviewprop(VF_ORIGIN, camera.origin);
	setviewprop(VF_ANGLES, camera.angles);
	Fx_Update();
	//add view entities
	addentities(MASK_ENGINE);
	//render 3d objects
	local vector seemov;
	if(cvar("glsl_seamove") == TRUE){
		seemov = [0,0,25*sin(time * 0.9)];
	}
	else{
		seemov = [0,0,0];
	}
	Render_Sky();
	Render_Sea();
	Render_PortalFrame(5,70,100,1,PORTAL1_ORG+[-58.8,0,0]+seemov,"portalframe");
	Render_Portal(64,PORTAL1_ORG+seemov,"portal");
	Render_PortalFrame(5,70,100,1,PORTAL2_ORG+[-69.1,0,0]+seemov,"portalframe2");
	Render_Portal(64,PORTAL2_ORG+seemov,"portal2");
	Render_Horizon();
	//render scene
	renderscene();
	//fx end
	FX_PostUpdate();
	//ui
	local string uicolen = "Post process color enabled";
	local string uimenutit = "GLSL Showreel - Antonio Latronico";
	local string uimenutgl = "ESC key to toggle menu";
	local string uimenumouse = "Mouse1 for toggle GLSL color, Mouse2 for toggle GLSL depth";
	local string uiquit = "Q key to quit showreel";
	local string uiquitmsg = "Do you want to leave showreel?";
	local string uiquitconfirm = "Y or N";
	local vector uitextcolor = [0.4,0.4,0.4];
	local vector uitextsize = [3.5,3.5,0];
	local vector uimenutitlesize = [7.5,7.5,0];
	local vector uimenutextsize = [5,5,0];
	if(uiMenu){
		if(!uiMenuQuit){
			drawfill([0,0,0],[vwidth,vheight,0],[1,1,1],0.92);
			drawstring([vwidth-stringwidth(uimenutit,0)*2,40,0],uimenutit,uimenutitlesize,uitextcolor,0.8,0);
			drawstring([20,70,0],uimenutgl,uimenutextsize,uitextcolor,0.8,0);
			drawstring([20,100,0],uimenumouse,uimenutextsize,uitextcolor,0.8,0);
			drawstring([20,130,0],uiquit,uimenutextsize,uitextcolor,0.8,0);
		}
		else{
			drawfill([0,0,0],[vwidth,vheight,0],[1,1,1],1);
			drawstring([vwidth-(stringwidth(uiquitmsg,0)*2),70,0],uiquitmsg,uimenutextsize,uitextcolor,0.8,0);
			drawstring([vwidth/2,95,0],uiquitconfirm,uimenutextsize,uitextcolor,0.8,0);
		}
	}
	else{
		if(uiFlashAlpha > 0){
			uiFlashAlpha -= frametime * 1;
		}
		if(fxPostprocessColor){
			if(uiColorAlpha > 0){
				uiColorAlpha -= frametime * 1;
			}
			drawstring([vwidth/2-stringwidth(uicolen,0)/2,100,0],uicolen,[10,10,0],uitextcolor+[0,0.8,0],uiColorAlpha,0);
			drawstring([20,20,0], "Glsl used: ",uitextsize,uitextcolor,0.5,0);
			drawstring([65,20,0], fxTitle,uitextsize,uitextcolor+[0,0,1.5],0.9,0);
			drawstring([20,35,0], "Scroll mouse wheel up to loop post process effects",uitextsize,uitextcolor,0.5,0);
		}
		drawfill([1,1,1],[vwidth,vheight,0],[1,1,1],uiFlashAlpha);
	}
}