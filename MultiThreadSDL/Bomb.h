#pragma once

#include <SDL.h>
#include <string>


class Bomb
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;

	float moveSpeed;
	float frameCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;
	int bombCounter;

	int id;
	char name[30];

public:
	//Default constructor
	//Bomb();

	Bomb(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);

	//Copy constructor
	//Bomb(const Bomb& bomb);

	//Assignment operator
	//Bomb& operator=(const Bomb& bomb);

	~Bomb();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	SDL_Rect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();

	void Spawn(int posX, int posY);
};

