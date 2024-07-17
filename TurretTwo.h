#pragma once

#include<iostream>
#include <stdlib.h> 
#include "TurretObject.h"

using namespace std;

class TurretTwo : public TurretObject {

public:

	TurretTwo();
	TurretTwo(int x, int y, SDL_Renderer* gRenderer);
	void Shoot(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);

};
