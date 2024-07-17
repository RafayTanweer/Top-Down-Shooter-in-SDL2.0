#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class LaserBullet : public GameObject //Inheriting From Abstract GameObject Class
{

protected:

	int frames = 0;
	bool RotationSet = false;
	double Degrees = 0.0;

public:

	LaserBullet();
	LaserBullet(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);
	SDL_Rect* GetClip();

};
