#pragma once

// OpenGL
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

struct PlayerVars
{
    PlayerVars(int l, bool go, bool lo, glm::vec2 plp, glm::vec2 pls) {
        lives = l;
        gameOver = go;
        lost = lo;
        plPos = plp;
        plSize = pls;
    }
    glm::vec2 GetPos() { return plPos; }
    glm::vec2 GetSize() { return plSize; }
    int lives;
	bool gameOver;
	bool lost;
	glm::vec2 plPos;
	glm::vec2 plSize;
};