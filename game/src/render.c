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

void Render_Cube(float side,vector org)
{		
	local string shd = "cube";
	
	//left_ok
	R_BeginPolygon(shd);
		R_PolygonVertex([-side,side,side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,-side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// top_ok
		R_PolygonVertex([side,-side,side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// back_ok
		R_PolygonVertex([side,side,-side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([side,-side,side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([side,-side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	//	right_ok
		R_PolygonVertex([side,-side,side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,-side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([side,-side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// bottom_ok
		R_PolygonVertex([side,side,-side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,-side,-side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,-side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
}

void Render_PortalFrame(float sd1,float sd2,float sd3,float size, vector org,string shd)
{
	local float side1 = sd1 * size;
	local float side2 = sd2 * size;
	local float side3 = sd3 * size;
	
	R_BeginPolygon(shd);
		R_PolygonVertex([-side1, side2, -side3]+org,[-1, 0, 0],[1,1,1],1);
		R_PolygonVertex([-side1, -side2, -side3]+org,[-1, 0, 0],[1,1,1],1);
		R_PolygonVertex([-side1, -side2, side3]+org,[-1, 0, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([-side1, -side2, side3]+org,[-1, 0, 0],[1,1,1],1);
		R_PolygonVertex([-side1, side2, side3]+org,[-1, 0, 0],[1,1,1],1);
		R_PolygonVertex([-side1, side2, -side3]+org,[-1, 0, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([-side1, side2, side3]+org,[0, 1, 0],[1,1,1],1);
		R_PolygonVertex([side1, side2, side3]+org,[0, 1, 0],[1,1,1],1);
		R_PolygonVertex([side1, side2, -side3]+org,[0, 1, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([side1, side2, -side3]+org,[0, 1, 0],[1,1,1],1);
		R_PolygonVertex([-side1, side2, -side3]+org,[0, 1, 0],[1,1,1],1);
		R_PolygonVertex([-side1, side2, side3]+org,[0, 1, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([side1, side2, side3]+org,[1, 0, 0],[1,1,1],1);
		R_PolygonVertex([side1, -side2, side3]+org,[1, 0, 0],[1,1,1],1);
		R_PolygonVertex([side1, -side2, -side3]+org,[1, 0, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([side1, -side2, -side3]+org,[1, 0, 0],[1,1,1],1);
		R_PolygonVertex([side1, side2, -side3]+org,[1, 0, 0],[1,1,1],1);
		R_PolygonVertex([side1, side2, side3]+org,[1, 0, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([-side1, -side2, -side3]+org,[0, -1, 0],[1,1,1],1);
		R_PolygonVertex([side1, -side2, -side3]+org,[0, -1, 0],[1,1,1],1);
		R_PolygonVertex([side1, -side2, side3]+org,[0, -1, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([side1, -side2, side3]+org,[0, -1, 0],[1,1,1],1);
		R_PolygonVertex([-side1, -side2, side3]+org,[0, -1, 0],[1,1,1],1);
		R_PolygonVertex([-side1, -side2, -side3]+org,[0, -1, 0],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([-side1, -side2, -side3]+org,[0, 0, -1],[1,1,1],1);
		R_PolygonVertex([-side1, side2, -side3]+org,[0, 0, -1],[1,1,1],1);
		R_PolygonVertex([side1, side2, -side3]+org,[0, 0, -1],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([side1, side2, -side3]+org,[0, 0, -1],[1,1,1],1);
		R_PolygonVertex([side1, -side2, -side3]+org,[0, 0, -1],[1,1,1],1);
		R_PolygonVertex([-side1, -side2, -side3]+org,[0, 0, -1],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([side1, -side2, side3]+org,[0, 0, 1],[1,1,1],1);
		R_PolygonVertex([side1, side2, side3]+org,[0, 0, 1],[1,1,1],1);
		R_PolygonVertex([-side1, side2, side3]+org,[0, 0, 1],[1,1,1],1);
	R_EndPolygon();
	
		R_PolygonVertex([-side1, side2, side3]+org,[0, 0, 1],[1,1,1],1);
		R_PolygonVertex([-side1, -side2, side3]+org,[0, 0, 1],[1,1,1],1);
		R_PolygonVertex([side1, -side2, side3]+org,[0, 0, 1],[1,1,1],1);
	R_EndPolygon();
}

void Render_Portal(float side, vector org,string shd)
{		
	local float z = 1.47;
	R_BeginPolygon(shd);
	// left(is front)
		R_PolygonVertex([-side,-side,side*z]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,side*z]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,-side*z]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,-side*z]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
}

void Render_Sky()
{		
	local string shd = "sky";
	local float side = 1048576*10;
	local float z = 10000;
	R_BeginPolygon(shd);
		R_PolygonVertex([side,-side,z],[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,z],[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,z],[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,z],[0,0,0],[1,1,1],1);
	R_EndPolygon();
}

void Render_Horizon()
{		
	local string shd = "horizon";
	local float side = 1048576*10;
	local float z = 10000;
	local vector org;
	makevectors(input_angles);
	org = camera.origin +(v_forward * 10000);
	// front
	R_BeginPolygon(shd);
		R_PolygonVertex([-side,side,side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,-side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// top

		R_PolygonVertex([side,-side,side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// right

		R_PolygonVertex([side,side,-side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([side,-side,side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([side,-side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// left

		R_PolygonVertex([-side,-side,side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,-side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// bottom

		R_PolygonVertex([side,-side,side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,-side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([side,-side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
	// back

		R_PolygonVertex([side,side,-side]+org,[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,-side,-side]+org,[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,-side]+org,[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,side,-side]+org,[0,0,0],[1,1,1],1);
	R_EndPolygon();
}

void Render_Sea()
{		
	local string shd = "sea";
	local float side = 1048576;
	local float z = 15;
	// front
	R_BeginPolygon(shd);
		R_PolygonVertex([side,-side,z],[0,1,0],[1,1,1],1);
		R_PolygonVertex([side,side,z],[1,1,0],[1,1,1],1);
		R_PolygonVertex([-side,side,z],[1,0,0],[1,1,1],1);
		R_PolygonVertex([-side,-side,z],[0,0,0],[1,1,1],1);
	R_EndPolygon();
}