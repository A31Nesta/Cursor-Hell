#pragma once

#include "Quad.hpp"
#include "Types/Polygon.hpp"
#include "GUI/CurserText.hpp"

#include "Sound/CurserSound.hpp"
#include "PlayerVars.hpp"

// std
#include <cmath>

class Scene
{
public:
	Scene(PlayerVars* pvars, CESoundMap* sm, CurserSoundPlayer* sp);

	virtual uint8_t Draw(unsigned int& shader, double dt);
	void DrawText(unsigned int& textShader);

protected:
	virtual void InitScene();

	void LoseLife();

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


	CurserSoundPlayer* soundPlayer;

	CESoundMap* smap;
	sf::Sound hit;
	sf::Sound graze;

	float patternTimer = 0.0f;
	
	float totalTime = 30.0f; // After this time (seconds), no more bullets will be generated
	float timeAfterFinished = 10.0f; // Time to clean all bullets from the screen

	unsigned int texture;
	Quad booletSprite;

	PlayerVars* pv;
	// int* lives;
	// bool* gameOver;
	// bool* lost;
	// glm::vec2* plPos;  // = glm::vec2(0.0f);
	// glm::vec2* plSize; // = glm::vec2(0.075f);

	glm::vec2 origin = glm::vec2(-1, 1);
	int numberOfBullets = 0;
	
	unsigned int numberOfMaxBoolets = 1000;
	std::vector<Bullet> bullets;
};

