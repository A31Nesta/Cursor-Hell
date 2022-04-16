#pragma once
#include "Bullet.hpp"

class Polygon
{
public:
    Polygon() { hasBeenInitialized = false; }
    Polygon(uint8_t nVerts, uint32_t nInter, glm::vec2 pos, float ang, float rad, unsigned int* tex, float brad, glm::vec2 scl)
    {
        Generate(nVerts, nInter, pos, ang, rad, tex, brad, scl);
    }

    void Destroy()
    {
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

    void RelativeRadius(float rad)
    {
        radius += rad;
    }
    void RelativeRotate(float ang)
    {
        angle += ang;
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

        hasBeenInitialized = true;
    }
};