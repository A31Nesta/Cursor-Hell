#include "Scene.hpp"


Scene::Scene(float* x, float* y, glm::mat4 projv)
{
	xpos = x;
	ypos = y;
	projview = projv;

	bigLimit   = projview / glm::vec4( 1.0f,  1.0f, 1.0f, 0.0f);
	smallLimit = projview / glm::vec4(-1.0f, -1.0f, 1.0f, 0.0f);

	for (uint8_t i = 0; i < maxTraps; i++) {
		Polygon p; // make it unusable
		traps.push_back(p);
		trapsAvailable.push_back(true);
	}

	deathQuad.LoadTexture("Assets/Sprites/explosion.png");

	livesIndicator.SetPosition(glm::vec2(0.7f, 0.5f));
	livesIndicator.SetScale(0.3f);
	livesIndicator.Init("Lives: 3");
}

void Scene::InitScene()
{
	
}

void Scene::GenTrap()
{
	uint8_t ind;
	bool available = false;

	// Get first usable trap
	for (ind = 0; ind < maxTraps; ind++) {
		if (trapsAvailable.at(ind)) {
			available = true;
			break;
		}
	}
	if (!available)	{
		std::cout << "LOG: Failed to generate trap.\n    - All traps in pool are currently being used.\n";
		return;
	}

	traps.at(ind).Generate(ind+3, 75, plPos, 0.0f, 20.0f, &texture, 0.04f, glm::vec2(0.056f, 0.0875f));
	// traps.at(ind).UpdatePolygon();
	trapsAvailable.at(ind) = false;
}

void Scene::LoseLife()
{
	lost = true;
	lostPoint = plPos;
	lostSize = glm::vec2(0.25f);
	lives -= 1;
	livesIndicator.SetString("Lives: " + std::to_string(lives));

	if (lives < 0) {
		gameOver = true;
		livesIndicator.SetString("You suck");
	}
}

void Scene::UpdatePlayer(GLFWwindow* window)
{
	if (S_X == -1) {
		glfwGetWindowSize(window, &S_X, &S_Y);
	}

	plPos.x += *xpos/10;
	plPos.y += *ypos/7;

	glm::vec4 trpos = projview * glm::vec4(plPos.x, plPos.y, 1.0f, 0.0f);

	if (trpos.x > 1) plPos.x = bigLimit.x;
	if (trpos.y > 1) plPos.y = bigLimit.y;
	if (trpos.x < -1) plPos.x = smallLimit.x;
	if (trpos.y < -1) plPos.y = smallLimit.y;
}

void Scene::Draw(unsigned int& shader, GLFWwindow* window, double dt)
{
	booletSprite.Draw(shader, bullets);
}
void Scene::DrawText(unsigned int& textShader)
{
	glUseProgram(textShader);
	livesIndicator.DrawText(textShader);
}