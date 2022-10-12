#include "Player.h"

Player::Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
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

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	frameCounter = 0;

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
	isAlive = true;

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

Player::~Player()
{
	SDL_DestroyTexture(texture);
}

bool Player::intersectsWithZombie(Zombie& z)
{
	if (sqrt(pow(GetOriginX() - z.GetOriginX(), 2) + pow(GetOriginY() - z.GetOriginY(), 2)) >= radius + z.GetRadius() && z.GetAlive())
	{
		return false;
	}
	return true;
}

void Player::Update(float delta, const Uint8* keyState, std::vector <Zombie>& zmb, int vecSize)
{
	isActive = true;

	if (isAlive)
	{
		if (keyState[keys[0]])
		{
			positionRect.y -= moveSpeed * delta;
			cropRect.y = frameHeight * 3;
		}
		else if (keyState[keys[1]])
		{
			positionRect.y += moveSpeed * delta;
			cropRect.y = 0;
		}
		else if (keyState[keys[2]])
		{
			positionRect.x -= moveSpeed * delta;
			cropRect.y = frameHeight;
		}
		else if (keyState[keys[3]])
		{
			positionRect.x += moveSpeed * delta;
			cropRect.y = frameHeight * 2;
		}
		else
			isActive = false;
	}
	
	if (isActive && isAlive)
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

	for (int i = 0; i< vecSize; i++)
	{
		if (intersectsWithZombie(zmb[i]) && zmb[i].GetAlive())
		{
			//isAlive = false;
			std::cout << "player took damage" << std::endl;
		}
	}
	
}

void Player::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

int Player::GetOriginX() { return positionRect.x + originX; }
int Player::GetOriginY() { return positionRect.y + originY; }
int Player::GetRadius() { return radius; }

bool Player::GetAlive()
{
	return isAlive;
}
