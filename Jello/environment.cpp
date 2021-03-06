#include "environment.h"

std::vector<Tile> tileList;
Grass grass[2];
Cloud cloud[20];
Rain rain[100];

void Environment::LoadContent() {
	filterColor[0] = 0; filterColor[1] = 0; filterColor[2] = 0; filterColor[3] = 255;
	mountain = LoadTexture("../Content/mountain.png");
	house = LoadTexture("../Content/house.png");
	housePos = Vector2(0, 395);

	grassTexture = LoadTexture("../Content/grass.png");
	for (int x = 0; x < (sizeof(grass) / sizeof(*grass)); x++) {
		grass[x].texture = &grassTexture;
		grass[x].position = Vector2(x * 400, 550);
		tileList.push_back(grass[x]);
	}

	cloudTexture = LoadTexture("../Content/cloud.png");
	for (int x = 0; x < (sizeof(cloud) / sizeof(*cloud)); x++) {
		if (x % 5 == 1 || x % 5 == 3) { cloud[x].moveLeft = true; }
		cloud[x].texture = &cloudTexture;
		cloud[x].movement = rand() % 100 + 1;
		cloud[x].position = Vector2(((x * 400) / 10) - 150, ((x % 3) * 25) - 35);
	}

	rainTexture[0] = LoadTexture("../Content/cat1.png");
	rainTexture[1] = LoadTexture("../Content/cat2.png");
	rainTexture[2] = LoadTexture("../Content/cat3.png");
	for (int x = 0; x < (sizeof(rain) / sizeof(*rain)); x++) {
		if (x % 3 == 0) { rain[x].texture = &rainTexture[0]; }
		if (x % 3 == 1) { rain[x].texture = &rainTexture[1]; }
		if (x % 3 == 2) { rain[x].texture = &rainTexture[2]; }
		rain[x].speedX = rand() % 50 + 50;
		rain[x].speedY = rand() % 100 + 200;
		rain[x].position = Vector2((x * 32) / 3, (x % 3) * 25);
	}

	houseBMP = ReadBMP("../Content/housemap.bmp", houseWidth, houseHeight);
}

void Environment::Update(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;

	for (int x = 0; x < (sizeof(cloud) / sizeof(*cloud)); x++) {
		if (cloud[x].moveLeft == true) { cloud[x].position.x -= 7 * deltaTimeS; cloud[x].movement += 1; }
		else { cloud[x].position.x += 7 * deltaTimeS; cloud[x].movement += 1; }

		if (cloud[x].movement >= 100) { cloud[x].moveLeft = !cloud[x].moveLeft; cloud[x].movement = 0; }
	}

	for (int x = 0; x < (sizeof(rain) / sizeof(*rain)); x++) {
		if (rain[x].position.x > SCREENWIDTH) {
			rain[x].position.x = 0 - rain[x].width;
		}
		if (rain[x].position.y > grass[0].position.y) {
			rain[x].position.y = 0 - rain[x].height;
		}

		rain[x].angle += 1;
		rain[x].position.x += rain[x].speedX * deltaTimeS;
		rain[x].position.y += rain[x].speedY * deltaTimeS;
	}

	if (filterSwitch == false) {
		filterColor[3] -= .1;

		if (filterColor[3] <= 100) filterSwitch = true;
	}
	else {
		if (filterSwitchB == false) {
			filterColor[3] += .1;

			if (filterColor[3] >= 160) {
				filterSwitchB = true;
			}
		}
		else {
			filterColor[3] -= .1;

			if (filterColor[3] <= 120) {
				filterSwitchB = false;
			}
		}
	}
}

void Environment::Draw() {
	DrawTexture(mountain, Vector2(0, 0), 800, 600);

	for (int x = 0; x < (sizeof(rain) / sizeof(*rain)); x++) {
		DrawTexture(*rain[x].texture, rain[x].position, rain[x].angle, rain[x].width, rain[x].height);
	}

	for (int x = 0; x < (sizeof(grass) / sizeof(*grass)); x++) {
		DrawTexture(*grass[x].texture, grass[x].position, grass[x].width, grass[x].height);
	}

	for (int x = 0; x < (sizeof(cloud) / sizeof(*cloud)); x++) {
		DrawTexture(*cloud[x].texture, cloud[x].position, cloud[x].width, cloud[x].height);
	}

	DrawTexture(house, housePos, 419, 155);

	for (int x = 0; x < houseWidth; x++) {
		for (int y = 0; y < houseHeight; y++) {
			if (*GetPixelBMP(houseBMP, x, y, houseWidth, houseHeight) < 255) {
				glColor3f(1, 1, 1);
				glBegin(GL_POINTS);
				glVertex2d(x, y - (SCREENHEIGHT / 2) + 395);
				glEnd();
			}
		}
	}
}

void Environment::DrawForeground() {
	DrawRect(Vector2(0, 0), 800, 600, filterColor);
}