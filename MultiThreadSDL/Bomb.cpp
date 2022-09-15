#include "Bomb.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>

Bomb::Bomb(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	isExploded = false;
	std::cout << "Creation of new bmb: " << std::endl;

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
}

Bomb::~Bomb()
{
	SDL_DestroyTexture(texture);
}

void Bomb::Update(float delta)
{

	if (isActive)
	{
		SDL_SetTextureColorMod(texture, rand() % 255, rand() % 255, rand() % 255);
		frameCounter += delta;

		if (frameCounter >= 0.25f)
		{
			frameCounter = 0;
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth)
				cropRect.x = 0;
			bombCounter++;

		}
	}

	if (bombCounter >= 15 && isActive == true)
	{
		std::cout << "Explosion!!" << std::endl;
		isActive = false;
		isExploded = true;
		frameCounter = 0;
		bombCounter = 0;
		cropRect.x = frameWidth;
	}
}

void Bomb::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}


int Bomb::GetOriginX() { return positionRect.x + originX; }

int Bomb::GetOriginY() { return positionRect.y + originY; }

int Bomb::GetRadius() { return radius; }

void Bomb::toggleBomb(bool value)
{
	isActive = value;
}

void Bomb::setCords(int x, int y)
{
	positionRect.x = x;
	positionRect.y = y;

}
bool Bomb::getActive() { return isActive; }

bool Bomb::getExploded() { return isExploded; }

void Bomb::setExploded(bool value)
{
	isExploded = value;
}


