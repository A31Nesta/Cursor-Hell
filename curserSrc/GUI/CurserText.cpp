#include "CurserText.hpp"

void Text::SetupText(std::string str)
{
	text = str;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '\n') {
			charpos.y -= 1;
			charpos.x = 0;
		}
		else if (str[i] == ' ') {
			charpos.x += 1;
		}
		else {
			int c = str[i];
			glm::vec3 textCoord = m[c];	// THE VECTOR2 IN THE MAP THAT CORRESPONDS TO THE INT C

			UIQuad quad(charpos, textCoord);
			quads.push_back(quad);

			if (textCoord.z == 1) {
				charpos.x += 1;
			}
			else {
				charpos.x += 0.5f;
			}
		}

		if (charpos.x +1 >= maxcharposx) {
			charpos.x = 0;
			charpos.y -= 1;
		}
	}

	for (int i = 0; i < quads.size(); i++)
	{
		for (int j = 0; j < 30; j++)
		{
			float posComponent = quads[i].verts[j];
			vertices.push_back(posComponent);
		}
	}
}
void Text::SetupText(std::wstring str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '\n') {
			charpos.y -= 1;
			charpos.x = 0;
		}
		else if (str[i] == ' ') {
			charpos.x += 1;
		}
		else {
			int c = str[i];
			glm::vec3 textCoord = m[c];	// THE VECTOR2 IN THE MAP THAT CORRESPONDS TO THE INT C

			UIQuad quad(charpos, textCoord);
			quads.push_back(quad);

			if (textCoord.z == 1) {
				charpos.x += 1;
			}
			else {
				charpos.x += 0.5f;
			}
		}

		if (charpos.x + 1 >= maxcharposx) {
			charpos.x = 0;
			charpos.y -= 1;
		}
	}

	for (int i = 0; i < quads.size(); i++)
	{
		for (int j = 0; j < 30; j++)
		{
			float posComponent = quads[i].verts[j];
			vertices.push_back(posComponent);
		}
	}
}

Text::Text()
{
	SetMaxCharPosX();
}

Text::Text(std::string str)
{
	GenerateMap();
	SetupText(str);
	CreateObjects();

	SetMaxCharPosX();
}
Text::Text(std::wstring str)
{
	GenerateMap();
	SetupText(str);
	CreateObjects();

	SetMaxCharPosX();
}

void Text::Init(std::string str)
{
	GenerateMap();
	SetupText(str);
	CreateObjects();

	SetMaxCharPosX();
}
void Text::Init(std::wstring str)
{
	GenerateMap();
	SetupText(str);
	CreateObjects();

	SetMaxCharPosX();
}

void Text::GenerateMap()
{
	// FIRST ROW OF IMAGE	(UPPERCASE AND 3 SYMBOLS)
	m['A'] = glm::vec3(0.0f, 1.0f, 1);
	m['B'] = glm::vec3(0.1f, 1.0f, 1);
	m['C'] = glm::vec3(0.2f, 1.0f, 1);
	m['D'] = glm::vec3(0.3f, 1.0f, 1);
	m['E'] = glm::vec3(0.4f, 1.0f, 1);
	m['F'] = glm::vec3(0.5f, 1.0f, 1);
	m['G'] = glm::vec3(0.6f, 1.0f, 1);
	m['H'] = glm::vec3(0.7f, 1.0f, 1);
	m['I'] = glm::vec3(0.8f, 1.0f, 1);
	m['J'] = glm::vec3(0.9f, 1.0f, 1);

	// SECOND ROW OF IMAGE
	m['K'] = glm::vec3(0.0f, 0.9f, 1);
	m['L'] = glm::vec3(0.1f, 0.9f, 1);
	m['M'] = glm::vec3(0.2f, 0.9f, 1);
	m['N'] = glm::vec3(0.3f, 0.9f, 1);
	m['Ñ'] = glm::vec3(0.3f, 0.9f, 1);
	m['O'] = glm::vec3(0.5f, 0.9f, 1);
	m['P'] = glm::vec3(0.6f, 0.9f, 1);
	m['Q'] = glm::vec3(0.7f, 0.9f, 1);
	m['R'] = glm::vec3(0.8f, 0.9f, 1);
	m['S'] = glm::vec3(0.9f, 0.9f, 1);

	// THIRD ROW OF IMAGE
	m['T'] = glm::vec3(0.0f, 0.8f, 1);
	m['U'] = glm::vec3(0.1f, 0.8f, 1);
	m['V'] = glm::vec3(0.2f, 0.8f, 1);
	m['W'] = glm::vec3(0.3f, 0.8f, 1);
	m['X'] = glm::vec3(0.4f, 0.8f, 1);
	m['Y'] = glm::vec3(0.5f, 0.8f, 1);
	m['Z'] = glm::vec3(0.6f, 0.8f, 1);
	m[L'⊘'] = glm::vec3(0.7f, 0.8f, 1);
	m[L'▼'] = glm::vec3(0.8f, 0.8f, 1);
	m[L'▲'] = glm::vec3(0.9f, 0.8f, 1);

	// FOURTH ROW OF IMAGE	(LOWERCASE)
	m['a'] = glm::vec3(0.0f, 0.7f, 0);
	m['b'] = glm::vec3(0.05f, 0.7f, 0);
	m['c'] = glm::vec3(0.1f, 0.7f, 0);
	m['d'] = glm::vec3(0.15f, 0.7f, 0);
	m['e'] = glm::vec3(0.2f, 0.7f, 0);
	m['f'] = glm::vec3(0.25f, 0.7f, 0);
	m['g'] = glm::vec3(0.3f, 0.7f, 0);
	m['h'] = glm::vec3(0.35f, 0.7f, 0);
	m['i'] = glm::vec3(0.4f, 0.7f, 0);
	m['j'] = glm::vec3(0.45f, 0.7f, 0);

	m['k'] = glm::vec3(0.5f, 0.7f, 0);
	m['l'] = glm::vec3(0.55f, 0.7f, 0);
	m['m'] = glm::vec3(0.6f, 0.7f, 0);
	m['n'] = glm::vec3(0.65f, 0.7f, 0);
	m['ñ'] = glm::vec3(0.7f, 0.7f, 0);
	m['o'] = glm::vec3(0.75f, 0.7f, 0);
	m['p'] = glm::vec3(0.8f, 0.7f, 0);
	m['q'] = glm::vec3(0.85f, 0.7f, 0);
	m['r'] = glm::vec3(0.9f, 0.7f, 0);
	m['s'] = glm::vec3(0.95f, 0.7f, 0);

	// FIFTH ROW OF IMAGE	(LOWERCASE AND SYMBOLS)
	m['t'] = glm::vec3(0.0f, 0.6f, 0);
	m['u'] = glm::vec3(0.05f, 0.6f, 0);
	m['v'] = glm::vec3(0.1f, 0.6f, 0);
	m['w'] = glm::vec3(0.15f, 0.6f, 0);
	m['x'] = glm::vec3(0.2f, 0.6f, 0);
	m['y'] = glm::vec3(0.25f, 0.6f, 0);
	m['z'] = glm::vec3(0.3f, 0.6f, 0);
	m['¿'] = glm::vec3(0.35f, 0.6f, 0);
	m['?'] = glm::vec3(0.4f, 0.6f, 0);
	m['¡'] = glm::vec3(0.45f, 0.6f, 0);

	m['!'] = glm::vec3(0.5f, 0.6f, 0);
	m['.'] = glm::vec3(0.55f, 0.6f, 0);
	m[','] = glm::vec3(0.6f, 0.6f, 0);
	m[':'] = glm::vec3(0.65f, 0.6f, 0);
	m['('] = glm::vec3(0.7f, 0.6f, 0);
	m[')'] = glm::vec3(0.75f, 0.6f, 0);
	m['['] = glm::vec3(0.8f, 0.6f, 0);
	m[']'] = glm::vec3(0.85f, 0.6f, 0);
	m['\"'] = glm::vec3(0.9f, 0.6f, 0);
	m['\''] = glm::vec3(0.95f, 0.6f, 0);

	// SIXTH ROW OF IMAGE	(NUMBERS)
	m['1'] = glm::vec3(0.0f, 0.5f, 1);
	m['2'] = glm::vec3(0.1f, 0.5f, 1);
	m['3'] = glm::vec3(0.2f, 0.5f, 1);
	m['4'] = glm::vec3(0.3f, 0.5f, 1);
	m['5'] = glm::vec3(0.4f, 0.5f, 1);
	m['6'] = glm::vec3(0.5f, 0.5f, 1);
	m['7'] = glm::vec3(0.6f, 0.5f, 1);
	m['8'] = glm::vec3(0.7f, 0.5f, 1);
	m['9'] = glm::vec3(0.8f, 0.5f, 1);
	m['0'] = glm::vec3(0.9f, 0.5f, 1);

	// SEVENTH ROW OF IMAGE	(SYMBOLS)
	m['+'] = glm::vec3(0.0f, 0.4f, 1);
	m['-'] = glm::vec3(0.1f, 0.4f, 1);
	//m[''] = glm::vec3(0.2f, 0.4f, 1);
	m['/'] = glm::vec3(0.3f, 0.4f, 1);
	m['&'] = glm::vec3(0.4f, 0.4f, 1);
	m['*'] = glm::vec3(0.5f, 0.4f, 1);
}

void Text::CreateObjects()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), &quads[0].verts, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

void Text::SetPosition(glm::vec2 newPos)
{
	transform.position = newPos;
	SetMaxCharPosX();
}

void Text::SetRotation(float newRot)
{

}

void Text::SetScale(float scale)
{
	transform.scale = scale;
	SetMaxCharPosX();
}

void Text::SetString(std::string str)
{
	charpos = glm::vec2(0.0f);
	quads.clear();
	vertices.clear();

	SetupText(str);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	CreateObjects();
}
void Text::SetString(std::wstring str)
{
	SetupText(str);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	CreateObjects();
}

void Text::DrawText(unsigned int& shader)
{
	if (!Enabled)
		return;

	glUniform1f(glGetUniformLocation(shader, "size"), transform.scale);
	glUniform2fv(glGetUniformLocation(shader, "posAdd"), 1, &transform.position[0]);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, quads.size()*6);
}