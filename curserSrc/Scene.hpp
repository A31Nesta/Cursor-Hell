#pragma once

#include "Quad.hpp"
#include "Types/Polygon.hpp"

// std
#include <cmath>

class Scene
{
public:
	Scene(float* x, float* y, glm::mat4 projv);

	virtual void Draw(unsigned int& shader, GLFWwindow* window, double dt);

protected:
	virtual void InitScene();

	void GenTrap(); // Execute after texture is set
	void UpdatePlayer(GLFWwindow* window);

	void LoadTexture(std::string path)
	{
		stbi_set_flip_vertically_on_load(true);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	unsigned int texture;
	Quad booletSprite;

	int S_X = -1, S_Y = -1;
	float* xpos;
	float* ypos;

	glm::mat4 projview;
	glm::vec4 smallLimit; // -1, -1 coordinate
	glm::vec4 bigLimit;   //  1,  1 coordinate

	bool lost = false;

	glm::vec2 plPos = glm::vec2(0.0f);
	glm::vec2 plSize = glm::vec2(0.075f);
	Quad player;

	glm::vec2 origin = glm::vec2(-1, 1);
	int numberOfBullets = 0;
	
	unsigned int numberOfMaxBoolets = 1000;
	std::vector<Bullet> bullets;

	uint32_t maxTraps = 5;
	std::vector<Polygon> traps;
	std::vector<bool> trapsAvailable;

	//std::vector<std::string> behaviours;
};

