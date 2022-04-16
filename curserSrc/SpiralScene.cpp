#include "SpiralScene.hpp"

void SpiralScene::InitScene()
{
	for (int i = 0; i < numberOfMaxBoolets; i++)
	{
		Bullet t(origin, 0.0f, glm::vec2(0.056f, 0.0875f), 0.05f, &texture);

		bullets.push_back(t);
	}

	GenTrap();
}

void SpiralScene::Update(double dt)
{
	//if (lost) { return; }

	if (numberOfBullets < numberOfMaxBoolets) {
		numberOfBullets++;
		//std::cout << "NoB: " << std::to_string(numberOfBullets) << std::endl;
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

		//if (bullets[i].HasCollided(plPos, 0.04)) { lost = true; }
	}
}

void SpiralScene::Draw(unsigned int& shader, GLFWwindow* window, double dt)
{
	UpdatePlayer(window);
	Update(dt);

	booletSprite.Draw(shader, bullets, numberOfBullets);
	std::vector<Bullet> bv = traps.at(0).GetBulletArr();
	booletSprite.Draw(shader, bv);
	player.Draw(shader, plPos, plSize);
}