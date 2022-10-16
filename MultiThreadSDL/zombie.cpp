#include "Zombie.h"

Zombie::Zombie()
{
	isAlive = true;
	frameCounter = 0;
}

Zombie::~Zombie()
{
	SDL_DestroyTexture(texture);
}

void Zombie::SetPosition(int x, int y)
{
	positionRect.x = rand() % 600;
	positionRect.y = rand() % 400;
}

void Zombie::SetTexture(SDL_Renderer* renderTarget, std::string filePath)
{
	int framesX = 3;
	int framesY = 4;

	SDL_Texture* texture = nullptr;
	texture = LoadTexture(filePath, renderTarget);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

	moveSpeed = rand() % 25;
}

SDL_Texture* Zombie::LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
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
	return texture;
}

void Zombie::Update(float delta, int playerX, int playerY, int player2X, int player2Y, Bomb& b1, Bomb& b2, int* h)
{
	frameCounter += delta;

	int zombieX = this->GetOriginX();
	int zombieY = this->GetOriginY();
	
	float dist1 = sqrt(pow(abs(playerX - zombieX), 2) + pow(abs(playerY - zombieY), 2));
	float dist2 = sqrt(pow(abs(player2X - zombieX), 2) + pow(abs(player2Y - zombieY), 2));

	if (frameCounter >= 0.25f)
	{
		frameCounter = 0;
		cropRect.x += frameWidth;

		if (cropRect.x >= textureWidth)
			cropRect.x = 0;
	}

	if (isAlive)
	{
		if (dist1 <= dist2)
		{
			if (zombieX < playerX)
				positionRect.x += moveSpeed * delta;

			else if (zombieX > playerX)
				positionRect.x -= moveSpeed * delta;


			if (zombieY > playerY)
				positionRect.y -= moveSpeed * delta;

			else if (zombieY < playerY)
				positionRect.y += moveSpeed * delta;
		}
		else
		{
			if (zombieX < player2X)
				positionRect.x += moveSpeed * delta;
			
			else if (zombieX > player2X)
				positionRect.x -= moveSpeed * delta;
			

			if (zombieY > player2Y)
				positionRect.y -= moveSpeed * delta;
			
			else if (zombieY < player2Y)
				positionRect.y += moveSpeed * delta;
		}
	}

	if ((b1.getExplosion() && intersectsWith(b1)) || (b2.getExplosion() && intersectsWith(b2)))
	{
		if (isAlive)
		{
			isAlive = false;
			std::cout << "hit!" << std::endl;
			*h += 200;
			cropRect.y += frameHeight * 3;
		}
	}

	std::cout << cropRect.y << " == " << frameHeight * 3 << " && " << cropRect.x << " == " << frameWidth * 2 << std::endl;

	if (cropRect.y == frameHeight * 3 && cropRect.x == frameWidth * 2)
	{
		SDL_DestroyTexture(texture);
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

bool Zombie::GetAlive()
{
	return isAlive;
}
