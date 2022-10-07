#include "Zombie.h"
#include "Player.h"

#include <SDL_image.h>
#include <iostream>
#include <cmath>

Zombie::Zombie(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	isAlive = true;
	frameCounter = 0;

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

	isActive = false;
	moveSpeed = 25.0f;
}

Zombie::~Zombie()
{
	SDL_DestroyTexture(texture);
}

void Zombie::Update(float delta, int zombieX, int zombieY, int playerX, int playerY, bool explosion, Bomb& b)
{
	isActive = true;
	
	if (isAlive)
	{
		if (zombieX < playerX)
		{
			positionRect.x += moveSpeed * delta;
			std::cout << "right" << std::endl;
		}
		else if (zombieX > playerX)
		{
			positionRect.x -= moveSpeed * delta;
			std::cout << "left" << std::endl;
		}

		if (zombieY > playerY)
		{
			positionRect.y -= moveSpeed * delta;
			std::cout << "up" << std::endl;
		}
		else if (zombieY < playerY)
		{
			positionRect.y += moveSpeed * delta;
			std::cout << "down" << std::endl;
		}
	}

	if (explosion && intersectsWith(b))
	{
		std::cout << "hit" << std::endl;
		isAlive = false;
		positionRect.x = -200.0f;
		positionRect.y = -200.0f;
	}

	if (isActive)
	{
		frameCounter += delta;

		if (frameCounter >= 0.25f)
		{
			frameCounter = 0;
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth)
				cropRect.x = 0;
		}
	}
	else
	{
		frameCounter = 0;
		cropRect.x = frameWidth;
	}
}

void Zombie::Draw(SDL_Renderer* renderTarget)
{
	SDL_Rect test;
	test.x = positionRect.x;
	test.w = positionRect.w;
	test.h = positionRect.h;
	test.y = positionRect.y;


	SDL_RenderCopy(renderTarget, texture, &cropRect, &test);
}

bool Zombie::intersectsWith(Bomb& p)
{
	if (sqrt(pow(GetOriginX() - p.GetOriginX(), 2) + pow(GetOriginY() - p.GetOriginY(), 2)) >= radius + p.GetRadius())
	{
		return false;
	}
	return true;
}

int Zombie::GetOriginX() { return positionRect.x + originX; }
int Zombie::GetOriginY() { return positionRect.y + originY; }
int Zombie::GetRadius() { return radius; }