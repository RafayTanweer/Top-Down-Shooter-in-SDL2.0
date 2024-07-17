#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class ShootingEnemyBullet : public GameObject //Inheriting From Abstract GameObject Class
{

private:

	int frames = 0;
	bool RotationSet = false;
	int InitialX = 0;
	float Angle = 0.0;
	int TargetX = 0;
	int TargetY = 0;
	double Degrees = 0.0;

public:

	ShootingEnemyBullet();
	ShootingEnemyBullet(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);
	SDL_Rect* GetClip();

};
