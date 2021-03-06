#include <SDL/SDL.h>
#include "game.h"
#include "graphics.h"
#include "sprite.h"

namespace {
const int kFps = 60;
const int kMaxFrameTime = 5 * 1000 / 60;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_ShowCursor(SDL_DISABLE);
	eventLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::eventLoop() {
	Graphics graphics; //create screen
	SDL_Event event;

	sprite_.reset(new Sprite("MyChar.bmp", 0, 0, 32, 32));

	bool running = true;
	while (running) {
		const int start_time_ms = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						running = false;
					}
					break;
				default:
					break;
			}
		}
		update();
		draw(graphics);
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		SDL_Delay(1000 / kFps - elapsed_time_ms);

		/* Calculate fps
		const int seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
		const float fps = 1 / seconds_per_frame;
		printf("fps=%f\n", fps);
		*/
	}
}

void Game::update() {
}

void Game::draw(Graphics& graphics) {
	sprite_->draw(graphics, 320, 240);
	graphics.flip();
}