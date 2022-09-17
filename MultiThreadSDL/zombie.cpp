#include "Zombie.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>

Zombie::Zombie(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	bool wechel = true;
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
	moveSpeed = 150.0f;
}

Zombie::~Zombie()
{
	SDL_DestroyTexture(texture);
}

void Zombie::Update(float delta, int playerX, int playerY)
{
	isActive = true;

	if (GetOriginX() > playerX)
	{
		positionRect.x -= moveSpeed * delta;
	}
	else if (GetOriginX() < playerX)
	{
		positionRect.x += moveSpeed * delta;
	}
	else if (GetOriginY() < playerY)
	{
		positionRect.y += moveSpeed * delta;
	}
	else if (GetOriginY() > playerY)
	{
		positionRect.y -= moveSpeed * delta;
	}
	else
		isActive = false;

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
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
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