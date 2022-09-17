#pragma once

#include <SDL.h>
#include <string>

#include "Zombie.h"
#include "Bomb.h"


class Zombie
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
	Zombie(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Zombie();

	void Update(float delta, int playerX, int playerY);
	void Draw(SDL_Renderer* renderTarget);
	bool intersectsWith(Bomb& b);

	SDL_Rect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();
};

