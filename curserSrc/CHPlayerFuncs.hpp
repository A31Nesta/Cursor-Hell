#pragma once
#include "PlayerVars.hpp"

float points = 0.0f;
int lastFrameLives = 3;


// int lives = 3;
// bool lost = false;
// bool gameOver = false;
// glm::vec2 plPos = glm::vec2(0.0f);
// glm::vec2 plSize = glm::vec2(1.0f);
PlayerVars pv(3, false, false, glm::vec2(0.0f), glm::vec2(0.075f));

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
		}
	}
    if (lastFrameLives != pv.lives) {
		// pv.lives = 3;

        livesIndicator.SetString("Lives: " + std::to_string(pv.lives));

        lostPoint = pv.plPos;
        lostSize = glm::vec2(0.25f);

        if (pv.lives < 0) {
            pv.gameOver = true;
            livesIndicator.SetString("You suck");
            sp.SayTotalScore(&sounds, (uint32_t)points);
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