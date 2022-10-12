#pragma once	

#include "Zombie.h"

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>
#include <cmath>
#include <vector>

class Player
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;

	float moveSpeed;
	float frameCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive, isAlive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;

public:
	Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	bool intersectsWithZombie(Zombie& z);
	void Update(float delta, const Uint8* keyState, std::vector<Zombie>& z, int vecSiz);
	void Draw(SDL_Renderer* renderTarget);  

	SDL_Rect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();
	bool GetAlive();
};

