#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"
#include "TurretOne.h"
#include "TurretTwo.h"
#include "TurretThree.h"
#include "TurretFour.h"

using namespace std;

class BossEnemy : public GameObject {

protected:

	int frames = 0;
	TurretObject* turretOne = nullptr;
	TurretObject* turretTwo = nullptr;
	TurretObject* turretThree = nullptr;
	TurretObject* turretFour = nullptr;

public:

	BossEnemy();
	BossEnemy(int x, int y, SDL_Renderer* gRenderer);
	void Move();
	void Render(SDL_Renderer* gRenderer);
	void SetTarget(GameObject* Target);
	void ShootTurretOne(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	void ShootTurretTwo(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	void ShootTurretThree(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	void ShootTurretFour(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	GameObject* GetTurretOne();
	GameObject* GetTurretTwo();
	GameObject* GetTurretThree();
	GameObject* GetTurretFour();
	void SetTurretOne(GameObject* turretOne);
	void SetTurretTwo(GameObject* turretTwo);
	void SetTurretThree(GameObject* turretThree);
	void SetTurretFour(GameObject* turretFour);
	bool TurretsIntact();
	SDL_Rect* GetClip();

};
