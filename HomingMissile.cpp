#include "HomingMissile.h"
//#include "GameObject.h"

//Constructor
HomingMissile::HomingMissile() {


}

//Constructor
HomingMissile::HomingMissile(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;
	this->hasSmoke = true;

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 32;
	this->Rectangle->h = 32;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = "PlayerMissile2.png";

	this->ObjectTexture = IMG_LoadTexture(gRenderer, path.c_str());

	if (ObjectTexture == nullptr)
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

	this->SmokeTexture = IMG_LoadTexture(gRenderer, "Smoke.png");

	if (SmokeTexture == nullptr)
		printf("Unable to create texture from %s! SDL Error: %s\n", "Smoke.png", SDL_GetError());

	
}


//Defining the Pure Virtual Function of Move() in the inherited class
void HomingMissile::Move() {

	if (this->TargetAcquired == false) {

		y -= 15;
		Sx = px = this->Rectangle->x + 12;
		Sy = py = this->Rectangle->y + this->Rectangle->h;

	}
	else {

		if (this->Target != nullptr) {

			centreX = this->Rectangle->x + this->Rectangle->w / 2;
			centreY = this->Rectangle->y + this->Rectangle->h / 2;

			Sx = px = this->Rectangle->x + 12;
			Sy = py = this->Rectangle->y + this->Rectangle->h;

			Sx = ((px - centreX) * cos(-(this->Degrees * 3.14159 / 180))) - ((py - centreY) * sin(-(this->Degrees * 3.14159 / 180))) + centreX;
			Sy = ((px - centreX) * sin(-(this->Degrees * 3.14159 / 180))) - ((py - centreY) * cos(-(this->Degrees * 3.14159 / 180))) + centreY;

			AngleToRotate = atan2f(abs(Target->GetRectangle()->y - this->y), abs(Target->GetRectangle()->x - this->x));

			if (Target->GetRectangle()->x > this->x) {

				this->x = this->x + ceil(25 * cos(AngleToRotate));

				if (Target->GetRectangle()->y > this->y) {

					this->y = this->y + ceil(25 * sin(AngleToRotate));				
					this->Degrees = 90.0 + (this->AngleToRotate * (180.0 / 3.14159));

				}
				else {

					this->y = this->y - ceil(25 * sin(AngleToRotate));
					this->Degrees = 90.0 - (this->AngleToRotate * (180.0 / 3.14159));

				}

			}
			else {

				this->x = this->x - ceil(25 * cos(AngleToRotate));

				if (Target->GetRectangle()->y > this->y) {

					this->y = this->y + ceil(25 * sin(AngleToRotate));
					this->Degrees = -(90.0 + (this->AngleToRotate * (180.0 / 3.14159)));

				}
				else {

					this->y = this->y - ceil(25 * sin(AngleToRotate));
					this->Degrees = -(90.0 - (this->AngleToRotate * (180.0 / 3.14159)));

				}

			}


		}
		else {

			y += 15;
			Sx = px = this->Rectangle->x + 12;
			Sy = py = this->Rectangle->y;
		}

	}
	

	if (x < 0 || x > 884)
		this->alive = false;

	if (y < 0 || y > 784) {
		this->alive = false;
	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;

	if (this->alive) {

		SDL_Rect* newRect = new SDL_Rect();
		newRect->x = Sx;
		newRect->y = Sy;
		newRect->w = 8;
		newRect->h = 8;
		SmokeRects.emplace_back(newRect);


	}

}

void HomingMissile::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, this->Degrees, nullptr, SDL_FLIP_NONE);

}

void HomingMissile::RenderSmoke(SDL_Renderer* gRenderer) {

	Alpha = 255;

	for (int i = SmokeRects.size() - 1; i >= 0; i--) {

		SDL_RenderCopy(gRenderer, this->SmokeTexture, nullptr, SmokeRects.at(i));

		if (Alpha - 20 < 0)
			Alpha = 0;
		else
			Alpha = Alpha - 20;

		SDL_SetTextureAlphaMod(SmokeTexture, Alpha);

	}


}