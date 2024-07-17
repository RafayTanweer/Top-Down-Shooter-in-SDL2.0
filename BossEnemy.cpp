#include "BossEnemy.h"

BossEnemy::BossEnemy() {

}

BossEnemy::BossEnemy(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;
	this->Health = 3;
	this->EnemyType = 4;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 256;
	this->Rectangle->h = 256;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "Boss.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

	SpriteSheetClips[0] = new SDL_Rect();
	SpriteSheetClips[1] = new SDL_Rect();
	SpriteSheetClips[2] = new SDL_Rect();


	//Set sprite clips
	SpriteSheetClips[0]->x = 0;
	SpriteSheetClips[0]->y = 0;
	SpriteSheetClips[0]->w = 256;
	SpriteSheetClips[0]->h = 256;

	SpriteSheetClips[1]->x = 256;
	SpriteSheetClips[1]->y = 0;
	SpriteSheetClips[1]->w = 256;
	SpriteSheetClips[1]->h = 256;

	SpriteSheetClips[2]->x = 512;
	SpriteSheetClips[2]->y = 0;
	SpriteSheetClips[2]->w = 256;
	SpriteSheetClips[2]->h = 256;

	this->turretOne = new TurretOne(this->x + 5, this->y + this->Rectangle->h/2, gRenderer);
	this->turretTwo = new TurretTwo(this->x + this->Rectangle->w * 0.28, this->y + this->Rectangle->h / 2, gRenderer);
	this->turretThree = new TurretThree((this->x + this->Rectangle->w) - (this->Rectangle->w * 0.46), this->y + this->Rectangle->h / 2, gRenderer);
	this->turretFour = new TurretFour((this->x + this->Rectangle->w) - (this->Rectangle->w * 0.21), this->y + this->Rectangle->h / 2, gRenderer);
}

void BossEnemy::Move() {

	if (this->y < 0) {

		this->y = this->y + 16;
		this->Rectangle->y = this->y;
		if(this->turretOne != nullptr)
			this->turretOne->SetCoordinates(this->turretOne->GetRectangle()->x, this->y + this->Rectangle->h/2);
		if (this->turretTwo != nullptr)
			this->turretTwo->SetCoordinates(this->turretTwo->GetRectangle()->x, this->y + this->Rectangle->h / 2);
		if (this->turretThree != nullptr)
			this->turretThree->SetCoordinates(this->turretThree->GetRectangle()->x, this->y + this->Rectangle->h / 2);
		if (this->turretFour != nullptr)
			this->turretFour->SetCoordinates(this->turretFour->GetRectangle()->x, this->y + this->Rectangle->h / 2);
	}

}

void BossEnemy::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);
	if (turretOne != nullptr) {
		this->turretOne->Move();
		this->turretOne->Render(gRenderer);
	}
	if (turretTwo != nullptr) {
		this->turretTwo->Move();
		this->turretTwo->Render(gRenderer);
	}
	if (turretThree != nullptr) {
		this->turretThree->Move();
		this->turretThree->Render(gRenderer);
	}
	if (turretFour != nullptr) {
		this->turretFour->Move();
		this->turretFour->Render(gRenderer);
	}
	

}

void BossEnemy::SetTarget(GameObject* Target) {

	this->Target = Target;
	this->turretOne->SetTarget(Target);
	this->turretTwo->SetTarget(Target);
	this->turretThree->SetTarget(Target);
	this->turretFour->SetTarget(Target);


}

void BossEnemy::ShootTurretOne(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {

	this->turretOne->Shoot(EnemyList, gRenderer);

}

void BossEnemy::ShootTurretTwo(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {

	this->turretTwo->Shoot(EnemyList, gRenderer);

}

void BossEnemy::ShootTurretThree(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {

	this->turretThree->Shoot(EnemyList, gRenderer);

}

void BossEnemy::ShootTurretFour(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {

	this->turretFour->Shoot(EnemyList, gRenderer);

}

GameObject* BossEnemy::GetTurretOne() {

	return (GameObject*)this->turretOne;

}

GameObject* BossEnemy::GetTurretTwo() {

	return (GameObject*)this->turretTwo;

}

GameObject* BossEnemy::GetTurretThree() {

	return (GameObject*)this->turretThree;

}

GameObject* BossEnemy::GetTurretFour() {

	return (GameObject*)this->turretFour;

}

void BossEnemy::SetTurretOne(GameObject* turretOne) {

	this->turretOne = (TurretObject*) turretOne;

}

void BossEnemy::SetTurretTwo(GameObject* turretTwo) {

	this->turretTwo = (TurretObject*)turretTwo;

}

void BossEnemy::SetTurretThree(GameObject* turretThree) {

	this->turretThree = (TurretObject*)turretThree;

}

void BossEnemy::SetTurretFour(GameObject* turretFour) {

	this->turretFour = (TurretObject*)turretFour;

}

bool BossEnemy::TurretsIntact() {

	if (this->turretOne == nullptr && this->turretTwo == nullptr && this->turretThree == nullptr && this->turretFour == nullptr)
		return false;
	else
		return true;

}

SDL_Rect* BossEnemy::GetClip() {

	this->clip = SpriteSheetClips[frames / 3];
	frames++;
	if (frames / 3 == 3)
		frames = 0;

	return this->clip;

}