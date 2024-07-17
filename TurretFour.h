#pragma once

#include<iostream>
#include <stdlib.h> 
#include "TurretObject.h"

using namespace std;

class TurretFour : public TurretObject {

protected:

	float AngleToFire = 0.0;

public:

	TurretFour();
	TurretFour(int x, int y, SDL_Renderer* gRenderer);
	void Shoot(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);

};
