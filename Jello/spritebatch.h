#pragma once
#include "main.h"
#include "vector2.h"
#include <SOIL.h>
#include <SDL_opengl.h>

//     "../Content/texture.bmp"
GLuint LoadTexture(const char* path);
void DrawTexture(GLuint texture, Vector2 position, int width, int height);
void DrawTexture(GLuint texture, Vector2 position, double angle, int width, int height);
void DrawTexture(GLuint texture, Vector2 position, double angle, int width, int height, float color[4]);
void DrawTextureFlippedHorizontal(GLuint texture, Vector2 position, int width, int height);

void DrawRect(Vector2 position, int width, int height, double color[4]);