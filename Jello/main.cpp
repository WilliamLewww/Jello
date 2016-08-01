#include "main.h"

void LoadContent();
void Update(int gameTime);
void Render(SDL_Window* window, SDL_GLContext context);

Player player;
Environment environment;

SDL_Event event;
SDL_GLContext context;

bool isRunning = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Jello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

	LoadContent();

	while (isRunning) {
		RemoveInitialPress();
		leftButtonPress = false;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isRunning = false;

			GetKeys(event);
			GetButtons(event);
		}

		if (deltaTime < 1 / 60) {
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
		}
		frameStart = SDL_GetTicks();
		Update(deltaTime);
		Render(displayWindow, context);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}

	return 0;
}

void LoadContent() {
	player.LoadContent();
	environment.LoadContent();
}

void Update(int gameTime) {
	player.Update(gameTime);
	environment.Update(gameTime);
}

void Render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClearColor(ConvertColor(69), ConvertColor(177), ConvertColor(237), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	environment.Draw();
	player.Draw();
	environment.DrawForeground();

	SDL_GL_SwapWindow(window);
}

float ConvertColor(int rgbValue) {
	return (float)rgbValue / 255;
}