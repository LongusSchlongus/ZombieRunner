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
	float bombCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;
	bool isExploded;
	bool isReady;

public:

	Bomb(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Bomb();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	SDL_Rect positionRect;

	int GetOriginX();
	int GetOriginY();
	int GetRadius();

	void toggleBomb(bool value);
	void setCords(int x, int y);
	bool getActive();
	bool getExploded();
	void setExploded(bool value);

	void LoadTexture(SDL_Renderer* renderTarget, std::string filePath);
};

