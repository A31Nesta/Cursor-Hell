#include "Scene.hpp"


Scene::Scene(PlayerVars* pvars, CESoundMap* sm, CurserSoundPlayer* sp)
{
	pv = pvars;
	soundPlayer = sp;
	smap = sm;
	hit.setBuffer(sm->at("hit"));
	graze.setBuffer(sm->at("graze"));
}

void Scene::InitScene()
{
	
}

void Scene::LoseLife()
{
	pv->lost = true;
	pv->lives -= 1;
	
	hit.play();
}

void Scene::Draw(unsigned int& shader, double dt)
{
	booletSprite.Draw(shader, bullets);
}