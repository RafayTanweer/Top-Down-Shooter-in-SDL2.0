#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Player : public GameObject //Inheriting From Abstract GameObject Class
{

public:

	Player();
	Player(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);

};
