#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "input.h"
#include "player.h"
#include "environment.h"

static const int SCREENWIDTH = 800, SCREENHEIGHT = 600;
static SDL_Window* displayWindow;

extern bool isRunning;

float ConvertColor(int rgbValue);