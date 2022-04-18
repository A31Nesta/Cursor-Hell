#include "SpiralScene.hpp"

void SpiralScene::InitScene()
{
	for (int i = 0; i < numberOfMaxBoolets; i++)
	{
		Bullet t(origin, 0.0f, glm::vec2(0.056f, 0.0875f), 0.04f, &texture);

		bullets.push_back(t);
	}

	GenTrap();
}

void SpiralScene::Update(double dt)
{
	if (lost) { 
		lostSize += glm::vec2(0.125f * 100 * dt);
		if (lostSize.x > 20.0f) {
			lost = false;
		}
	}
	if (gameOver) { return; }

	if (numberOfBullets < numberOfMaxBoolets) {
		numberOfBullets++;
		//std::cout << "NoB: " << std::to_string(numberOfBullets) << std::endl;
	}

	trapSpawnTimer += dt;
	if (trapSpawnTimer > 5.f) {
		GenTrap();
		trapSpawnTimer = 0.0f;
	}

	for (int i = 0; i < numberOfBullets; i++)
	{
		float distance = 0.01f;
		float angle;
		if (i == numberOfBullets-1) {
			angle = (360.0f / (50.0f-(i/50.0f)) * i);
			bullets[i].SetRotation(angle - 90);
		}
		else {
			angle = bullets[i].GetRotation() + 90;

			float x, y;
			x = std::cos(glm::radians(angle)) * distance * dt * 100;
			y = std::sin(glm::radians(angle)) * distance * dt * 100;

			glm::vec2 pos = bullets[i].GetPosition();
			if ((pos.x > 10 || pos.x < -10) || (pos.y > 5 || pos.y < -5)) {
				bullets[i].SetPosition(origin);
			}
			if (numberOfBullets < numberOfMaxBoolets) bullets[i].SetRotation(angle + 2.5f*i/numberOfBullets - 90);
			bullets[i].Translate(glm::vec2(x, y));
		}

		if (!lost) {
			if (bullets[i].HasCollided(plPos, 0.04)) { 
				LoseLife();
			}
		}
	}

	for (uint8_t i = 0; i < maxTraps; i++) {
		if (!trapsAvailable.at(i)) {
			Polygon& p = traps.at(i);
			if (p.GetRadius() > 2.0f && p.userTimer < 3) {
				p.ChangeCenter(plPos);
				p.RelativeRadius(-0.05f * 100 * dt);
				p.UpdatePolygon();
			}
			else {
				p.userTimer += dt;
				if (p.userTimer > 3) {
					p.RelativeRadius(0.02f * 100 * dt);
					p.UpdatePolygon();

					if (p.GetRadius() > 20.0f) {
						p.Destroy();
						trapsAvailable.at(i) = true;
					}
				}
			}
			if (!lost) {
				if (p.HasCollided(plPos, 0.04)) { 
					LoseLife();
				}
			}
		}
	}
}

void SpiralScene::Draw(unsigned int& shader, GLFWwindow* window, double dt)
{
	UpdatePlayer(window);
	Update(dt);

	booletSprite.Draw(shader, bullets, numberOfBullets);

	for (uint8_t i = 0; i < maxTraps; i++) {
		if (!trapsAvailable.at(i)) {
			std::vector<Bullet> bv = traps.at(i).GetBulletArr();
			booletSprite.Draw(shader, bv);
		}
	}

	if (lost) deathQuad.Draw(shader, lostPoint, lostSize);
	
	player.Draw(shader, plPos, plSize);
}