#pragma once

#include "Quad.hpp"

// std
#include <cmath>

class Scene
{
public:
	Scene();

	void Draw(unsigned int& shader);

protected:
	void InitScene();

	Quad booletSprite;
	
	unsigned int numberOfMaxBoolets = 1000;
	std::vector<Transform> transforms;

	//std::vector<std::string> behaviours;
};

