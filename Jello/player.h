#pragma once
#include "vector2.h"
#include "environment.h"
#include "spritebatch.h"
#include <SDL_opengl.h>
struct Tile;
class Player {
	GLuint texture;
	Vector2 position;

	const int width = 50, height = 50;

	double velocityX, velocityY;
	double speed, jumpSpeed;
	bool onGround, jumpPress;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }

	void HandleCollision(Tile tile);
	bool CheckCollisionBottom(Tile tile);
	bool CheckCollision(Tile tile);
public:
	void LoadContent();
	void Update(int gameTime);
	void Draw();
};