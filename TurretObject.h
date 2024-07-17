#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"
#include "ShootingEnemyBullet.h"
#include "LaserBullet.h"

using namespace std;

class TurretObject : public GameObject //Inheriting From Abstract GameObject Class
{

protected:

	float Angle = 0.0;
	double Degrees = 0.0;
	int BulletSpeed = 0;
	int TargetX = 0;
	int TargetY = 0;

public:

	TurretObject();
	TurretObject(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);
	virtual void Shoot(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) = 0;

};
