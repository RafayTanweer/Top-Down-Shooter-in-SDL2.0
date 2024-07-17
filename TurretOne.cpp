#include "TurretOne.h"

TurretOne::TurretOne() {


}

TurretOne::TurretOne(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;
	this->BulletSpeed = 12;
	this->Health = 3;
	this->EnemyType = 3;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 58;
	this->Rectangle->h = 64;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "Turret3.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());



}

void TurretOne::Shoot(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {

	GameObject* Bullet = new ShootingEnemyBullet(this->x + this->Rectangle->w / 2, this->y + this->Rectangle->h / 2, gRenderer);
	Bullet->SetTarget(this->Target);
	Bullet->SetSpeed(this->BulletSpeed);
	EnemyList->emplace_back(Bullet);

	/*GameObject* laser = new LaserBullet(this->x + this->Rectangle->w / 4, this->y + this->Rectangle->h / 2, gRenderer);
	this->TargetX = Target->GetRectangle()->x;
	this->TargetY = Target->GetRectangle()->y;
	laser->setAngle(atan2f((TargetY - laser->GetRectangle()->y), (TargetX - laser->GetRectangle()->x)));
	laser->SetSpeed(this->BulletSpeed);
	EnemyList->emplace_back(laser);*/


}