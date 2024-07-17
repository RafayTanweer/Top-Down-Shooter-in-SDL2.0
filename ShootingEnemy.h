#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class ShootingEnemy : public GameObject //Inheriting From Abstract GameObject Class
{

public:

	ShootingEnemy();
	ShootingEnemy(int x, int y, SDL_Renderer* gRenderer);
	void Render(SDL_Renderer* gRenderer);
	void Move();

};
