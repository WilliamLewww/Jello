#include "environment.h"

std::vector<Tile> tileList;
Grass grass[2];
Cloud cloud[20];

void Environment::LoadContent() {
	mountain = LoadTexture("../Content/mountain.png");

	for (int x = 0; x < (sizeof(grass) / sizeof(*grass)); x++) {
		grass[x].texture = LoadTexture("../Content/grass.png");
		grass[x].position = Vector2(x * 400, 550);
		tileList.push_back(grass[x]);
	}

	for (int x = 0; x < (sizeof(cloud) / sizeof(*cloud)); x++) {
		if (x % 5 == 1 || x % 5 == 3) { cloud[x].moveLeft = true; }
		cloud[x].movement = rand() % 100 + 1;
		cloud[x].texture = LoadTexture("../Content/cloud.png");
		cloud[x].position = Vector2(((x * 400) / 10) - 150, ((x % 3) * 25) - 30);
	}
}

void Environment::Update(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;

	for (int x = 0; x < (sizeof(cloud) / sizeof(*cloud)); x++) {
		if (cloud[x].moveLeft == true) { cloud[x].position.x -= 7 * deltaTimeS; cloud[x].movement += 1; }
		else { cloud[x].position.x += 7 * deltaTimeS; cloud[x].movement += 1; }

		if (cloud[x].movement >= 100) { cloud[x].moveLeft = !cloud[x].moveLeft; cloud[x].movement = 0; }
	}
}

void Environment::Draw() {
	DrawTexture(mountain, Vector2(0, 0), 800, 600);

	for (int x = 0; x < (sizeof(grass) / sizeof(*grass)); x++) {
		DrawTexture(grass[x].texture, grass[x].position, grass[x].width, grass[x].height);
	}

	for (int x = 0; x < (sizeof(cloud) / sizeof(*cloud)); x++) {
		DrawTexture(cloud[x].texture, cloud[x].position, cloud[x].width, cloud[x].height);
	}
}