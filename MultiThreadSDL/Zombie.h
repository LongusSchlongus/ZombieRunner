#pragma once

#include <SDL.h>
#include <string>

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
	int originX, originY;
	int radius;
	bool isAlive;
public:
	Zombie(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Zombie();

	void Update(float delta, int zombieX, int zombieY, int playerX, int playerY, bool explosion, Bomb& b);
	void Draw(SDL_Renderer* renderTarget);
	bool intersectsWith(Bomb& b);

	SDL_FRect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();
};

