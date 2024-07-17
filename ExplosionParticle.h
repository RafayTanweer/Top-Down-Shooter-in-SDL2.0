#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class ExplosionParticle : public GameObject //Inheriting From Abstract GameObject Class
{

protected:

	Uint8 Alpha = 255;

public:

	ExplosionParticle();
	ExplosionParticle(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);

};
