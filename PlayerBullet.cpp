#include "PlayerBullet.h"
//#include "GameObject.h"

//Constructor
PlayerBullet::PlayerBullet() {


}

//Constructor
PlayerBullet::PlayerBullet(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 16;
	this->Rectangle->h = 16;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "PlayerBullet.png";

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
void PlayerBullet::Move() {

	y -= 20;

	if (y < 0) {
		this->alive = false;
	}

	this->Rectangle->y = this->y;


}

SDL_Rect* PlayerBullet::GetClip() {

	SDL_Rect* Clip = SpriteSheetClips[frames / 3];
	frames++;
	if (frames / 3 == 3)
		frames = 0;

	return Clip;

}

void PlayerBullet::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}