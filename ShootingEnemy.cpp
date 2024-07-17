#include "ShootingEnemy.h"
//#include "GameObject.h"

//Constructor
ShootingEnemy::ShootingEnemy() {


}

//Constructor
ShootingEnemy::ShootingEnemy(int x, int y, SDL_Renderer* gRenderer) {

	this->EnemyType = 1;

	this->Health = 3;

	this->alive = true;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 64;
	this->Rectangle->h = 64;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "EnemyShip1.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());


}


//Defining the Pure Virtual Function of Move() in the inherited class
void ShootingEnemy::Move() {

	y += (int)ty;
	ty *= friction;

	if ((int)ty == 0) {
		ty = 20.0;
	}

	if (y > 736)
		this->alive = false;

	this->Rectangle->y = this->y;

}

void ShootingEnemy::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}