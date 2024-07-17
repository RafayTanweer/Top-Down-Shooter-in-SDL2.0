#include "ShootingEnemyBullet.h"
//#include "GameObject.h"

//Constructor
ShootingEnemyBullet::ShootingEnemyBullet() {


}

//Constructor
ShootingEnemyBullet::ShootingEnemyBullet(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;
	this->Speed = 10;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 16;
	this->Rectangle->h = 16;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "EnemyBullet2.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == nullptr)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

	SpriteSheetClips[0] = new SDL_Rect();
	SpriteSheetClips[1] = new SDL_Rect();
	SpriteSheetClips[2] = new SDL_Rect();


	//Set sprite clips
	SpriteSheetClips[0]->x = 0;
	SpriteSheetClips[0]->y = 0;
	SpriteSheetClips[0]->w = 16;
	SpriteSheetClips[0]->h = 16;

	SpriteSheetClips[1]->x = 16;
	SpriteSheetClips[1]->y = 0;
	SpriteSheetClips[1]->w = 16;
	SpriteSheetClips[1]->h = 16;

	SpriteSheetClips[2]->x = 32;
	SpriteSheetClips[2]->y = 0;
	SpriteSheetClips[2]->w = 16;
	SpriteSheetClips[2]->h = 16;


}


//Defining the Pure Virtual Function of Move() in the inherited class
void ShootingEnemyBullet::Move() {

	if (!this->RotationSet) {

		this->TargetX = Target->GetRectangle()->x;
		this->TargetY = Target->GetRectangle()->y;
		this->Angle = atan2f(abs(TargetY - this->y), abs(TargetX - this->x));
		this->Degrees = 180.0 - (90.0 + (this->Angle * (180.0 / 3.14159)));
		if(TargetX > this->x)
			this->Degrees = -this->Degrees;
		
		this->InitialX = this->x;
		
		this->RotationSet = true;

	}

	if (TargetX > this->InitialX)
		this->x = this->x + ceil(Speed * cos(Angle));
	else
		this->x = this->x - ceil(Speed * cos(Angle));

	this->y = this->y + ceil(Speed * sin(Angle));

	if (x < 0 || x > 884)
		this->alive = false;

	if (y > 784) {
		this->alive = false;
	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;


}

SDL_Rect* ShootingEnemyBullet::GetClip() {

	this->clip = SpriteSheetClips[frames / 3];
	frames++;
	if (frames / 3 == 3)
		frames = 0;

	return this->clip;

}

void ShootingEnemyBullet::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, this->Degrees, nullptr, SDL_FLIP_NONE);

}