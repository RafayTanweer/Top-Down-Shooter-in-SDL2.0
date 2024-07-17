#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <stdlib.h> 
#include <string>
//#include <SDL.h>
//#include <SDL_image.h>
#include<iostream>
#include"Player.h"
#include"PlayerBullet.h"
#include"ShootingEnemy.h"
#include"ShootingEnemyBullet.h"
#include"DodgingEnemy.h"
#include"DodgingEnemyBullet.h"
#include"HomingMissile.h"
#include"ExplosionParticle.h"
#include"BossEnemy.h"
#include"SDL_ttf.h"
#include"SDL_mixer.h"
#include <vector>

using namespace std;

const int nScreenWidth = 900;
const int nScreenHeight = 800;

//Starting SDL, creating window, renderer etc
bool innit();

//Deallocation of memory and closing SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

TTF_Font* gFont = nullptr;


bool innit() {

    bool success = true;

    //Create window
    gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, nScreenWidth, nScreenHeight, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create renderer for window
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gRenderer == nullptr)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 135, 136, 156, 0xFF);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }

            //Initialize SDL_ttf
            if (TTF_Init() == -1)
            {
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                success = false;
            }

            gFont = TTF_OpenFont("Antonio-Bold.ttf", 25);
            if (gFont == NULL)
            {
                printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                success = false;
            }

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            }

        }

    }

    return success;

}

void close()
{
    //Destroy renderer and window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    TTF_CloseFont(gFont);
    gFont = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main() {

    if (!innit()) {

        printf("Failed to initialize!\n");

    }
    else {

        bool Selection = false;
        bool PlayGame = false;

        SDL_Color ButtonColor = { 255, 255, 255 };

        string PlayText = ".....Play Game.....";
        //string ExitText = "Exit";

        SDL_Rect* PlayRect = new SDL_Rect();

        SDL_Surface* PlaySurface = TTF_RenderText_Solid(gFont, PlayText.c_str(), ButtonColor);
        //SDL_Surface* ExitSurface = TTF_RenderText_Solid(gFont, ExitText.c_str(), ButtonColor);

        SDL_Texture* PlayTexture = SDL_CreateTextureFromSurface(gRenderer, PlaySurface);
        //SDL_Texture* ExitTexture = SDL_CreateTextureFromSurface(gRenderer, ExitSurface);

        SDL_FreeSurface(PlaySurface);
        //SDL_FreeSurface(ExitSurface);

        SDL_Texture* ButtonTexture = IMG_LoadTexture(gRenderer, "Button.png");

        if (ButtonTexture == nullptr)
            printf("Unable to create texture from %s! SDL Error: %s\n", "Button.png", SDL_GetError());

        SDL_Rect* ButtonRect = new SDL_Rect();

        SDL_Rect* ButtonSpriteSheetClips[3] = { nullptr, nullptr, nullptr };

        ButtonSpriteSheetClips[0] = new SDL_Rect();
        ButtonSpriteSheetClips[1] = new SDL_Rect();
        ButtonSpriteSheetClips[2] = new SDL_Rect();


        //Set sprite clips
        ButtonSpriteSheetClips[0]->x = 0;
        ButtonSpriteSheetClips[0]->y = 0;
        ButtonSpriteSheetClips[0]->w = 64;
        ButtonSpriteSheetClips[0]->h = 64;

        ButtonSpriteSheetClips[1]->x = 64;
        ButtonSpriteSheetClips[1]->y = 0;
        ButtonSpriteSheetClips[1]->w = 64;
        ButtonSpriteSheetClips[1]->h = 64;

        ButtonSpriteSheetClips[2]->x = 128;
        ButtonSpriteSheetClips[2]->y = 0;
        ButtonSpriteSheetClips[2]->w = 64;
        ButtonSpriteSheetClips[2]->h = 64;

        int width = 0;
        int height = 0;

        SDL_QueryTexture(PlayTexture, nullptr, nullptr, &width, &height);

        int cols = ceil(width / 64.0);
        int rows = ceil(height / 64.0);

        ButtonRect->w = 64;
        ButtonRect->h = 64;

        SDL_Event MenuEvent;

        while (!Selection) {

            while (SDL_PollEvent(&MenuEvent) != 0)
            {
                //User requests quit
                if (MenuEvent.type == SDL_QUIT)
                {
                    PlayGame = false;
                    Selection = true;
                }
                //User presses a key
                else if (MenuEvent.type == SDL_KEYDOWN)
                {
                    //Select surfaces based on key press
                    switch (MenuEvent.key.keysym.sym)
                    {
                    case SDLK_p:
                        PlayGame = true;
                        Selection = true;
                        break;

                    }

                }
                else if (MenuEvent.type == SDL_MOUSEBUTTONUP)//Inc Dec rows or columns based on mouse presses
                {
                    //Get mouse position
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    if ((x >= PlayRect->x && x <= PlayRect->x + PlayRect->w) && (y >= PlayRect->y && y <= PlayRect->y + PlayRect->h)) {

                        PlayGame = true;
                        Selection = true;
                        break;


                    }

                }

            }

            //Clear screen
            SDL_RenderClear(gRenderer);

            ButtonRect->x = (nScreenWidth - 64 * cols) / 2;
            ButtonRect->y = (nScreenHeight - 64 * (rows + 1)) / 2;

            for (int i = 0; i < cols; i++) {

                if (i == 0)
                    SDL_RenderCopy(gRenderer, ButtonTexture, ButtonSpriteSheetClips[0], ButtonRect);
                else if(i == cols - 1)
                    SDL_RenderCopyEx(gRenderer, ButtonTexture, ButtonSpriteSheetClips[0], ButtonRect, 90.0, nullptr, SDL_FLIP_NONE);
                else
                    SDL_RenderCopy(gRenderer, ButtonTexture, ButtonSpriteSheetClips[1], ButtonRect);

                ButtonRect->x = ButtonRect->x + 64;

            }

            for (int i = 1; i < rows - 1; i++) {

                ButtonRect->x = (nScreenWidth - 64 * cols) / 2;
                ButtonRect->y = ButtonRect->y + 64;

                for (int j = 0; j < cols; j++) {

                    if (j == 0)
                        SDL_RenderCopyEx(gRenderer, ButtonTexture, ButtonSpriteSheetClips[1], ButtonRect, -90.0, nullptr, SDL_FLIP_NONE);
                    else if (j == cols - 1)
                        SDL_RenderCopyEx(gRenderer, ButtonTexture, ButtonSpriteSheetClips[1], ButtonRect, 90.0, nullptr, SDL_FLIP_NONE);
                    else
                        SDL_RenderCopy(gRenderer, ButtonTexture, ButtonSpriteSheetClips[2], ButtonRect);

                    ButtonRect->x = ButtonRect->x + 64;


                }

            }

            ButtonRect->x = (nScreenWidth - 64 * cols) / 2;
            ButtonRect->y = ButtonRect->y + 64;

            for (int i = 0; i < cols; i++) {

                if (i == 0)
                    SDL_RenderCopyEx(gRenderer, ButtonTexture, ButtonSpriteSheetClips[0], ButtonRect, 270.0, nullptr, SDL_FLIP_NONE);
                else if (i == cols - 1)
                    SDL_RenderCopyEx(gRenderer, ButtonTexture, ButtonSpriteSheetClips[0], ButtonRect, 180.0, nullptr, SDL_FLIP_NONE);
                else
                    SDL_RenderCopyEx(gRenderer, ButtonTexture, ButtonSpriteSheetClips[1], ButtonRect, 180.0, nullptr, SDL_FLIP_NONE);

                ButtonRect->x = ButtonRect->x + 64;


            }

            TTF_SizeText(gFont, PlayText.c_str(), &PlayRect->w, &PlayRect->h);
            PlayRect->x = (nScreenWidth - 64 * cols) / 2 + (64 * cols - PlayRect->w)/2;
            PlayRect->y = (nScreenHeight - 64 * (rows +1)) / 2 + (64*(rows + 1) - PlayRect->h)/2;

            SDL_RenderCopy(gRenderer, PlayTexture, nullptr, PlayRect);

            //Update screen
            SDL_RenderPresent(gRenderer);


        }

        SDL_DestroyTexture(PlayTexture);
        PlayTexture = nullptr;

        SDL_DestroyTexture(ButtonTexture);
        ButtonTexture = nullptr;

        for (int i = 0; i < 3; i++) {

            delete ButtonSpriteSheetClips[i];
            ButtonSpriteSheetClips[i] = nullptr;

        }

        delete PlayRect;
        PlayRect = nullptr;

        delete ButtonRect;
        ButtonRect = nullptr;
        
        if (PlayGame) {

            bool GameRunning = true;
            long int nSpeedCount = 0;
            vector<GameObject*> PlayerList;
            vector<GameObject*> EnemyList;
            int Score = 0;
            int MissileCount = 10;
            bool hasBossSpawned = false;
            bool BossDefeated = false;
            GameObject* Boss = nullptr;
            GameObject* Object = nullptr;
            GameObject* Object2 = nullptr;
            Mix_Music* GameMusic = Mix_LoadMUS("GameMusic_1.mp3");
            Mix_PlayMusic(GameMusic, -1);

            float ExplosionAngles[] = { 0.0, -0.78539, -1.57079, -2.35619, 3.14159, 2.35619, 1.57079, 0.7854 };

            //Event handler
            SDL_Event e;

            //Color for Text
            SDL_Color ForText = { 0, 0, 0 };
            SDL_Color ForNumbers = { 0, 0, 0 };

            string Text1 = "Score: ";
            string Text2 = "Missiles: ";

            SDL_Rect* Text = new SDL_Rect();
            SDL_Rect* Numbers = new SDL_Rect();

            SDL_Surface* TextSurface1 = TTF_RenderText_Solid(gFont, Text1.c_str(), ForText);
            SDL_Surface* TextSurface2 = TTF_RenderText_Solid(gFont, Text2.c_str(), ForText);

            SDL_Texture* TextTexture1 = SDL_CreateTextureFromSurface(gRenderer, TextSurface1);
            SDL_Texture* TextTexture2 = SDL_CreateTextureFromSurface(gRenderer, TextSurface2);

            SDL_FreeSurface(TextSurface1);
            SDL_FreeSurface(TextSurface2);

            SDL_Surface* NumberSurface1 = nullptr;
            SDL_Surface* NumberSurface2 = nullptr;

            SDL_Texture* NumberTexture1 = nullptr;
            SDL_Texture* NumberTexture2 = nullptr;

            GameObject* Player1 = new Player(450, 350, gRenderer);

            /*GameObject* shootingEnemy = new ShootingEnemy(200, 0, gRenderer);
            EnemyList.emplace_back(shootingEnemy);
            shootingEnemy->Translate(0, 20);*/

            while (GameRunning) {

                this_thread::sleep_for(50ms);
                nSpeedCount++;

                while (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        GameRunning = false;
                    }
                    //User presses a key
                    else if (e.type == SDL_KEYDOWN)
                    {
                        //Select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            Player1->Translate(0, -20);
                            break;

                        case SDLK_DOWN:
                            Player1->Translate(0, 20);
                            break;

                        case SDLK_LEFT:
                            Player1->Translate(-25, 0);
                            break;

                        case SDLK_RIGHT:
                            Player1->Translate(25, 0);
                            break;

                        case SDLK_SPACE:
                        {
                            GameObject* playerBullet = new PlayerBullet(Player1->GetRectangle()->x + 26, Player1->GetRectangle()->y, gRenderer);
                            PlayerList.emplace_back(playerBullet);
                            break;

                        }

                        case SDLK_b:
                        {

                            //if (MissileCoolDown >= 5) {

                                if (MissileCount > 0) {

                                    GameObject* Missile = new HomingMissile(Player1->GetRectangle()->x + 16, Player1->GetRectangle()->y, gRenderer);
                                    PlayerList.emplace_back(Missile);

                                    GameObject* Lock = nullptr;
                                    int DistanceX = 1000;

                                    for (int i = 0; i < EnemyList.size(); i++) {

                                        Object = EnemyList.at(i);

                                        if (Object->GetEnemyType() != 0) {

                                            if (abs(Object->GetRectangle()->x - Missile->GetRectangle()->x) < DistanceX) {
                                                DistanceX = abs(Object->GetRectangle()->x - Missile->GetRectangle()->x);
                                                Lock = Object;
                                            }

                                        }

                                    }

                                    if (Lock == nullptr)
                                        Missile->SetTarget(Lock);
                                    else {
                                        Missile->SetTarget(Lock);
                                        Missile->SetTargetAcquired(true);
                                    }

                                    MissileCount--;

                                }

                            //}

                            break;
                        }


                        }
                    }

                }

                if (nSpeedCount % 40 == 0) {

                    if (MissileCount < 10)
                        MissileCount++;

                }

                if (nSpeedCount % 80 == 0) {

                    if (nSpeedCount < 300) {

                        int random1 = rand() % 2;
                        int random2 = 100 + (rand() % 350);
                        int random3 = 450 + (rand() % 350);

                        if (random1 == 0) {

                            GameObject* shootingEnemy = new ShootingEnemy(random2, 0, gRenderer);
                            EnemyList.emplace_back(shootingEnemy);
                            shootingEnemy->Translate(0, 20);

                            GameObject* shootingEnemyBullet = new ShootingEnemyBullet(shootingEnemy->GetRectangle()->x + 26, shootingEnemy->GetRectangle()->y + 64, gRenderer);
                            EnemyList.emplace_back(shootingEnemyBullet);
                            shootingEnemyBullet->SetTarget(Player1);

                            GameObject* dodgingEnemy = new DodgingEnemy(random3, 0, gRenderer);
                            EnemyList.emplace_back(dodgingEnemy);
                            dodgingEnemy->Translate(0, 18);

                            GameObject* dodgingEnemyBullet = new DodgingEnemyBullet(dodgingEnemy->GetRectangle()->x + 26, dodgingEnemy->GetRectangle()->y + 64, gRenderer);
                            EnemyList.emplace_back(dodgingEnemyBullet);



                        }
                        else {

                            GameObject* shootingEnemy = new ShootingEnemy(random3, 0, gRenderer);
                            EnemyList.emplace_back(shootingEnemy);
                            shootingEnemy->Translate(0, 20);

                            GameObject* shootingEnemyBullet = new ShootingEnemyBullet(shootingEnemy->GetRectangle()->x + 26, shootingEnemy->GetRectangle()->y + 64, gRenderer);
                            EnemyList.emplace_back(shootingEnemyBullet);
                            shootingEnemyBullet->SetTarget(Player1);

                            GameObject* dodgingEnemy = new DodgingEnemy(random2, 0, gRenderer);
                            EnemyList.emplace_back(dodgingEnemy);
                            dodgingEnemy->Translate(0, 18);

                            GameObject* dodgingEnemyBullet = new DodgingEnemyBullet(dodgingEnemy->GetRectangle()->x + 26, dodgingEnemy->GetRectangle()->y + 64, gRenderer);
                            EnemyList.emplace_back(dodgingEnemyBullet);

                        }

                    }
                    if (hasBossSpawned && !BossDefeated) {

                        if(Boss->GetTurretOne() != nullptr)
                            Boss->ShootTurretOne(&EnemyList, gRenderer);


                    }

                }

                if (nSpeedCount % 90 == 0 && hasBossSpawned && !BossDefeated) {

                    if (Boss->GetTurretTwo() != nullptr)
                        Boss->ShootTurretTwo(&EnemyList, gRenderer);

                }

                if (nSpeedCount % 100 == 0 && hasBossSpawned && !BossDefeated) {

                    if (Boss->GetTurretThree() != nullptr)
                        Boss->ShootTurretThree(&EnemyList, gRenderer);

                }

                if (nSpeedCount % 115 == 0 && hasBossSpawned && !BossDefeated) {

                    if (Boss->GetTurretFour() != nullptr)
                        Boss->ShootTurretFour(&EnemyList, gRenderer);

                }

                if (nSpeedCount >= 300 && !hasBossSpawned && EnemyList.empty()) {

                    hasBossSpawned = true;
                    Boss = new BossEnemy((nScreenWidth - 256)/2, -256, gRenderer);
                    Boss->SetTarget(Player1);
                    EnemyList.emplace_back(Boss);
                    EnemyList.emplace_back(Boss->GetTurretOne());
                    EnemyList.emplace_back(Boss->GetTurretTwo());
                    EnemyList.emplace_back(Boss->GetTurretThree());
                    EnemyList.emplace_back(Boss->GetTurretFour());

                }

                if (nSpeedCount % 2 == 0) {

                    int Distance = 0;
                    int DodgeUnits = 0;

                    //Dodge Coding

                    for (int i = 0; i < PlayerList.size(); i++) {

                        Object = PlayerList.at(i);

                        for (int j = 0; j < EnemyList.size(); j++) {

                            Object2 = EnemyList.at(j);

                            if (Object2->GetEnemyType() == 2 && Object2->GetDodgeStatus() == false && Object->IsParticle() == false) {

                                Distance = Object2->GetRectangle()->y - Object->GetRectangle()->y;

                                if (Distance > -90 && Distance < Object->GetRectangle()->h + 26) {

                                    Distance = Object2->GetRectangle()->x - Object->GetRectangle()->x;

                                    if (Distance > -74 && Distance < Object->GetRectangle()->w + 10) {

                                        //Collision Imminent !!

                                        if (Distance >= 0) {

                                            if (Object2->GetRectangle()->x + Object->GetRectangle()->w > 816)
                                                DodgeUnits = -(64 + Distance);
                                            else
                                                DodgeUnits = Object->GetRectangle()->w;

                                        }
                                        else {

                                            if (abs(Distance) < 32) {

                                                if (Object2->GetRectangle()->x + (32 + Object->GetRectangle()->w) > 816)
                                                    DodgeUnits = -(64);
                                                else
                                                    DodgeUnits = 32 + Object->GetRectangle()->w;

                                            }
                                            else {

                                                if (Object2->GetRectangle()->x - (32 + Object->GetRectangle()->w) < 0)
                                                    DodgeUnits = 64 + Distance;
                                                else
                                                    DodgeUnits = -(32 + Object->GetRectangle()->w);

                                            }

                                        }


                                        Object2->SetDodgeStatus(true);
                                        Object2->Translate(DodgeUnits, 0);


                                    }


                                }


                            }

                        }

                    }



                    //Collision Detection

                    for (int i = 0; i < PlayerList.size(); i++) {

                        Object = PlayerList.at(i);

                        for (int j = 0; j < EnemyList.size(); j++) {
                                
                            Object2 = EnemyList.at(j);

                                if (Object->IsParticle() == false) {

                                    if (Object2->GetRectangle()->w == 64 && Object2->GetRectangle()->h == 64 && Object2->GetEnemyType() != 3) {

                                        Distance = Object2->GetRectangle()->x - Object->GetRectangle()->x;

                                        if (Distance > -64 && Distance < Object->GetRectangle()->w) {

                                            Distance = Object2->GetRectangle()->y - Object->GetRectangle()->y;

                                            if (Distance > -64 && Distance < Object->GetRectangle()->h) {

                                                //Collision Detected !!

                                                if (Object2->GetEnemyType() == 1) {

                                                    if (Object2->GetHealth() > 1) {

                                                        Object2->DecHealth();
                                                        Object->ChangeAliveStatus(false);
                                                        Score = Score + 5;


                                                    }
                                                    else {

                                                        Object2->DecHealth();
                                                        Object->ChangeAliveStatus(false);
                                                        Object2->ChangeAliveStatus(false);
                                                        Score = Score + 10;

                                                        for (int i = 0; i < 8; i++) {

                                                            GameObject* ExpParticle = new ExplosionParticle(Object2->GetRectangle()->x, Object2->GetRectangle()->y, gRenderer);
                                                            ExpParticle->setAngle(ExplosionAngles[i]);
                                                            PlayerList.emplace_back(ExpParticle);


                                                        }


                                                    }

                                                }
                                                else if (Object2->GetEnemyType() == 2) {

                                                    Object->ChangeAliveStatus(false);
                                                    Object2->ChangeAliveStatus(false);
                                                    Score = Score + 10;

                                                    for (int i = 0; i < 8; i++) {

                                                        GameObject* ExpParticle = new ExplosionParticle(Object2->GetRectangle()->x, Object2->GetRectangle()->y, gRenderer);
                                                        ExpParticle->setAngle(ExplosionAngles[i]);
                                                        PlayerList.emplace_back(ExpParticle);


                                                    }

                                                }

                                            }

                                        }


                                    }
                                    else if (Object2->GetEnemyType() == 3) {

                                        Distance = Object2->GetRectangle()->x - Object->GetRectangle()->x;

                                        if (Distance > -64 && Distance < Object->GetRectangle()->w) {

                                            Distance = Object2->GetRectangle()->y - Object->GetRectangle()->y;

                                            if (Distance > -64 && Distance < Object->GetRectangle()->h) {

                                                if (Object2->GetHealth() > 1) {

                                                    Object2->DecHealth();
                                                    Object->ChangeAliveStatus(false);
                                                    Score = Score + 5;

                                                }
                                                else {

                                                    Object2->DecHealth();
                                                    Object->ChangeAliveStatus(false);
                                                    Object2->ChangeAliveStatus(false);
                                                    Score = Score + 10;

                                                    for (int i = 0; i < 8; i++) {

                                                        GameObject* ExpParticle = new ExplosionParticle(Object2->GetRectangle()->x, Object2->GetRectangle()->y, gRenderer);
                                                        ExpParticle->setAngle(ExplosionAngles[i]);
                                                        PlayerList.emplace_back(ExpParticle);


                                                    }


                                                }

                                            }


                                        }


                                    }
                                    else if (Object2->GetEnemyType() == 4 && !Object2->TurretsIntact()) {

                                        if (SDL_HasIntersection(Object->GetRectangle(), Object2->GetRectangle())) {

                                            if (Object2->GetHealth() > 1) {

                                                Object2->DecHealth();
                                                Object->ChangeAliveStatus(false);
                                                Score = Score + 5;

                                            }
                                            else {

                                                Object2->DecHealth();
                                                Object->ChangeAliveStatus(false);
                                                Object2->ChangeAliveStatus(false);
                                                Score = Score + 10;
                                                BossDefeated = true;
                                                Mix_HaltMusic();

                                                for (int i = 0; i < 8; i++) {

                                                    GameObject* ExpParticle = new ExplosionParticle(Object2->GetRectangle()->x + Object2->GetRectangle()->w / 2, Object2->GetRectangle()->y + Object2->GetRectangle()->h / 2, gRenderer);
                                                    ExpParticle->setAngle(ExplosionAngles[i]);
                                                    PlayerList.emplace_back(ExpParticle);


                                                }


                                            }

                                        }

                                    }

                                }


                        }

                    }

                    //Collision Detection between Player and EnemyList

                    for (int i = 0; i < EnemyList.size(); i++){

                        Object2 = EnemyList.at(i);

                        Distance = Player1->GetRectangle()->x - Object2->GetRectangle()->x;

                        if (Distance > -(64) && Distance < Object2->GetRectangle()->w) {

                            Distance = Player1->GetRectangle()->y - Object2->GetRectangle()->y;

                            if (Distance > -(64) && Distance < Object2->GetRectangle()->h) {

                                //Collision Detected !!

                                this_thread::sleep_for(200ms);
                                Player1->ChangeAliveStatus(false);
                                Object2->ChangeAliveStatus(false);
                                GameRunning = false;
                                cout << "Game Over! Colission Detected!" << endl;



                            }

                        }


                    }


                    //Clear screen
                    SDL_RenderClear(gRenderer);

                    //Rendering Scores and Missile Count
                    TTF_SizeText(gFont, Text1.c_str(), &Text->w, &Text->h);
                    Text->x = 0;
                    Text->y = 0;

                    SDL_RenderCopy(gRenderer, TextTexture1, NULL, Text);

                    NumberSurface1 = TTF_RenderText_Solid(gFont, to_string(Score).c_str(), ForNumbers);
                    SDL_DestroyTexture(NumberTexture1);
                    NumberTexture1 = SDL_CreateTextureFromSurface(gRenderer, NumberSurface1);
                    SDL_FreeSurface(NumberSurface1);


                    TTF_SizeText(gFont, to_string(Score).c_str(), &Numbers->w, &Numbers->h);
                    Numbers->x = Text->w + 10;
                    Numbers->y = 0;

                    SDL_RenderCopy(gRenderer, NumberTexture1, NULL, Numbers);

                    TTF_SizeText(gFont, Text2.c_str(), &Text->w, &Text->h);
                    Text->x = 0;
                    Text->y = 30;

                    SDL_RenderCopy(gRenderer, TextTexture2, NULL, Text);

                    NumberSurface2 = TTF_RenderText_Solid(gFont, to_string(MissileCount).c_str(), ForNumbers);
                    SDL_DestroyTexture(NumberTexture2);
                    NumberTexture2 = SDL_CreateTextureFromSurface(gRenderer, NumberSurface2);
                    SDL_FreeSurface(NumberSurface2);


                    TTF_SizeText(gFont, to_string(MissileCount).c_str(), &Numbers->w, &Numbers->h);
                    Numbers->x = Text->w + 10;
                    Numbers->y = 30;

                    SDL_RenderCopy(gRenderer, NumberTexture2, NULL, Numbers);


                    //Calling Players Move
                    if (Player1->Alive() == true)
                        Player1->Move();

                    //Render texture to screen
                    Player1->Render(gRenderer);

                    for (int i = 0; i < PlayerList.size(); i++) {

                        Object = PlayerList.at(i);
                        Object->Move();
                        if (Object->GetSmokeStatus())
                            Object->RenderSmoke(gRenderer);
                        if (Object->Alive())
                            Object->Render(gRenderer);


                    }

                    for (int i = 0; i < EnemyList.size(); i++) {

                        Object = EnemyList.at(i);
                        if (Object->GetDodgeStatus())
                            Object->Dodge();
                        else
                            Object->Move();

                        if (Object->Alive()) {
                            Object->Render(gRenderer);
                        }

                    }

                    //Update screen
                    SDL_RenderPresent(gRenderer);

                    for (int i = 0; i < PlayerList.size(); i++) {

                        if (PlayerList.at(i)->Alive() == false) {
                            delete PlayerList.at(i);
                            PlayerList.erase(PlayerList.begin() + i);
                        }

                    }

                    for (int i = 0; i < EnemyList.size(); i++) {

                        if (EnemyList.at(i)->Alive() == false) {

                            for (int j = 0; j < PlayerList.size(); j++) {

                                Object = PlayerList.at(j);
                                if (Object->GetTarget() == EnemyList.at(i))
                                    Object->SetTarget(nullptr);

                            }
                            if (hasBossSpawned && !BossDefeated) {

                                if (Boss->GetTurretOne() == EnemyList.at(i))
                                    Boss->SetTurretOne(nullptr);
                                else if ((Boss->GetTurretTwo() == EnemyList.at(i)))
                                    Boss->SetTurretTwo(nullptr);
                                else if ((Boss->GetTurretThree() == EnemyList.at(i)))
                                    Boss->SetTurretThree(nullptr);
                                else if ((Boss->GetTurretFour() == EnemyList.at(i)))
                                    Boss->SetTurretFour(nullptr);

                            }

                            delete EnemyList.at(i);
                            EnemyList.erase(EnemyList.begin() + i);
                        }

                    }

                    if (BossDefeated && PlayerList.empty())
                        GameRunning = false;


                }

                /*for (int i = 0; i < PlayerList.size(); i++) {

                    if (PlayerList.at(i)->Alive() == false) {
                        delete PlayerList.at(i);
                        PlayerList.erase(PlayerList.begin() + i);
                    }

                }

                for (int i = 0; i < EnemyList.size(); i++) {

                    if (EnemyList.at(i)->Alive() == false) {

                        for (GameObject* Missile : PlayerList) {

                            if (Missile->GetTarget() == EnemyList.at(i))
                                Missile->SetTarget(nullptr);

                        }
                        if (hasBossSpawned) {

                            if (Boss->GetTurretOne() == EnemyList.at(i))
                                Boss->SetTurretOne(nullptr);
                            else if((Boss->GetTurretTwo() == EnemyList.at(i)))
                                Boss->SetTurretTwo(nullptr);

                        }

                        delete EnemyList.at(i);
                        EnemyList.erase(EnemyList.begin() + i);
                    }

                }

                if (BossDefeated && PlayerList.empty())
                    GameRunning = false;*/

            }

            SDL_DestroyTexture(TextTexture1);
            SDL_DestroyTexture(TextTexture2);
            SDL_DestroyTexture(NumberTexture1);
            SDL_DestroyTexture(NumberTexture2);

            TextTexture1 = nullptr;
            TextTexture2 = nullptr;
            NumberTexture1 = nullptr;
            NumberTexture2 = nullptr;

            delete Text;
            Text = nullptr;
            delete Numbers;
            Numbers = nullptr;

            Mix_FreeMusic(GameMusic);
            GameMusic = nullptr;

            Object = nullptr;
            Object2 = nullptr;


        }

    }

    close();
	
    return 0;

}