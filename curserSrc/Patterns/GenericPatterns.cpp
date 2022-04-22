#include "GenericPatterns.hpp"

void CHPattern1::InitScene()
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

	moosic.openFromFile("Assets/ShittyMusic/2.wav");
	moosic.setVolume(volume);
	startMusic = true;
}

uint8_t CHPattern1::Update(double dt)
{
	if (pv->gameOver) { return 0; }	

    // 0 = Game Over
	// 1 = Draw
	// 2 = Stop drawing
    // 3 = Draw but start with next

	StartMusic();

    patternTimer += dt;
	if (patternTimer > totalTime + timeAfterFinished) {
		return 2;
    }

	if (pv->lives < 0 && moosic.getStatus() == sf::SoundSource::Status::Playing) {
		moosic.stop();
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
        originXOffset = std::sin(i) * 7;

        if (pv->plPos.y > 3.0f) PlayerIsOnTop = true;
        else PlayerIsOnTop = false;

		float distance = 0.0075f;
		float angle;
		if (i == numberOfBullets-1) {
			angle = ((90.0f / 10.0f) * (float)(i%10) - 135);
            bullets[i].SetPosition(glm::vec2(origin.x + originXOffset, 3.0f));
			if (PlayerIsOnTop) bullets[i].SetRotation(angle + 90);
            else bullets[i].SetRotation(angle - 90);
		}
		else {
			angle = bullets[i].GetRotation() + 90;

			float x, y;
			x = std::cos(glm::radians(angle)) * distance * dt * 100;
			y = std::sin(glm::radians(angle)) * distance * dt * 100;

			glm::vec2 pos = bullets[i].GetPosition();
			if (patternTimer < totalTime && ((pos.x > 10 || pos.x < -10) || (pos.y > 5 || pos.y < -5))) {
				bullets[i].SetPosition(glm::vec2(origin.x + originXOffset, 3.0f));
                if (PlayerIsOnTop) bullets[i].SetRotation(angle + 90);
                else bullets[i].SetRotation(angle - 90);
			}
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

uint8_t CHPattern1::Draw(unsigned int& shader, double dt)
{
	if (finished) return 2;
	uint8_t status = Update(dt);

	if (status != 2) booletSprite.Draw(shader, bullets, numberOfBullets);
	else finished = true;

    return status;
}


// CHPATTERN2
void CHPattern2::InitScene()
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

	moosic.openFromFile("Assets/ShittyMusic/3.wav");
	moosic.setVolume(volume);
	startMusic = true;
}

uint8_t CHPattern2::Update(double dt)
{
	if (pv->gameOver) { return 0; }	

    // 0 = Game Over
	// 1 = Draw
	// 2 = Stop drawing
    // 3 = Draw but start with next

	StartMusic();

    patternTimer += dt;
	if (patternTimer > totalTime + timeAfterFinished) {
		return 2;
    }

	if (pv->lives < 0 && moosic.getStatus() == sf::SoundSource::Status::Playing) {
		moosic.stop();
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
		float distance = 0.01f * ((float)(i%5)/2.0f);
		float angle;
		if (i == numberOfBullets-1) {
			angle = (360.0f / (50.0f-(i/50.0f)) * i);
            bullets[i].SetPosition(origin);
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

uint8_t CHPattern2::Draw(unsigned int& shader, double dt)
{
	if (finished) return 2;

	uint8_t status = Update(dt);

	if (status != 2) booletSprite.Draw(shader, bullets, numberOfBullets);
	else finished = true;

    return status;
}

// CHPATTERN3
void CHPattern3::InitScene()
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

	moosic.openFromFile("Assets/ShittyMusic/1.wav");
	moosic.setVolume(volume);
	startMusic = true;
}

uint8_t CHPattern3::Update(double dt)
{
	if (pv->gameOver) { return 0; }	

    // 0 = Game Over
	// 1 = Draw
	// 2 = Stop drawing
    // 3 = Draw but start with next

	StartMusic();

    patternTimer += dt;
	if (patternTimer > totalTime + timeAfterFinished) {
		return 2;
    }

	if (pv->lives < 0 && moosic.getStatus() == sf::SoundSource::Status::Playing) {
		moosic.stop();
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
		float distance = 0.01f * ((float)(i%5)/2.0f);
		float angle;
		if (i == numberOfBullets-1) {
			angle = (360.0f / (50.0f-(i/50.0f)) * i);
            bullets[i].SetPosition(origin);
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

uint8_t CHPattern3::Draw(unsigned int& shader, double dt)
{
	if (finished) return 2;

	uint8_t status = Update(dt);

	if (status != 2) booletSprite.Draw(shader, bullets, numberOfBullets);
	else finished = true;

    return status;
}