#include "spritebatch.h"

GLuint LoadTexture(const char* path) {

	//Filter SOIL_FLAG_MIPMAPS
	GLuint texture = SOIL_load_OGL_texture(
		path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	if (0 == texture) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return -1;
	}

	return texture;
}

void DrawTexture(GLuint texture, Vector2 position, int width, int height) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	for (int x = 0; x < 4; x++) {
		glTexCoord2f(vectors[x].x, vectors[x].y);
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2f(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawTexture(GLuint texture, Vector2 position, double angle, int width, int height) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (SCREENWIDTH / 2), position.y + (height / 2) - (SCREENHEIGHT / 2), 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (SCREENWIDTH / 2)), -(position.y + (height / 2) - (SCREENHEIGHT / 2)), 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 4; x++) {
		glTexCoord2f(vectors[x].x, vectors[x].y);
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2f(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void DrawTexture(GLuint texture, Vector2 position, double angle, int width, int height, float color[4]) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (SCREENWIDTH / 2), position.y + (height / 2) - (SCREENHEIGHT / 2), 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (SCREENWIDTH / 2)), -(position.y + (height / 2) - (SCREENHEIGHT / 2)), 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor4f(ConvertColor(color[0]), ConvertColor(color[1]), ConvertColor(color[2]), ConvertColor(color[3]));
	for (int x = 0; x < 4; x++) {
		glTexCoord2f(vectors[x].x, vectors[x].y);
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2f(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void DrawTextureFlippedHorizontal(GLuint texture, Vector2 position, int width, int height) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	Vector2 vectorsFlipped[4]{
		Vector2(1, 0),
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 1)
	};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	for (int x = 0; x < 4; x++) {
		glTexCoord2f(vectorsFlipped[x].x, vectorsFlipped[x].y);
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2f(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawRect(Vector2 position, int width, int height, double color[4]) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor4f(ConvertColor(color[0]), ConvertColor(color[1]), ConvertColor(color[2]), ConvertColor(color[3]));
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}