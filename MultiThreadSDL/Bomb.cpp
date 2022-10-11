#include "Bomb.h"



Bomb::Bomb(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	explosion = false;
	frameCounter = 0;
	isActive = false;
	periodCounter = 0;

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
		frameCounter += delta;
		if (frameCounter >= 0.25f)
		{
			periodCounter++;

			frameCounter = 0;

			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth)
				cropRect.x = 0;

		}

		if (periodCounter >= 0 && periodCounter < 4)
		{
			cropRect.y = 0;
			explosion = false;
		}
		else if (periodCounter >= 4 && periodCounter < 8)
		{
			cropRect.y = frameWidth;
			explosion = true;
		}
		else if (periodCounter >= 8)
		{
			resetBomb();
			explosion = false;
		}
	}
}

void Bomb::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}


int Bomb::GetOriginX() { return positionRect.x + originX; }

int Bomb::GetOriginY() { return positionRect.y + originY; }

int Bomb::GetRadius() { return radius; }

void Bomb::toggleBomb(int x, int y)
{
	positionRect.x = x;
	positionRect.y = y;
	isActive = true;
}
void Bomb::resetBomb()
{
	positionRect.x = -200;
	positionRect.y = 200;
	isActive = false;
	periodCounter = 0;
}
bool Bomb::getExplosion() { return explosion; }




