#pragma once
#include "PlayerVars.hpp"

float points = 0.0f;
int lastFrameLives = 3;


// int lives = 3;
// bool lost = false;
// bool gameOver = false;
// glm::vec2 plPos = glm::vec2(0.0f);
// glm::vec2 plSize = glm::vec2(1.0f);
PlayerVars pv(3, false, false, glm::vec2(-1, -3), glm::vec2(0.25f));

glm::vec4 smallLimit; // -1, -1 coordinate
glm::vec4 bigLimit;   //  1,  1 coordinate


uint32_t maxTraps = 5;
std::vector<Polygon> traps;
std::vector<bool> trapsAvailable;
float trapSize = 2.0f;
float trapSpawnTimer = 0.0f;

glm::vec2 lostPoint = glm::vec2(0.0f);
glm::vec2 lostSize;
Quad* booletSprite;
Quad* deathQuad;
Quad* player;

sf::Sound hit;
sf::Sound graze;

Text scoreIndicator;
Text livesIndicator;

void SetupPlayer()
{
    bigLimit   = projview / glm::vec4( 1.0f,  1.0f, 1.0f, 0.0f);
	smallLimit = projview / glm::vec4(-1.0f, -1.0f, 1.0f, 0.0f);

    for (uint8_t i = 0; i < maxTraps; i++) {
		Polygon p; // make it unusable
		traps.push_back(p);
		trapsAvailable.push_back(true);
	}

	booletSprite = new Quad();
	deathQuad = new Quad();
	player = new Quad();

	player->LoadTexture("Assets/Sprites/weirdplayer.png");

	hit.setBuffer(sounds.at("hit"));
	graze.setBuffer(sounds.at("graze"));

    deathQuad->LoadTexture("Assets/Sprites/explosion.png");

    scoreIndicator.SetPosition(glm::vec2(0.7f, 0.75f));
	scoreIndicator.SetScale(0.35f);
	scoreIndicator.Init("You are noob lol no points");

	livesIndicator.SetPosition(glm::vec2(0.7f, 0.5f));
	livesIndicator.SetScale(0.3f);
	livesIndicator.Init("Lives: 3");
}

void GenTrap()
{
	uint8_t ind;
	bool available = false;

	// Get first usable trap
	for (ind = 0; ind < maxTraps; ind++) {
		if (trapsAvailable.at(ind)) {
			available = true;
			break;
		}
	}
	if (!available)	{
		std::cout << "LOG: Failed to generate trap.\n    - All traps in pool are currently being used.\n";
		return;
	}

	traps.at(ind).Generate(ind+3, 75, pv.plPos, 0.0f, 20.0f, &arrowTex, 0.04f, glm::vec2(0.056f, 0.0875f));
	// traps.at(ind).UpdatePolygon();
	trapsAvailable.at(ind) = false;

	if (trapSize > 1.0f) trapSize -= 0.05f;
}

void UpdateLives()
{
	if (pv.lost) { 
		lostSize += glm::vec2(0.125f * 100 * deltaTime);
		if (lostSize.x > 20.0f) {
			pv.lost = false;
			lostSize = glm::vec2(0.25f);
		}
		if (lastFrameLives != pv.lives) {
			// pv.lives = 3;

			livesIndicator.SetString("Lives: " + std::to_string(pv.lives));

			lostPoint = pv.plPos;
			lostSize = glm::vec2(0.25f);

			if (pv.lives < 0) {
				pv.gameOver = true;
				livesIndicator.SetString("Game Over");
				sp.SayTotalScore(&sounds, (uint32_t)points);
			}
		}
	}
    lastFrameLives = pv.lives;
}

void UpdatePlayer()
{
	if (pv.gameOver)
		return;

	pv.plPos.x += xcur/10;
	pv.plPos.y += ycur/7;

	glm::vec4 trpos = projview * glm::vec4(pv.plPos.x, pv.plPos.y, 1.0f, 0.0f);

	if (trpos.x > 1) pv.plPos.x = bigLimit.x;
	if (trpos.y > 1) pv.plPos.y = bigLimit.y;
	if (trpos.x < -1) pv.plPos.x = smallLimit.x;
	if (trpos.y < -1) pv.plPos.y = smallLimit.y;

	points += deltaTime;
	scoreIndicator.SetString(std::to_string(points));

	trapSpawnTimer += deltaTime;
	if (trapSpawnTimer > 5.f) {
		GenTrap();
		trapSpawnTimer = 0.0f;
	}

	for (uint8_t i = 0; i < maxTraps; i++) {
		if (!trapsAvailable.at(i)) {
			Polygon& p = traps.at(i);
			if (p.GetRadius() > trapSize * 1.75f && p.userTimer < 3) {
				p.ChangeCenter(pv.plPos);
			}
			if (p.GetRadius() > trapSize && p.userTimer < 3) {
				p.RelativeRadius(-0.05f * 100 * deltaTime);
				p.UpdatePolygon();
			}
			else {
				p.userTimer += deltaTime;
				if (p.userTimer > 3) {
					p.RelativeRadius(0.02f * 100 * deltaTime);
					p.UpdatePolygon();

					if (p.GetRadius() > 20.0f) {
						p.Destroy();
						trapsAvailable.at(i) = true;
					}
				}
			}
			if (!pv.lost) {
				if (p.HasCollided(pv.plPos, 0.04)) { 
					hit.play();
					pv.lost = true;
					pv.lives -= 1;
					hit.play();
				}
			}
		}
	}
}

void UpdatePlayerRelated()
{
	UpdatePlayer();
	UpdateLives();
}

void DrawPlayerRelated()
{
	glUseProgram(shader);
	for (uint8_t i = 0; i < maxTraps; i++) {
		if (!trapsAvailable.at(i)) {
			std::vector<Bullet> bv = traps.at(i).GetBulletArr();
			booletSprite->Draw(shader, bv);
		}
	}
	if (pv.lost) deathQuad->Draw(shader, lostPoint, lostSize);
	glm::vec2 pos = pv.GetPos();
	glm::vec2 size = pv.GetSize();
	player->Draw(shader, pos, size);
}
void DrawText()
{
	glUseProgram(textShader);
	glBindTexture(GL_TEXTURE_2D, font);
	livesIndicator.DrawText(textShader);
	scoreIndicator.DrawText(textShader);
}

void DeletePtrs()
{
	delete booletSprite;
	delete deathQuad;
	delete player;
}


// TITLE SCREEN AND DEATH
bool isInTitle = true;

float deadCounter = 0.0f;
float opacity = 1.0f;

int selectedButton = 0;
bool canUp = true;
bool canDown = true;

Text playText;
Text exitText;

Text gameOverText;

bool inSplash = true;
float splashTimer;
Quad* splash;

Quad* titleBG;
Quad* deathBG;

Quad* titleLogo;
Quad* titleCur;

glm::vec2 titleLogoPos  = glm::vec2(-5.0f, 2.5f);
glm::vec2 titleLogoSize = glm::vec2(2.645f, 1.800f);

glm::vec2 titleCurPos  = glm::vec2(6.25f, -2.0f);
glm::vec2 titleCurSize = glm::vec2(0.75f);

void InitTitle()
{
	splash = new Quad();

	titleBG = new Quad();
	deathBG = new Quad();

	titleLogo = new Quad();
	titleCur = new Quad();

	splash->LoadTexture("Assets/Splash.png");

	titleLogo->LoadTexture("Assets/logoWhite.png");
	titleBG->LoadTexture("Assets/titleBG.png");
	titleCur->LoadTexture("Assets/Sprites/menuSelection.png");

	deathBG->LoadTexture("Assets/deadBG.png");

	playText.SetPosition(glm::vec2(0.75f, -0.5f));
	playText.SetScale(0.75f);
	playText.Init("Play");

	exitText.SetPosition(glm::vec2(0.75f, -0.9f));
	exitText.SetScale(0.75f);
	exitText.Init("Exit");

	gameOverText.SetPosition(glm::vec2(-0.25f, 0.0f));
	gameOverText.SetScale(0.75f);
	gameOverText.Init("Game Over");
}

void UpdateTitle(std::vector<Scene*>& scenes)
{
	// UP
	if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && canUp) {
		canUp = false;
		if (selectedButton > 0) selectedButton--;
	}
	else if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) && !canUp) {
		canUp = true;
	}

	// DOWN
	if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) && canDown) {
		canDown = false;
		if (selectedButton < 1) selectedButton++;
	}
	else if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) && !canDown) {
		canDown = true;
	}

	// ENTER
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		if (selectedButton == 0) {
			isInTitle = false;
			for (size_t j = 0; j < scenes.size(); j++) {
				scenes.at(j)->InitScene();
				opacity = 1.0f;
			}
		}
		else if (selectedButton == 1) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	// UPDATE CURSOR
	switch (selectedButton)
	{
	case 0:
		titleCurPos = glm::vec2(6.25f, -2.0f);
		break;
	
	case 1:
		titleCurPos = glm::vec2(6.25f, -3.75f);
		break;

	default:
		break;
	}
}

void DrawTitle(std::vector<Scene*>& scenes)
{
	UpdateTitle(scenes);

	glUseProgram(uiShader);
	titleBG->Draw();

	glUseProgram(shader);
	titleLogo->Draw(shader, titleLogoPos, titleLogoSize);
	titleCur->Draw(shader, titleCurPos, titleCurSize);

	glUseProgram(textShader);
	glBindTexture(GL_TEXTURE_2D, font);
	playText.DrawText(textShader);
	exitText.DrawText(textShader);
}

void DrawGameOver()
{
	deadCounter += deltaTime;
	glUseProgram(uiShader);

	bool deadPastLimit = deadCounter > 5;
	
	if (deadPastLimit) {
		opacity -= deltaTime * 2;
		if (opacity < 0) {
			opacity = 0.0f;
			deadCounter = 0.0f;

			pv.gameOver = false;
			pv.plPos = glm::vec2(-1, -3);
			pv.lives = 3;
			pv.lost = false;

			trapSize = 2.0f;
			trapSpawnTimer = 0.0f;
			points = 0.0f;
			for (uint32_t i = 0; i < trapsAvailable.size(); i++) {
				traps.at(i).Destroy();
				trapsAvailable.at(i) = true;
			}

			isInTitle = true;
		}

		titleBG->Draw();
		glUniform1f(glGetUniformLocation(uiShader, "opacity"), opacity);
	}
	deathBG->Draw();
	glUniform1f(glGetUniformLocation(uiShader, "opacity"), 1.0f);

	if (!deadPastLimit)
	{
		if (deadCounter < 1) {
			gameOverText.SetString("Game Over\nScore: " + std::to_string((int)points));
		}
		glUseProgram(textShader);
		glBindTexture(GL_TEXTURE_2D, font);
		gameOverText.DrawText(textShader);
	}
}

void DrawSplash()
{
	splashTimer += deltaTime;
	glUseProgram(uiShader);

	if (splashTimer > 4) {
		opacity -= deltaTime * 2;
		if (opacity < 0) {
			opacity = 0;
			inSplash = false;
		}

		titleBG->Draw();
		glUniform1f(glGetUniformLocation(uiShader, "opacity"), opacity);
	}

	splash->Draw();
	glUniform1f(glGetUniformLocation(uiShader, "opacity"), 1.0f);
}

void DeleteTitlePtrs()
{
	delete titleLogo;
	delete titleBG;
	delete titleCur;
	delete splash;
	delete deathBG;
}