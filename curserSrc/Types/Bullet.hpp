#pragma once

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../stb_image.h"

// std
#include <iostream>
#include <string>
#include <vector>

class Bullet
{
public:
    Bullet(glm::vec2 pos, float rot, glm::vec2 scale, float rad, unsigned int* tex)
    {
        position = pos;
        angle = rot;
        spriteAngle = rot;

        rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));

        imageSize = scale;
        collisionRadius = rad;
        texture = tex;
    }

    bool HasTexture() { return texture != nullptr; }
    unsigned int GetTexture() { return *texture; }

    glm::vec2 GetPosition() { return position; }
    float GetTrueRot() { return angle; }
    float GetRotation() { return spriteAngle; }

    void SetPosition(glm::vec2 pos) { position = pos; }
    void Translate(glm::vec2 pos) { position += pos; }
    void SetRotation(float rot)
    {
        spriteAngle = rot;
        rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    glm::mat4 GetMat() {
        glm::mat4 m(1.0f);

        m = glm::translate(m, glm::vec3(position.x, position.y, 1.0f));
        m *= rotMat;
        m = glm::scale(m, glm::vec3(imageSize.x, imageSize.y, 1.0f));

        return m;
    }

    bool HasCollided(glm::vec2 plPos, float rad)
    {
        float dist = glm::distance(plPos, position);

        // If the distance between the player and the bullet is less
        // than the sum of the two radius return true, otherwise
        // return false
        return dist < rad + collisionRadius;
    }

    // can be used by the developer to have different types of bullets
    int type = 0;

private:
    unsigned int* texture;

    float angle = 0.0f;
    float spriteAngle = 0.0f; // Affects visuals and not gameplay

    glm::mat4 rotMat = glm::mat4(1.0f);

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 imageSize = glm::vec2(1.0f);

    float collisionRadius = 1.0f;
};