#include"TurretObject.h"

TurretObject::TurretObject() {
		
	this->alive = true;

}

TurretObject::TurretObject(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;

}

void TurretObject::Move() {

	this->TargetX = Target->GetRectangle()->x;
	this->TargetY = Target->GetRectangle()->y;
	this->Angle = atan2f(abs(TargetY - this->y), abs(TargetX - this->x));
	this->Degrees = 360.0 - (90.0 + (this->Angle * (180.0 / 3.14159)));
	if (TargetX > this->x)
		this->Degrees = -this->Degrees;

}

void TurretObject::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, this->Degrees, nullptr, SDL_FLIP_NONE);


}

void TurretObject::Shoot(vector<GameObject*>* EnemeyList, SDL_Renderer* gRenderer) {
	//Pure Virtual Function
}