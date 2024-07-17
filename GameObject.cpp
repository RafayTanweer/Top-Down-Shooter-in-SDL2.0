#include "GameObject.h"

//Constructor
GameObject::GameObject() {

	this->alive = true;
	
}

//Constructor
GameObject::GameObject(int x, int y, SDL_Renderer* gRenderer) {

	this->alive = true;

}

GameObject::~GameObject() {

	SDL_DestroyTexture(this->ObjectTexture);
	ObjectTexture = nullptr;
	
	for (int i = 0; i < 3; i++) {

		if (this->SpriteSheetClips[i] != nullptr) {

			delete this->SpriteSheetClips[i];
			this->SpriteSheetClips[i] = nullptr;

		}

	}

	SDL_DestroyTexture(this->SmokeTexture);
	SmokeTexture = nullptr;

	for (int i = 0; i < SmokeRects.size(); i++) {

		delete SmokeRects.at(i);
		SmokeRects.erase(SmokeRects.begin() + i);

	}

}

/*SDL_Texture* GameObject::Art() {

	return this->ObjectTexture;

}*/

SDL_Rect* GameObject::GetRectangle() {

	return this->Rectangle;

}

void GameObject::Move() {
	//Pure Virtual Function for Movement
}

SDL_Rect* GameObject::GetClip() {

	//Virtual Function for Getting The Clip Of the Sprite Sheet
	return nullptr;

}


//Function for returning the status of alive
bool GameObject::Alive() {

	return this->alive;

}

//Function for changing the alive status
void GameObject::ChangeAliveStatus(bool alive) {

	this->alive = alive;

}

void GameObject::Translate(int x, int y) {

	this->tx = x;
	this->ty = y;


}

bool GameObject::GetPowerUpStatus() {

	return this->HasPowerUp;

}

void GameObject::SetPowerUpStatus(bool PU) {

	this->HasPowerUp = PU;

}

void GameObject::SetTarget(GameObject* Target) {

	this->Target = Target;
	

}

GameObject* GameObject::GetTarget() {

	return this->Target;

}

void GameObject::SetTargetAcquired(bool Status) {

	this->TargetAcquired = Status;

}

void GameObject::Dodge() {

	x += (int)tx;
	tx *= friction;

	if ((int)tx == 0) {
		this->DodgeEnabled = false;
		this->Translate(0, 18);
	}

	this->Rectangle->x = this->x;
}

int GameObject::GetEnemyType() {

	return this->EnemyType;

}

bool GameObject::GetDodgeStatus() {

	return this->DodgeEnabled;

}

void GameObject::SetDodgeStatus(bool status) {

	this->DodgeEnabled = status;

}

int GameObject::GetHealth() {

	return this->Health;

}

void GameObject::DecHealth() {

	this->Health--;

}

void GameObject::RenderSmoke(SDL_Renderer* gRenderer) {
	


}

bool GameObject::GetSmokeStatus() {

	return this->hasSmoke;

}

void GameObject::setAngle(float Angle) {


	this->AngleToMoveAt = Angle;


}

bool GameObject::IsParticle() {


	return this->isParticle;


}

void GameObject::SetSpeed(int Speed) {

	this->Speed = Speed;

}

void GameObject::ShootTurretOne(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {


}

void GameObject::ShootTurretTwo(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {


}

void GameObject::ShootTurretThree(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {


}

void GameObject::ShootTurretFour(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer) {


}

GameObject* GameObject::GetTurretOne() {

	return nullptr;

}

GameObject* GameObject::GetTurretTwo() {

	return nullptr;

}

GameObject* GameObject::GetTurretThree() {

	return nullptr;

}

GameObject* GameObject::GetTurretFour() {

	return nullptr;

}

void GameObject::SetTurretOne(GameObject* turretOne) {
		
	
}

void GameObject::SetTurretTwo(GameObject* turretTwo) {


}

void GameObject::SetTurretThree(GameObject* turretThree) {


}

void GameObject::SetTurretFour(GameObject* turretFour) {


}

bool GameObject::TurretsIntact() {

	return true;

}

void GameObject::SetCoordinates(int x, int y) {

	this->Rectangle->x = x;
	this->Rectangle->y = y;
	this->x = x;
	this->y = y;

}

void GameObject::SetColor(Uint8 r, Uint8 g, Uint8 b) {

	SDL_SetTextureColorMod(this->ObjectTexture, r, g, b);

}