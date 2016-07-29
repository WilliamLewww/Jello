#include "environment.h"

std::vector<Tile> tileList;
Grass grass[2];

void Environment::LoadContent() {
	mountain = LoadTexture("../Content/mountain.png");
	grass[0].texture = LoadTexture("../Content/grass.png");
	grass[0].position = Vector2(0, 550);
	grass[1].texture = LoadTexture("../Content/grass.png");
	grass[1].position = Vector2(400, 550);

	tileList.push_back(grass[0]);
	tileList.push_back(grass[1]);
}

void Environment::Update(int gameTime) {

}

void Environment::Draw() {
	DrawTexture(mountain, Vector2(0, 0), 800, 600);
	DrawTexture(grass[0].texture, grass[0].position, grass[0].width, grass[0].height);
	DrawTexture(grass[1].texture, grass[1].position, grass[1].width, grass[1].height);
}