#include "player.h"

void Player::LoadContent() {
	texture = LoadTexture("../Content/player.png");
	position = Vector2(25, 500);
	speed = 100;
	jumpSpeed = 5;
}

std::vector<Tile> groundTileList;
void Player::Update(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;

	position.x += velocityX;
	position.y += velocityY;
	velocityX = 0;

	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) velocityX = -speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) velocityX = speed * deltaTimeS;

	if (onGround == true) {
		if (jumpPress == false) {
			if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end()) {
				velocityY = -jumpSpeed; onGround = false; jumpPress = true;
			}
		}
	}
	else {
		velocityY += 9.8 * deltaTimeS;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) == keyList.end()) {
		if (velocityY < 0 && onGround == false) velocityY += 9.8 * deltaTimeS;
		if (onGround == true) jumpPress = false;
	}

	for (auto &tile : tileList) {
		if (CheckCollision(tile) == true) {
			HandleCollision(tile);
		}
	}

	std::vector<Tile> tempGroundTileList;
	for (auto &tile : groundTileList) {
		if (CheckCollision(tile) == false) {
			tempGroundTileList.push_back(tile);
		}
	}

	for (auto &tile : tempGroundTileList) {
		groundTileList.erase(std::remove(groundTileList.begin(), groundTileList.end(), tile), groundTileList.end());
	}
	tempGroundTileList.clear();

	if (groundTileList.size() == 0) onGround = false;
}

bool Player::CheckCollision(Tile tile) {
	if (left() <= tile.right() &&
		right() >= tile.left() &&
		top() <= tile.bottom() &&
		bottom() >= tile.top()) {
		return true;
	}

	return false;
}

bool Player::CheckCollisionBottom(Tile tile) {
	if (top() <= tile.bottom() && top() >= tile.bottom() - 5 && left() <= tile.right() - 3 && right() >= tile.left() + 3) return true;
	return false;
}

void Player::HandleCollision(Tile tile) {
	double overlapX, overlapY;
	if (midpoint().x > tile.midpoint().x) overlapX = tile.right() - left();
	else overlapX = -(right() - tile.left());
	if (midpoint().y > tile.midpoint().y) overlapY = tile.bottom() - top();
	else overlapY = -(bottom() - tile.top());

	if (overlapX != 0 && overlapY != 0) {
		if (abs(overlapY) < abs(overlapX)) {
			if (overlapY < 0) {
				if (velocityY > 0) {
					onGround = true;
					position.y += overlapY; velocityY = 0;
					if (std::find(groundTileList.begin(), groundTileList.end(), tile) == groundTileList.end()) groundTileList.push_back(tile);
				}
			}
			else {
				if (velocityY < 0) {
					if (CheckCollisionBottom(tile)) { position.y += overlapY; velocityY = 0; }
				}
			}
		}
		else {
			position.x += overlapX; velocityX = 0;
		}
	}
}

void Player::Draw() {
	DrawTexture(texture, position, width, height);
}