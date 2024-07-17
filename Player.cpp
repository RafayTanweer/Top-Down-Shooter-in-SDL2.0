#include "Player.h"
//#include "GameObject.h"

//Constructor
Player::Player() {


}

//Constructor
Player::Player(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 64;
	this->Rectangle->h = 64;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "Ship.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if(ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	

}


//Defining the Pure Virtual Function of Move() in the inherited class
void Player::Move() {

		x += (int)tx;
		y += (int)ty;
		

		if (x < 0) {
			x = 0;
		}
		else if (x > 836) {
			x = 836;
		}

		if (y < 260) {
			y = 260;
		}
		else if (y > 736) {
			y = 736;
		}

		tx *= friction;
		ty *= friction;

		this->Rectangle->x = this->x;
		this->Rectangle->y = this->y;
		


}

void Player::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
