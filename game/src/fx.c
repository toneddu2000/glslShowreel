//GLSL Showreel - created by Antonio "toneddu2000" Latronico and released under CC0 Public Domain license https://creativecommons.org/publicdomain/zero/1.0/

void FX_PlayLoop()
{
	fxLoop++;
	if(fxLoop > FX_TOTAL){
		fxLoop = 0;
	}
	//increase here for new effects
	switch(fxLoop){
		case 0:
			fxName = "postproc_basic";
			fxTitle = "None";
		break;
		case 1:
			fxName = "postproc_bw";
			fxTitle = "Black and white";
		break;
		case 2:
			fxName = "postproc_mblur";
			fxTitle = "Motion blur";
		break;
		case 3:
			fxName = "postproc_chr_aberration";
			fxTitle = "Chromatic aberration";
		break;
		case 4:
			fxName = "postproc_ascii";
			fxTitle = "Ascii code";
		break;
		case 5:
			fxName = "postproc_bloom";
			fxTitle = "Bloom";
		break;
		case 6:
			fxName = "postproc_median";
			fxTitle = "Median point";
		break;
		default:
			fxName = "";
		break;
	}
}

void FX_GlslPostProcessVarsInit()
{
	fxPostprocessDepth = TRUE;
	fxPostprocessColor = TRUE;
}

void Fx_Update()
{
	//local vector psize = (vector)getproperty(VF_SCREENPSIZE); //get the actual size in pixels, so we don't end up with any scaling
	local vector vsize = (vector)getproperty(VF_SCREENVSIZE);
	if(fxPostprocessColor){
		setproperty(VF_RT_DESTCOLOUR, "mycolorbuffer", 1, vsize); //rgba8
		//setproperty(VF_RT_DEPTH, "mydepthbuffer", 6, vsize); //depth32, for lots of precision (3d writes to it, 2d reads from it)
	}
}

void FX_PostUpdate()
{
	//local vector psize = (vector)getproperty(VF_SCREENPSIZE);
	local vector vsize = (vector)getproperty(VF_SCREENVSIZE);
	
	if(fxPostprocessColor){
		//mycolorbuffer and mydepthbuffer now contain the scene colour+depth.
		setproperty(VF_RT_DESTCOLOUR, ""); //2d is now drawing to the screen again.
		setproperty(VF_RT_SOURCECOLOUR, "mycolorbuffer"); //$sourcecolour now refers to 'mycolorbuffer'
		drawpic([0,0], fxName, vsize, '1 1 1', 1, 0); //do post processing
		setproperty(VF_RT_DEPTH, "mydepthbuffer", 6, vsize); //done reading from that now.
	}
}

void FX_GlslGetUniformByCvars()
{
	//setting vars to cvars, which have uniform corrispective in glsl shader.
	//add time
	fxGlslTimer = time;
	localcmd(strcat("glsl_time ",ftos(fxGlslTimer),"\n"));
	//add mouse position (for motion blur stuff)
	local vector mpos = getmousepos();
	localcmd(strcat("glsl_mousex ",ftos(mpos_x),"\n"));
	localcmd(strcat("glsl_mousey ",ftos(mpos_y),"\n"));
	//add velocity
	localcmd(strcat("glsl_velx ",ftos(camera.velocity_x),"\n"));
	localcmd(strcat("glsl_vely ",ftos(camera.velocity_y),"\n"));
}