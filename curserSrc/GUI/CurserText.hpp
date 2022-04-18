#pragma once

#include "CurserUIQuad.hpp"

class Text
{
public:
    bool Enabled = true;

	Transform2D transform;
    Text();
    Text(std::string str);
    Text(std::wstring str);

    // Weird ctor
    void Init(std::string str);
    void Init(std::wstring str);

	void SetPosition(glm::vec2 newPos);
	void SetRotation(float newRot);
    void SetScale(float scale);
    void SetString(std::string str);
    void SetString(std::wstring str);
    std::string GetString() {
        return text;
    }

    float ScreenPosToCharPos(float pos, glm::vec2 aspectRatio = glm::vec2(16, 9), bool horizontal = true)
    {
        float trdotpos = horizontal ? transform.position.x : transform.position.y;
        float ar = horizontal ? aspectRatio.y : aspectRatio.x;

        float charposConverted = (pos - trdotpos)/(transform.scale * (ar / 100.0f));
        return charposConverted;
    }

    void SetMaxCharPosX(glm::vec2 aspectRatio = glm::vec2(16, 9))
    {
       maxcharposx = ScreenPosToCharPos(1, aspectRatio);
    }

    //void SetBaseColor(glm::vec3 color) { m_color = color; }

	void DrawText(unsigned int& shader);

private:
    bool usingWide = false;
    std::string text;
    std::wstring wtext;

    unsigned int VAO, VBO;
	//unsigned int texture;

    std::map<int, glm::vec3> m; // 2 first values for Pos | last value: 0 = SMALL QUAD and 1 = BIG QUAD

    std::vector<UIQuad> quads;
    std::vector<float> vertices;

    //glm::vec3 m_color = glm::vec3(1.0f);

    glm::vec2 charpos = glm::vec2(0.0f);

    float maxcharposx = 10;

    void SetupText(std::string str);
    void SetupText(std::wstring str);

    void GenerateMap();
    void CreateObjects();
};