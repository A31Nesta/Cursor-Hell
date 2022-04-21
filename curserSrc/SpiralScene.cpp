#include "SpiralScene.hpp"

void SpiralScene::InitScene()
{
	bullets.clear();

	numberOfBullets = 0;
	patternTimer = 0.0f;
	finished = false;
	for (int i = 0; i < numberOfMaxBoolets; i++)
	{
		Bullet t(origin, 0.0f, glm::vec2(0.056f, 0.0875f), 0.04f, &texture);

		bullets.push_back(t);
	}
}

uint8_t SpiralScene::Update(double dt)
{
	if (pv->gameOver) { return 0; }	

	// 0 = Game Over
	// 1 = Draw
	// 2 = Stop drawing

    patternTimer += dt;
	if (patternTimer > totalTime + timeAfterFinished) {
		return 2;
    }

	if (numberOfBullets < numberOfMaxBoolets) {
		genBulletTimer += dt * genBulletTimeMultiplier;
		if (genBulletTimer > 1) {
			numberOfBullets++;
			genBulletTimer = 0.0;
		}
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
			if (patternTimer < totalTime && ((pos.x > 10 || pos.x < -10) || (pos.y > 5 || pos.y < -5))) {
				bullets[i].SetPosition(origin);
			}
			if (numberOfBullets < numberOfMaxBoolets) bullets[i].SetRotation(angle + (100.0*dt*i/numberOfBullets - 90));
			bullets[i].Translate(glm::vec2(x, y));
		}

		if (!pv->lost) {
			if (bullets[i].HasCollided(pv->plPos, 0.04)) { 
				LoseLife();
			}
		}
	}

	if (patternTimer > totalTime) return 3;
	return 1;
}

uint8_t SpiralScene::Draw(unsigned int& shader, double dt)
{
	if (finished) return 2;
	uint8_t status = Update(dt);

	if (status != 2) booletSprite.Draw(shader, bullets, numberOfBullets);
	else finished = true;

	return status;
}