#pragma once	

#include <SDL.h>
#include <string>

#include "Zombie.h"


class Player
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;

	float moveSpeed;
	float frameCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;

public:
	Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	void Update(float delta, const Uint8* keyState);
	void Draw(SDL_Renderer* renderTarget);  
	//bool intersectsWithZombie(Zombie& z);

	SDL_Rect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();
};

