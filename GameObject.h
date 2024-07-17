#pragma once

#include<iostream>
#include <stdlib.h> 
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <vector>

using namespace std;

//Abstract Class For GameObject
class GameObject {

protected:

	SDL_Texture* ObjectTexture = nullptr;
	SDL_Texture* SmokeTexture = nullptr;
	vector<SDL_Rect*> SmokeRects;
	SDL_Rect* Rectangle = nullptr;
	SDL_Rect* SpriteSheetClips[3] = { nullptr, nullptr, nullptr };
	SDL_Rect* clip = nullptr;
	string path;
	bool alive;
	float tx = 0.0;
	float ty = 0.0;
	float friction = 0.5;
	bool HasPowerUp = false;
	bool TargetAcquired = false;
	GameObject* Target = nullptr;
	int x = 0;
	int y = 0;
	int EnemyType = 0; //1 for Shooting Enemy, 2 for Dodging Enemy, 3 for Turrets, 4 for Boss
	int Health = 0;
	bool DodgeEnabled = false;
	bool hasSmoke = false;
	bool isParticle = false;
	float AngleToMoveAt = 0.0;
	int Speed = 0;

public:

	GameObject();
	GameObject(int x, int y, SDL_Renderer* gRenderer);
	~GameObject();
	//SDL_Texture* Art();
	SDL_Rect* GetRectangle();
	virtual void Render(SDL_Renderer* gRenderer) = 0;
	virtual void Move() = 0; //Pure Virtual Function For Movement
	bool Alive();
	void ChangeAliveStatus(bool alive);
	void Translate(int x, int y);
	bool GetPowerUpStatus();
	void SetPowerUpStatus(bool PU);
	virtual void SetTarget(GameObject* Target);
	GameObject* GetTarget();
	void SetTargetAcquired(bool Status);
	virtual SDL_Rect* GetClip();
	void Dodge();
	int GetEnemyType();
	bool GetDodgeStatus();
	void SetDodgeStatus(bool status);
	int GetHealth();
	void DecHealth();
	virtual void RenderSmoke(SDL_Renderer* gRenderer);
	bool GetSmokeStatus();
	void setAngle(float Angle);
	bool IsParticle();
	void SetSpeed(int Speed);
	virtual void ShootTurretOne(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	virtual void ShootTurretTwo(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	virtual void ShootTurretThree(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	virtual void ShootTurretFour(vector<GameObject*>* EnemyList, SDL_Renderer* gRenderer);
	virtual GameObject* GetTurretOne();
	virtual GameObject* GetTurretTwo();
	virtual GameObject* GetTurretThree();
	virtual GameObject* GetTurretFour();
	virtual void SetTurretOne(GameObject* turretOne);
	virtual void SetTurretTwo(GameObject* turretTwo);
	virtual void SetTurretThree(GameObject* turretThree);
	virtual void SetTurretFour(GameObject* turretFour);
	virtual bool TurretsIntact();
	void SetCoordinates(int x, int y);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	


};
