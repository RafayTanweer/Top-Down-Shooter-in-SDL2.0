#include "ExplosionParticle.h"
//#include "GameObject.h"

//Constructor
ExplosionParticle::ExplosionParticle() {


}

//Constructor
ExplosionParticle::ExplosionParticle(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;

	this->isParticle = true;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 16;
	this->Rectangle->h = 16;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "Explosion.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

	SDL_SetTextureAlphaMod(ObjectTexture, Alpha);


}


//Defining the Pure Virtual Function of Move() in the inherited class
void ExplosionParticle::Move() {

	if (Alpha - 10 < 0)
		Alpha = 0;
	else
		Alpha = Alpha - 10;

	SDL_SetTextureAlphaMod(ObjectTexture, Alpha);

	this->x = this->x + ceil(10 * cos(AngleToMoveAt));
	this->y = this->y + ceil(10 * sin(AngleToMoveAt));


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

	if (Alpha == 0)
		this->alive = false;

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;



}

void ExplosionParticle::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}