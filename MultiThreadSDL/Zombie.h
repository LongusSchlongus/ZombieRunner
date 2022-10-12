#pragma once

#include "Bomb.h"

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>
#include <cmath>


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
	int counter;

public:
	//constructor
	Zombie();

	//copy-constructor
	//Zombie(const Zombie& z);

	//Assignment operator
	//Zombie& operator= (const Zombie& other);

	//destructor
	~Zombie();

	void SetTexture(SDL_Renderer* renderTarget, std::string filePath);

	SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget);

	void Update(float delta, int playerX, int playerY, int player2X, int player2Y, Bomb& b, Bomb& b2, int* h);
	void Draw(SDL_Renderer* renderTarget);
	bool intersectsWith(Bomb& b);

	SDL_FRect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();
	bool GetAlive();
};

