#include "SpiralScene.hpp"

void SpiralScene::InitScene()
{
	int reps = 1000;

	for (int i = 0; i < reps; i++)
	{
		Transform t;
		t.scale = glm::vec2(0.056f, 0.0875f);

		transforms.push_back(t);
	}
}

void SpiralScene::Update(double dt)
{
	if (numberOfBullets < numberOfMaxBoolets) {
		numberOfBullets++;
		//std::cout << "NoB: " << std::to_string(numberOfBullets) << std::endl;
	}

	for (int i = 0; i < numberOfBullets; i++)
	{
		float distance = 0.01f;
		float angle = (360.0f / (50.0f-(i/50.0f)) * i);
		float x, y;
		x = std::cos(glm::radians(angle)) * distance * dt * 100;
		y = std::sin(glm::radians(angle)) * distance * dt * 100;

		glm::vec3 pos = glm::vec3(transforms[i].transform[3]);
		if ((pos.x > 10 || pos.x < -10) || (pos.y > 5 || pos.y < -5)) {
			transforms[i].transform = glm::mat4(1.0f);
		}

		//transforms[i].rotation = angle + 90;
		/**/
		if (i == numberOfBullets-1) {
			transforms[i].rotMatrix = glm::rotate(transforms[i].rotMatrix, glm::radians(angle - 90), glm::vec3(0, 0, 1.0f));
		}
		/**/

		transforms[i].Translate(x, y);
	}
}

void SpiralScene::Draw(unsigned int& shader, double dt)
{
	Update(dt);

	booletSprite.Draw(shader, transforms, numberOfBullets);
}