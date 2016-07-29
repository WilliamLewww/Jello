#pragma once
#include "main.h"
#include "vector2.h"
#include <SOIL.h>
#include <SDL_opengl.h>

//     "../Content/texture.bmp"
GLuint LoadTexture(const char* path);
void DrawTexture(GLuint texture, Vector2 position, int width, int height);