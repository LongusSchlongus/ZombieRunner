#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>
#include <cmath>


class Bomb
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;

	float frameCounter;
	int periodCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	int originX, originY;
	int radius;

	bool explosion;

public:

	Bomb(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Bomb();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	SDL_Rect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();

	void toggleBomb(int x, int y);
	void resetBomb();
	bool getExplosion();
};

