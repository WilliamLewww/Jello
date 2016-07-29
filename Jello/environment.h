#pragma once
#include "vector2.h"
#include "spritebatch.h"
#include <SDL_opengl.h>

struct Tile {
	GLuint texture;
	Vector2 position;

	const int width = 400, height = 50;

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }
};

struct Grass : Tile {
	
};

struct Cloud : Tile {

};

extern Grass grass[2];

class Environment {
	GLuint mountain;
	Vector2 mountainPos;
public:
	void LoadContent();
	void Update(int gameTime);
	void Draw();
};