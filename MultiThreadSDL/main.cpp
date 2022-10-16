#include "player.h"
#include "Bomb.h"
#include "Zombie.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>

#include <list>


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
	// --------------------------------------------------- Initiallaizing and loading variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	float waveDelta = 0.0f;
	const Uint8* keyState;
	SDL_Rect cameraRect = { 0, 0, 640, 480 };
	int levelWidth, levelHeight;
	bool bomb = false;
	int zombieNum, bigBoyNum;
	zombieNum = bigBoyNum = 0;
	int highscore = 0;
	std::string score_text = "Highscore: " + std::to_string(highscore);

	SDL_Init(SDL_INIT_VIDEO);
	if (TTF_Init() < 0)
		std::cout << "error!" << std::endl;

	window = SDL_CreateWindow("Zombierunner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player player1(renderTarget, "playerNew1.png", 20, 20, 3, 4);
	Player player2(renderTarget, "playerNew2.png", 600, 400, 3, 4);

	Bomb b(renderTarget, "bombNew2.png", -200, 200, 3, 4);
	Bomb b2(renderTarget, "bombNew2.png", -200, 200, 3, 4);

	Zombie zombie;
	std::list <Zombie> zombies3;
	std::vector <Zombie> *zombies2  = new std::vector<Zombie>;
	std::vector <Zombie> zombies;

	Zombie bigBoy;
	std::vector <Zombie> bigBoys;

	SDL_Texture* texture = LoadTexture("rectNew.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);


	TTF_Font* font = TTF_OpenFont("comicText.ttf", 25);
	SDL_Color color = { 0, 0, 0, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), color);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_Rect textRect;
	textRect.x = textRect.y = 20;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;


	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		if (!player1.GetAlive())
		{
			if (!player2.GetAlive())
			{
				isRunning = false;
				std::cout << "Gmae Over." << std::endl;

			}
		}

		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;
		while (SDL_PollEvent(&ev) != 0)
		{
			// --------------------------------------------------- Getting the quit and keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym)
				{
				case SDLK_SPACE:
					if(player1.GetAlive() && !b.GetActive())
						b.toggleBomb(player1.GetOriginX() - 24, player1.GetOriginY() - 32);
					break;

				case SDLK_m:
					if (player2.GetAlive() && !b2.GetActive())
						b2.toggleBomb(player2.GetOriginX() - 24, player2.GetOriginY() - 32);
					break;

				case SDLK_n:
					// change background
					break;

				case SDLK_b:
					highscore += 200;
					std::cout << score_text << std::endl;
					break;

				case SDLK_v:
					zombies.push_back(zombie);
					zombies[zombieNum].SetPosition(rand() % 600, rand() % 400);
					zombies[zombieNum].SetTexture(renderTarget, "zombieNew2.png");
					zombieNum++;
					std::cout << zombieNum << std::endl;
					break;

				case SDLK_c:
					bigBoys.push_back(bigBoy);
					bigBoys[bigBoyNum].SetPosition(rand() % 600, rand() % 400);
					bigBoys[bigBoyNum].SetTexture(renderTarget, "bigboy.png");
					bigBoyNum++;
					std::cout << bigBoyNum << std::endl;
					break;

				default:
					break;
				}
			}
		}

		//Highscore update i guess
		score_text = "Highscore: " + std::to_string(highscore);
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), color);
		SDL_Texture* text = SDL_CreateTextureFromSurface(renderTarget, textSurface);

		keyState = SDL_GetKeyboardState(NULL);
		
		player1.Update(delta, keyState, zombies, zombies.size());
		player2.Update(delta, keyState, zombies, zombies.size());

		b.Update(delta);
		b2.Update(delta);

		/*
		
		for (auto z : zombies) z.Update(delta, player1.GetOriginX(), player1.GetOriginY(), player2.GetOriginX(), player2.GetOriginY(), b, b2, &highscore);

		for (auto b : bigBoys) b.Update(delta, player1.GetOriginX(), player1.GetOriginY(), player2.GetOriginX(), player2.GetOriginY(), b, b2, &highscore);

		*/
		
		waveDelta += delta;

		if (waveDelta >= 2.25f)
		{
			waveDelta = 0;

			zombies.push_back(zombie);
			zombies[zombieNum].SetPosition(rand() % 600, rand() % 400);
			zombies[zombieNum].SetTexture(renderTarget, "zombieNew2.png");
			zombieNum++;

		}
		
		for (int i = 0; i < zombieNum; i++)
		{
			zombies[i].SetTexture(renderTarget, "zombieNew2.png");
			zombies[i].Update(delta, player1.GetOriginX(), player1.GetOriginY(), player2.GetOriginX(), player2.GetOriginY(), b, b2, &highscore);
		}

		for (int i = 0; i < bigBoyNum; i++)
		{
			bigBoys[i].SetTexture(renderTarget, "bigboy.png");
			bigBoys[i].Update(delta, player1.GetOriginX(), player1.GetOriginY(), player2.GetOriginX(), player2.GetOriginY(), b, b2, &highscore);
		}

		/*	for camera movement
		
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
		
		*/
		
		// --------------------------------------------------- Drawing the cuurent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, &cameraRect, NULL);

		player1.Draw(renderTarget);
		player2.Draw(renderTarget);

		b.Draw(renderTarget);
		b2.Draw(renderTarget);

		for (int i = 0; i < zombieNum; i++)
		{
			zombies[i].Draw(renderTarget);
		}

		for (int i = 0; i < bigBoyNum; i++)
		{
			bigBoys[i].Draw(renderTarget);
		}

		SDL_RenderCopy(renderTarget, text, NULL, &textRect);		
		SDL_RenderPresent(renderTarget);


	}

	// --------------------------------------------------- Freeing the memory
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(text);						

	window = nullptr;
	renderTarget = nullptr;
	texture = nullptr;
	text = nullptr;					

	IMG_Quit();
	SDL_Quit();

	return 0;

}

//^^^^°°abortb#i*
