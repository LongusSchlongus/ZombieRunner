#include "Bomb.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>

Bomb::Bomb(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	isActive = false;

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

	static int playerNumber = 0;
	playerNumber++;

	if (playerNumber == 1)
	{
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
	}
	else
	{
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;

	}
	moveSpeed = 200.0f;
}

Bomb::~Bomb()
{
	SDL_DestroyTexture(texture);
}

void Bomb::Update(float delta)
{
	if (isActive)
	{
		SDL_SetTextureColorMod(texture, rand()%255, rand() % 255, rand() % 255);
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
		frameCounter = 0;
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

void Bomb::Spawn(int posX, int posY)
{
    positionRect.x = posX;
	positionRect.y = posY;

	isActive = true;
}




