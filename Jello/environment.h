#pragma once
#include "vector2.h"
#include "spritebatch.h"
#include <SDL_opengl.h>
#include <stdlib.h>
#include <vector>

struct Tile {
	GLuint *texture;
	Vector2 position;

	int width, height;

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

static GLuint grassTexture;
struct Grass : Tile {
	Grass() {
		width = 400;
		height = 50;
	}
};
extern Grass grass[2];

static GLuint cloudTexture;
struct Cloud : Tile {
	Cloud() {
		width = 300;
		height = 100;
	}

	int movement;
	bool moveLeft;
};
extern Cloud cloud[20];

static GLuint rainTexture[3];
struct Rain : Tile {
	Rain() {
		width = 25;
		height = 25;
	}

	double angle;
	double speedX, speedY;
};
extern Rain rain[100];

class Environment {
	GLuint mountain;
	Vector2 mountainPos;
public:
	void LoadContent();
	void Update(int gameTime);
	void Draw();
};