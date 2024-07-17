#include "TurretTwo.h"

TurretTwo::TurretTwo() {


}

TurretTwo::TurretTwo(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;
	this->BulletSpeed = 15;
	this->Health = 3;
	this->EnemyType = 3;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 52;
	this->Rectangle->h = 64;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "Turret1.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());



}

void TurretTwo::Shoot(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {

	GameObject* laser = new LaserBullet(this->x + this->Rectangle->w / 4, this->y + this->Rectangle->h / 2, gRenderer);
	this->TargetX = Target->GetRectangle()->x;
	this->TargetY = Target->GetRectangle()->y;
	laser->setAngle(atan2f((TargetY - laser->GetRectangle()->y), (TargetX - laser->GetRectangle()->x)));
	laser->SetSpeed(this->BulletSpeed);
	EnemyList->emplace_back(laser);


}