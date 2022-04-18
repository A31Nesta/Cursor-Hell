#pragma once
#include "Bullet.hpp"

class Polygon
{
public:
    float userTimer = 0.0f;

    Polygon() { hasBeenInitialized = false; }
    Polygon(uint8_t nVerts, uint32_t nInter, glm::vec2 pos, float ang, float rad, unsigned int* tex, float brad, glm::vec2 scl)
    {
        Generate(nVerts, nInter, pos, ang, rad, tex, brad, scl);
    }

    void Destroy()
    {
        if (!hasBeenInitialized) return;

        userTimer = 0.0f;

        vertices.clear();
        intermediateBullets.clear();
        hasBeenInitialized = false;
    }
    void Generate(uint8_t nVerts, uint32_t nInter, glm::vec2 pos, float ang, float rad, unsigned int* tex, float brad, glm::vec2 scl)
    {
        nVertices = nVerts;
        nIntermediateBullets = nInter;
        origin = pos;
        angle = ang;
        radius = rad;

        texture = tex;
        scale = scl;
        bulletRadius = brad;

        GeneratePolygon();
    }

    bool HasCollided(glm::vec2 plPos, float rad)
    {
        if (!hasBeenInitialized) return false;

        for (uint32_t i = 0; i < nVertices * nIntermediateBullets; i++) {
            if (intermediateBullets.at(i).HasCollided(plPos, rad)) return true;
        }
        for (uint8_t i = 0; i < nVertices; i++) {
            if (vertices.at(i).HasCollided(plPos, rad)) return true;
        }

        return false;
    }

    float GetRadius() { return radius; }
    void RelativeRadius(float rad)
    {
        radius += rad;
    }
    void RelativeRotate(float ang)
    {
        angle += ang;
    }
    void ChangeCenter(glm::vec2 newCen)
    {
        origin = newCen;
    }
    void UpdatePolygon()
    {
        if (!hasBeenInitialized) return;

        float individualAngle = 0.0f;
        glm::vec2 position;

        for (uint8_t i = 0; i < nVertices; i++)
        {
            individualAngle = i * (360.0f / nVertices);
            position.x = std::cos(individualAngle * M_PI / 180.0f);
            position.y = std::sin(individualAngle * M_PI / 180.0f);

            position *= radius;
            position += origin;

            vertices.at(i).SetPosition(position);
            vertices.at(i).SetRotation(individualAngle-90);
        }

        uint32_t run = 0;
        for (uint8_t i = 0; i < nVertices; i++)
        {
            glm::vec2 diffBetweenPoints;
            uint8_t p1 = i; 
            uint8_t p2 = 0;
            if (i != nVertices-1)
                p2 = i+1;

            diffBetweenPoints = vertices.at(p2).GetPosition() - vertices.at(p1).GetPosition();
            float totalLength = glm::length(diffBetweenPoints);
            float step = totalLength / nIntermediateBullets;
            glm::vec2 normalizedDiff = glm::normalize(diffBetweenPoints);

            for (uint32_t j = 0; j < nIntermediateBullets; j++)
            {
                uint32_t ind = j + (run * nIntermediateBullets);
                intermediateBullets.at(ind).SetPosition((normalizedDiff * (float)((j+1)*step)) + vertices.at(p1).GetPosition());
                intermediateBullets.at(ind).SetRotation(vertices.at(p1).GetRotation());
            }

            run++;
        }
    }

    std::vector<Bullet> GetBulletArr()
    {
        std::vector<Bullet> bv;
        bv.insert(bv.end(), vertices.begin(), vertices.end());
        bv.insert(bv.end(), intermediateBullets.begin(), intermediateBullets.end());

        return bv;
    }


private:
    bool hasBeenInitialized = false;

    uint8_t nVertices;
    uint32_t nIntermediateBullets;

    glm::vec2 origin;

    float angle;
    float radius;

    std::vector<Bullet> vertices;
    std::vector<Bullet> intermediateBullets;

    unsigned int* texture;
    float bulletRadius;
    glm::vec2 scale;

    void GeneratePolygon()
    {
        float individualAngle = 0.0f;
        glm::vec2 position;

        for (uint8_t i = 0; i < nVertices; i++)
        {
            individualAngle = i * (360.0f / nVertices);
            position.x = std::cos(individualAngle * M_PI / 180.0f);
            position.y = std::sin(individualAngle * M_PI / 180.0f);

            position *= radius;
            position += origin;

            Bullet b(position, individualAngle-90, scale, bulletRadius, texture);
            vertices.push_back(b);
        }

        for (uint8_t i = 0; i < nVertices; i++)
        {
            glm::vec2 diffBetweenPoints;
            uint8_t p1 = i; 
            uint8_t p2 = 0;
            if (i != nVertices-1)
                p2 = i+1;

            diffBetweenPoints = vertices.at(p2).GetPosition() - vertices.at(p1).GetPosition();
            float totalLength = glm::length(diffBetweenPoints);
            float step = totalLength / nIntermediateBullets;
            glm::vec2 normalizedDiff = glm::normalize(diffBetweenPoints);

            for (uint32_t j = 0; j < nIntermediateBullets; j++)
            {
                Bullet b((normalizedDiff * (float)((j+1)*step)) + vertices.at(p1).GetPosition(), vertices.at(p1).GetRotation(), scale, bulletRadius, texture);
                intermediateBullets.push_back(b);
            }
        }

        hasBeenInitialized = true;
    }
};