#pragma once
#include "vector2.h"
#include "spritebatch.h"
#include <SDL_opengl.h>
#include <vector>

struct Tile {
	GLuint texture;
	Vector2 position;

	const int width = 400, height = 50;

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	int operator==(const Tile& tile)const {
		return (position.x == tile.position.x) && (position.y == tile.position.y);
	}

	void operator=(const Tile& tile)const { }
};
extern std::vector<Tile> tileList;

struct Grass : Tile {
	
};
extern Grass grass[2];

struct Cloud : Tile {

};

class Environment {
	GLuint mountain;
	Vector2 mountainPos;
public:
	void LoadContent();
	void Update(int gameTime);
	void Draw();
};