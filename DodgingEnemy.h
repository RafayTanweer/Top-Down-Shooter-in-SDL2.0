#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class DodgingEnemy : public GameObject //Inheriting From Abstract GameObject Class
{

public:

	DodgingEnemy();
	DodgingEnemy(int x, int y, SDL_Renderer* gRenderer);
	void Render(SDL_Renderer* gRenderer);
	void Move();

};
