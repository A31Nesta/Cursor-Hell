// Cursor Hell
#include "CHEngine.hpp"

int main()
{
	if (!InitEngine())
	{
		std::cout << "What kind of potato are you using??" << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{


		EndUpdate();
	}
}