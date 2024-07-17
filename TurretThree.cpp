#include "TurretThree.h"

TurretThree::TurretThree() {


}

TurretThree::TurretThree(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;
	this->BulletSpeed = 12;
	this->Health = 5;
	this->EnemyType = 3;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 52;
	this->Rectangle->h = 64;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "Turret2.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());



}

void TurretThree::Shoot(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {

	GameObject* laser = new LaserBullet(this->x + this->Rectangle->w / 4, this->y + this->Rectangle->h / 2, gRenderer);
	GameObject* laser1 = new LaserBullet(this->x + this->Rectangle->w / 4, this->y + this->Rectangle->h / 2, gRenderer);
	GameObject* laser2 = new LaserBullet(this->x + this->Rectangle->w / 4, this->y + this->Rectangle->h / 2, gRenderer);
	this->TargetX = Target->GetRectangle()->x;
	this->TargetY = Target->GetRectangle()->y;
	AngleToFire = atan2f((TargetY - laser->GetRectangle()->y), (TargetX - laser->GetRectangle()->x));

	laser->setAngle(AngleToFire);
	laser->SetSpeed(this->BulletSpeed);
	EnemyList->emplace_back(laser);

	if(AngleToFire < 0)
		laser1->setAngle(AngleToFire + 0.174533);
	else
		laser1->setAngle(AngleToFire - 0.174533);
	laser1->SetSpeed(this->BulletSpeed);
	EnemyList->emplace_back(laser1);

	if (AngleToFire < 0)
		laser2->setAngle(AngleToFire - 0.174533);
	else
		laser2->setAngle(AngleToFire + 0.174533);
	laser2->SetSpeed(this->BulletSpeed);
	EnemyList->emplace_back(laser2);


}