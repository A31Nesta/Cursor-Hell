#include "Scene.hpp"


Scene::Scene()
{
	//InitScene();
}

void Scene::InitScene()
{
	/**
	Transform t;
	transforms.push_back(t);
	/**/
	int reps = 100;

	for (int i = 0; i < reps; i++)
	{
		float distance = 4;
		float angle = (360.0f / reps * i);
		float x, y;
		x = std::cos(glm::radians(angle)) * distance;
		y = std::sin(glm::radians(angle)) * distance;

		Transform t;
		t.position = glm::vec2(x, y);
		t.rotation = angle + 90;
		t.scale = glm::vec2(0.056f, 0.0875f);
		t.Apply();

		transforms.push_back(t);
	}
	/**/
}

void Scene::Draw(unsigned int& shader)
{
	booletSprite.Draw(shader, transforms);
}