#include "screen.h"
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#define endl '\n'
#define ll long long

int width=640*2,height=480*2;
int cx = width/2, cy=height/2;

// ********************************************** STANDERD DEFINATIONS **************************************************************

struct vec2
{
	float x,y;
};

struct vec3
{
	float x,y,z;
};


//************************************************* DRAWING FUNCTIONS *****************************************************************
void line(Screen& screen, float x1,float y1,float x2,float y2)
{
	float dx = x2-x1, dy=y2-y1;
	float len = sqrt(dx*dx + dy*dy);
	float ang = atan2(dy,dx);

	for(float r=0; r<len;r=r+0.01)
	{
		screen.pixel(x1+cos(ang)*r, y1+sin(ang)*r);
	}
}


vec3 vec_rotate(vec3& v, float alpha,float beta,float gamma)
{
	float a=(22*alpha)/(7*180);
	float b=(22*beta)/(7*180);
	float g=(22*gamma)/(7*180);

	vec3 vres;
	vres.x = (v.x)*(cos(b)*cos(g)) + (v.y)*(sin(a)*sin(b)*cos(g)-cos(a)*sin(g))+ (v.z)*(cos(a)*sin(b)*cos(g)+sin(a)*sin(g));
	vres.y = (v.x)*(cos(b)*sin(g)) + (v.y)*(sin(a)*sin(b)*sin(g)+cos(a)*cos(g)) + (v.z)*(cos(a)*sin(b)*sin(g)-sin(a)*cos(g));
	vres.z = (v.x)*(-sin(b)) + (v.y)*(sin(a)*cos(b)) + (v.z)*(cos(a)*cos(b));

	return vres;
}

vector<vec3> cube_rotate(vector<vec3>& c, float a,float b,float g)
{
	vector<vec3> res;
	for(auto A:c)
	{
		vec3 vi = vec_rotate(A,a,b,g);
		res.push_back(vi);
	}
	return res;
}

vec2 vec3_vec2(vec3&);
float x_pixel(vec2&);
float y_pixel(vec2&);

void draw_cube(Screen& screen,vector<vec3>& c)
{
	vector<vec2> temp;
	for(auto A:c)
	{
		vec2 vi = vec3_vec2(A);
		temp.push_back(vi);
	}
	for(auto it=temp.begin(); it!=temp.end()-1; it++)
	{
		auto v1 = *it, v2=*(it+1);
		line(screen,x_pixel(v1),y_pixel(v1),x_pixel(v2),y_pixel(v2));
	}
	line(screen,x_pixel(temp[0]),y_pixel(temp[0]),x_pixel(temp[3]),y_pixel(temp[3]));
	line(screen,x_pixel(temp[0]),y_pixel(temp[0]),x_pixel(temp[5]),y_pixel(temp[5]));
	line(screen,x_pixel(temp[7]),y_pixel(temp[7]),x_pixel(temp[4]),y_pixel(temp[4]));
	line(screen,x_pixel(temp[7]),y_pixel(temp[7]),x_pixel(temp[2]),y_pixel(temp[2]));
	line(screen,x_pixel(temp[1]),y_pixel(temp[1]),x_pixel(temp[6]),y_pixel(temp[6]));
}

//********************************************** VECTOR TRANSFORMATION ****************************************************************

vec2 vec3_vec2(vec3& v)
{
	vec2 vres;
	vres.x= v.x - (v.z)/(sqrt(2));
	vres.y= v.y - (v.z)/(sqrt(2));
	return vres;
}

float x_pixel(vec2& v)
{
	return (cx+v.x);
}

float y_pixel(vec2& v)
{
	return (cy-v.y);
}



int main(){
	Screen screen(width,height);	
	
	vector<vec3> cube3 = {{100,100,100},{190,100,100},{190,190,100},{100,190,100},{100,190,190},{100,100,190},{190,100,190},{190,190,190}};
	vec3 A{100,100,100};
	float a=0,b=0,g=0;

	// RANDOM PATTERN FORMATION/PATH OF ROTATING VECTOR
	while(true)
	{
		vec3 vres = vec_rotate(A,a,b,g);
		vec2 vi = vec3_vec2(vres);
		screen.pixel(x_pixel(vi),y_pixel(vi));
		a+=0.6;b+=0.7;g+=0.8;
		screen.show();
		screen.input();
	}

	// ROTATING CUBE
	/* while(true) */
	/* { */
	/* 	vector<vec3> res = cube_rotate(cube3,a,b,g); */
	/* 	a+=0.4; */
	/* 	b+=0.6; */
	/* 	g+=0.9; */
	/* 	draw_cube(screen, res); */
	/* 	screen.show(); */
	/* 	screen.clear(); */
	/* 	screen.input(); */
	/* } */
	
}

