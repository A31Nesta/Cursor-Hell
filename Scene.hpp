#pragma once

#include "Quad.hpp"

// std
#include <cmath>

class Scene
{
public:
	Scene();

	virtual void Draw(unsigned int& shader);

protected:
	virtual void InitScene();

	Quad booletSprite;
	
	unsigned int numberOfMaxBoolets = 1000;
	std::vector<Transform> transforms;

	//std::vector<std::string> behaviours;
};

