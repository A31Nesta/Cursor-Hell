#include "Scene.hpp"


Scene::Scene()
{
	int reps = 12;

	for (int i = 0; i < reps; i++)
	{
		float distance = 3;
		float angle = 360.0f / reps * i;
		float x, y;
		x = std::cos(glm::radians(angle)) * distance;
		y = std::sin(glm::radians(angle)) * distance;

		Transform t;
		t.position = glm::vec2(x, y);
		t.rotation = angle;
		t.size = glm::vec2(0.25f, 0.25f);

		transforms.push_back(t);
	}
}

void Scene::Draw(unsigned int& shader)
{
	booletSprite.Draw(shader, transforms);
}