#include "Scene.hpp"


Scene::Scene()
{
	//InitScene();
}

void Scene::InitScene()
{
	
}

void Scene::Draw(unsigned int& shader)
{
	booletSprite.Draw(shader, bullets);
}