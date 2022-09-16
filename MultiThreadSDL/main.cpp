#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <iostream>
#include <vector>
#include "player.h"
#include "Bomb.h"

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
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

int main(int argc, char* argv[])
{
	// Initiallaizing and loading variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	const Uint8* keyState; 
	SDL_Rect cameraRect = { 0, 0, 640, 480 };
	int levelWidth, levelHeight;
	bool bomb = false;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player player1(renderTarget, "player1.png", 20, 20, 3, 4);
	Player player2(renderTarget, "player2.png", 600, 400, 3, 4);

	Bomb b(renderTarget, "bomb.png", player1.GetOriginX(), player1.GetOriginY(), 3, 4);

	SDL_Texture* texture = LoadTexture("rect.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
	
	bool isRunning = true;
	SDL_Event ev;

	int i = 0;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym)
				{
				case SDLK_SPACE:
					if (true)
					{
						b.setCords(player1.GetOriginX(), player1.GetOriginY()); // check if bomb is ready or in use
						b.toggleBomb(true);
					}
					break;
				case SDLK_t:
					break;
				default:
					break;
				}
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		
		player1.Update(delta, keyState);
		player2.Update(delta, keyState);
		b.Update(delta);
		

		cameraRect.x = player1.GetOriginX() - 320;
		cameraRect.y = player1.GetOriginY() - 240;

		if (cameraRect.x < 0)
			cameraRect.x = 0;
		if (cameraRect.y < 0)
			cameraRect.y = 0;

		if (cameraRect.x + cameraRect.w >= levelWidth)
			cameraRect.x = levelWidth - 640;
		if (cameraRect.y + cameraRect.h >= levelHeight)
			cameraRect.y = levelHeight - 480;

		if (player1.intersectsWith(b) && b.getExploded())
		{
			b.setExploded(false);
			std::cout << "Damag taken!" << std::endl;
		}

		// Drawing the cuurent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, &cameraRect, NULL);

		player1.Draw(renderTarget);
		player2.Draw(renderTarget);
		b.Draw(renderTarget);
		
		SDL_RenderPresent(renderTarget);
	}
	// Freeing the memory
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);
	window = nullptr;
	renderTarget = nullptr;
	texture = nullptr;

	IMG_Quit();
	SDL_Quit();

	return 0;

}

//^^^^°°abortb#i*
