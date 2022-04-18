#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <map>
#include <string>
#include <vector>

struct Transform2D
{
	glm::vec2 position = glm::vec2(-0.5f);
	float rotation = 0.0f;
    float scale = 0.75f;

    glm::vec2 otherPos = glm::vec2(1.0f);
};

enum QuadType
{
    FULL_QUAD,
    HALF_QUAD
};

class UIQuad
{
public:
    float verts[30];

    UIQuad(glm::vec2 pos, glm::vec3 texCoords);
private:

};