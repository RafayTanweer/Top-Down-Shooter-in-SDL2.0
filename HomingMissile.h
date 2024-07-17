#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class HomingMissile : public GameObject //Inheriting From Abstract GameObject Class
{

private:

	float AngleToRotate = 0.0;
	double Degrees = 0.0;
	int Sx = 0;
	int Sy = 0;
	int px = 0;
	int py = 0;
	int centreX = 0;
	int centreY = 0;
	Uint8 Alpha = 255;

public:

	HomingMissile();
	HomingMissile(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);
	void RenderSmoke(SDL_Renderer* gRenderer);

};
