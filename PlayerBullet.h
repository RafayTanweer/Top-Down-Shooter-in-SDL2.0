#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class PlayerBullet : public GameObject //Inheriting From Abstract GameObject Class
{

private:

	int frames = 0;

public:

	PlayerBullet();
	PlayerBullet(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);
	SDL_Rect* GetClip();

};



