#pragma once
#include "../Scene.hpp"

class CHPattern1 : public Scene
{
public:
    CHPattern1(PlayerVars* pvars, CESoundMap* sm, CurserSoundPlayer* sp) 
		: Scene(pvars, sm, sp)
    {
        LoadTexture("Assets/Sprites/Cursor.png");
		  InitScene();
    }

    float originXOffset = 0.0f;

    bool PlayerIsOnTop = false;

    void InitScene();

    uint8_t Draw(unsigned int& shader, double dt);

private:
    uint8_t Update(double dt);    
};

// CHPATTERN2
class CHPattern2 : public Scene
{
public:
    CHPattern2(PlayerVars* pvars, CESoundMap* sm, CurserSoundPlayer* sp) 
		: Scene(pvars, sm, sp)
    {
        LoadTexture("Assets/Sprites/Cursor.png");
		  InitScene();
    }

    void InitScene();

    uint8_t Draw(unsigned int& shader, double dt);

private:
    uint8_t Update(double dt);    
};

// CHPATTERN
class CHPattern3 : public Scene
{
public:
    CHPattern3(PlayerVars* pvars, CESoundMap* sm, CurserSoundPlayer* sp) 
		: Scene(pvars, sm, sp)
    {
        LoadTexture("Assets/Sprites/Cursor.png");
		  InitScene();
    }

    void InitScene();

    uint8_t Draw(unsigned int& shader, double dt);

private:
    uint8_t Update(double dt);    
};