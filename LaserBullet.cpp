#include "LaserBullet.h"
//#include "GameObject.h"

//Constructor
LaserBullet::LaserBullet() {


}

//Constructor
LaserBullet::LaserBullet(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;

	this->isParticle = true;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 16;
	this->Rectangle->h = 16;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "Laser.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

	SpriteSheetClips[0] = new SDL_Rect();
	SpriteSheetClips[1] = new SDL_Rect();
	SpriteSheetClips[2] = new SDL_Rect();


	//Set sprite clips
	SpriteSheetClips[0]->x = 0;
	SpriteSheetClips[0]->y = 0;
	SpriteSheetClips[0]->w = 32;
	SpriteSheetClips[0]->h = 16;

	SpriteSheetClips[1]->x = 32;
	SpriteSheetClips[1]->y = 0;
	SpriteSheetClips[1]->w = 32;
	SpriteSheetClips[1]->h = 16;

	SpriteSheetClips[2]->x = 64;
	SpriteSheetClips[2]->y = 0;
	SpriteSheetClips[2]->w = 32;
	SpriteSheetClips[2]->h = 16;



}


//Defining the Pure Virtual Function of Move() in the inherited class
void LaserBullet::Move() {

	if (!RotationSet) {

		if(this->AngleToMoveAt < 0)
			this->Degrees = 270 + (180 - (90.0 + (this->AngleToMoveAt * (180.0 / 3.14159))));
		else
			this->Degrees = -(90 + (180 - (90.0 + (this->AngleToMoveAt * (180.0 / 3.14159)))));

		RotationSet = true;

	}

	this->x = this->x + ceil(Speed * cos(AngleToMoveAt));
	this->y = this->y + ceil(Speed * sin(AngleToMoveAt));


	if (x < 0) {
		this->alive = false;
	}
	else if (x > 836) {
		this->alive = false;
	}

	if (y < 0) {
		this->alive = false;
	}
	else if (y > 736) {
		this->alive = false;
	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;



}

void LaserBullet::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, this->Degrees, nullptr, SDL_FLIP_NONE);

}

SDL_Rect* LaserBullet::GetClip() {

	this->clip = SpriteSheetClips[frames / 3];
	frames++;
	if (frames / 3 == 3)
		frames = 0;

	return this->clip;

}