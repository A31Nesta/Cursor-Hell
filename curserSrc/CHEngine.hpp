#pragma once

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

// Cursor Hell
#include "Scene.hpp"

GLFWwindow* window;

int SCR_WIDTH, SCR_HEIGHT;

int REN_WIDTH, REN_HEIGHT;
unsigned int quadVAO, quadVBO;
unsigned int framebuffer;
unsigned int textureColorbuffer;
unsigned int rbo;

float aspectx, aspecty;

unsigned int shader;
unsigned int screenShader;
unsigned int uiShader;
unsigned int textShader;

unsigned int font;
unsigned int arrowTex;

double lastTime = 0;

double deltaTime;
int counter = 0;
double timer = 0.0;
int fps = 0;
float invDT = 0.0;

glm::mat4 projection = glm::mat4(1.0f);

Quad* sidebar;

float sensitivity = 0.1f;
bool firstMouse = true;
float lastX = SCR_WIDTH/2;
float lastY = SCR_HEIGHT/2;
float xcur, ycur;

glm::mat4 projview = glm::mat4(1.0f);


// Sound
CESound hitsound;
CESound grazeSound;
CESound deadnotice1;
CESound deadnotice2;

CESound one;
CESound two;
CESound three;
CESound four;
CESound five;
CESound six;
CESound seven;
CESound eight;
CESound nine;
CESound zero;
CESound ten;
CESound eleven;
CESound twelve;
CESound teen;

CESound twenty;
CESound thirty;
CESound forty;
CESound fifty;
CESound sixty;
CESound seventy;
CESound eighty;
CESound ninety;
CESound hundred;
CESound thousand;

CESoundMap sounds;

CurserSoundPlayer sp;



void ProcessInput();
void CreateShader();
void CreateScreenShader();
void CreateUIShader();
void CreateTextShader();
unsigned int LoadTexture(std::string str);
void LoadSounds();

void CreateFramebufferObjects();
void CreateFBO();

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xposf = static_cast<float>(xpos);
    float yposf = static_cast<float>(ypos);

	if (firstMouse)
    {
        lastX = xposf;
        lastY = yposf;
        firstMouse = false;
    }

	float xoffset = xposf - lastX;
	float yoffset = lastY - yposf; // reversed since y-coordinates range from bottom to top
	lastX = xposf;
	lastY = yposf;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	xcur = xoffset;
	ycur = yoffset;
}

bool InitEngine(int mode = 0)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	/**/
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SCR_HEIGHT = (vidmode->height);
	SCR_WIDTH  = (vidmode->width);

	if (mode == 0) {
		SCR_WIDTH  = SCR_WIDTH  / 1.5f;
		SCR_HEIGHT = SCR_HEIGHT / 1.5f;
	}

#if FORCERES
	REN_WIDTH  = 1920;
	REN_HEIGHT = 1080;
#else
	/**
	REN_HEIGHT = SCR_HEIGHT / 1.5f;
	REN_WIDTH  = SCR_WIDTH  / 1.5f;
	/**/
	REN_HEIGHT = SCR_HEIGHT;
	REN_WIDTH  = SCR_WIDTH;
	/**/
#endif

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cursor Hell - CursEr Engine", mode == 1 ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	CreateShader();
	CreateScreenShader();
	CreateUIShader();
	CreateTextShader();

	LoadSounds();

	CreateFramebufferObjects();
	CreateFBO();

	float gcd = std::gcd(SCR_WIDTH, SCR_HEIGHT);

	std::cout << "GCD: " << std::to_string(gcd) << std::endl;

	aspectx = SCR_WIDTH  / gcd;
	aspecty = SCR_HEIGHT / gcd;

	std::cout << "Aspect Ratio: " << std::to_string(aspectx) << ":" << std::to_string(aspecty) << std::endl;

	float aspectRatio = aspectx/aspecty;
	aspecty = 9;
	aspectx = 9 * aspectRatio;

	std::cout << "Corrected Aspect Ratio: " << std::to_string(aspectx) << ":" << std::to_string(aspecty) << std::endl;

	projection = glm::ortho(-((float)aspectx)/2, ((float)aspectx)/2, -((float)aspecty)/2, ((float)aspecty)/2, 0.1f, 100.0f);
	//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);

#if NOGRAB
	std::cout << "THIS IS A DEBUG VERSION!!\nThis version does not grab the mouse, making the game unplayable\n-----------------\n";
#else
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
	projview = projection * view;

	sidebar = new Quad();
	sidebar->LoadTexture("./Assets/Background2.png");

	arrowTex = LoadTexture("Assets/Sprites/Cursor.png");


	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD); // this is default
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	lastTime = glfwGetTime();

	return true;
}

void CreateFramebufferObjects()
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	// screen quad VAO
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
void CreateFBO()
{
	// framebuffer configuration
	// -------------------------
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, REN_WIDTH, REN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, REN_WIDTH, REN_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}


void LoadSounds()
{
	hitsound.loadFromFile("Assets/Sounds/wav/CH_Hit.wav");
	grazeSound.loadFromFile("Assets/Sounds/wav/CH_Graze.wav");
	deadnotice1.loadFromFile("Assets/Sounds/wav/CH_Lost_Notice1.wav");
	deadnotice2.loadFromFile("Assets/Sounds/wav/CH_Lost_Notice2.wav");

	one.loadFromFile("Assets/Sounds/wav/1.wav");
	two.loadFromFile("Assets/Sounds/wav/2.wav");
	three.loadFromFile("Assets/Sounds/wav/3.wav");
	four.loadFromFile("Assets/Sounds/wav/4.wav");
	five.loadFromFile("Assets/Sounds/wav/5.wav");
	six.loadFromFile("Assets/Sounds/wav/6.wav");
	seven.loadFromFile("Assets/Sounds/wav/7.wav");
	eight.loadFromFile("Assets/Sounds/wav/8.wav");
	nine.loadFromFile("Assets/Sounds/wav/9.wav");
	zero.loadFromFile("Assets/Sounds/wav/0.wav");
	ten.loadFromFile("Assets/Sounds/wav/10.wav");
	eleven.loadFromFile("Assets/Sounds/wav/11.wav");
	twelve.loadFromFile("Assets/Sounds/wav/12.wav");
	teen.loadFromFile("Assets/Sounds/wav/teen.wav");
	twenty.loadFromFile("Assets/Sounds/wav/20.wav");
	thirty.loadFromFile("Assets/Sounds/wav/30.wav");
	forty.loadFromFile("Assets/Sounds/wav/40.wav");
	fifty.loadFromFile("Assets/Sounds/wav/50.wav");
	sixty.loadFromFile("Assets/Sounds/wav/60.wav");
	seventy.loadFromFile("Assets/Sounds/wav/70.wav");
	eighty.loadFromFile("Assets/Sounds/wav/80.wav");
	ninety.loadFromFile("Assets/Sounds/wav/90.wav");
	hundred.loadFromFile("Assets/Sounds/wav/100.wav");
	thousand.loadFromFile("Assets/Sounds/wav/1000.wav");

	sounds["hit"]		= hitsound;
	sounds["graze"]		= grazeSound;
	sounds["dnotice1"]	= deadnotice1;
	sounds["dnotice2"]	= deadnotice2;
	sounds["one"]		= one;
	sounds["two"]		= two;
	sounds["three"]		= three;
	sounds["four"]		= four;
	sounds["five"]		= five;
	sounds["six"]		= six;
	sounds["seven"]		= seven;
	sounds["eight"]		= eight;
	sounds["nine"]		= nine;
	sounds["zero"]		= zero;
	sounds["ten"]		= ten;
	sounds["eleven"]	= eleven;
	sounds["twelve"]	= twelve;
	sounds["teen"]		= teen;
	sounds["twenty"]	= twenty;
	sounds["thirty"]	= thirty;
	sounds["forty"]		= forty;
	sounds["fifty"]		= fifty;
	sounds["sixty"]		= sixty;
	sounds["seventy"]	= seventy;
	sounds["eigthy"]	= eighty;
	sounds["ninety"]	= ninety;
	sounds["hundred"]	= hundred;
	sounds["thousand"]	= thousand;
}

void CalcFPS()
{
	double thisTime = glfwGetTime();
	deltaTime = thisTime - lastTime;

	lastTime = thisTime;

	invDT = 1 / deltaTime;

	if (timer < 1) {
		timer += deltaTime;
		counter++;
	}
	else {
		fps = counter;
		std::cout << "FPS: " << fps << std::endl;
		//std::cout << "FPS (InvDT): " << invDT << std::endl << std::endl;

		counter = 0;
		timer = 0;
	}
}

void DrawInterface()
{
	glUseProgram(uiShader);
	sidebar->Draw();
}

void EndUpdate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// rendering
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(screenShader);
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

	xcur = 0;
	ycur = 0;

	glfwSwapBuffers(window);
	glfwPollEvents();

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, REN_WIDTH, REN_HEIGHT);

	// rendering
	glClearColor(0.0f, 0.05f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(shader);
}

// Totally not stolen from learnopengl.com
void CreateShader()
{
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		""
		"out vec2 TexCoord;\n"
		""
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 transform;\n"
		""
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * transform * vec4(aPos, 1.0);\n"
		"   TexCoord = vec2((aPos.x+1)/2, (aPos.y+1)/2);\n"
		"}\0"
		;
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		""
		"in vec2 TexCoord;\n"
		""
		"uniform sampler2D texture1;\n"
		""
		"void main()\n"
		"{\n"
		"   vec4 color = texture(texture1, TexCoord);\n"
		"	//if (color.a < 0.5)\n"
		"	//	discard;\n"
		""
		"   //FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"   FragColor = color;\n"
		"}\n\0"
		;

	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);
	// check for linking errors
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "texture1"), 0);
}
void CreateScreenShader()
{
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec2 aPos;\n"
		"layout(location = 1) in vec2 aTexCoords;\n"

		"out vec2 TexCoords;\n"

		"void main()\n"
		"{\n"
			"TexCoords = aTexCoords;\n"
			"gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
		"}"
		;
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec2 TexCoords;\n"

		"uniform sampler2D screenTexture;\n"

		"void main()\n"
		"{\n"
			"vec4 col = texture(screenTexture, TexCoords);\n"
			"FragColor = col;\n"
			"//FragColor = vec4(TexCoords.x, TexCoords.y, 0.0, 1.0);\n"
		"}\0"
		;

	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	screenShader = glCreateProgram();
	glAttachShader(screenShader, vertexShader);
	glAttachShader(screenShader, fragmentShader);
	glLinkProgram(screenShader);
	// check for linking errors
	glGetProgramiv(screenShader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(screenShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(screenShader);
	glUniform1i(glGetUniformLocation(screenShader, "screenTexture"), 0);

	glUseProgram(shader);
}
void CreateUIShader()
{
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec2 aPos;\n"

		"out vec2 TexCoords;\n"

		"void main()\n"
		"{\n"
			"TexCoords = vec2((aPos.x+1)/2, (aPos.y+1)/2);\n"
			"gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
		"}"
		;
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec2 TexCoords;\n"

		"uniform sampler2D uitex;\n"

		"void main()\n"
		"{\n"
			"vec4 col = texture(uitex, TexCoords);\n"
			"if (col.a < 0.5) { discard; }\n"
			"FragColor = vec4(col.rgb, 1.0);\n"
			"//FragColor = vec4(TexCoords.x, TexCoords.y, 0.0, 1.0);\n"
		"}\0"
		;

	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	uiShader = glCreateProgram();
	glAttachShader(uiShader, vertexShader);
	glAttachShader(uiShader, fragmentShader);
	glLinkProgram(uiShader);
	// check for linking errors
	glGetProgramiv(uiShader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(uiShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(uiShader);
	glUniform1i(glGetUniformLocation(uiShader, "uitex"), 0);

	glUseProgram(shader);
}
void CreateTextShader()
{
	const char* vertexShaderSource =
		"#version 330 core\n"

		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 atexCoords;\n"

		"uniform float size;\n"
		"uniform vec2 aspectRatio = vec2(16, 9);\n"
		"uniform vec2 posAdd;\n"

		"int nextLine;\n"

		"out vec2 TexCoord;\n"

		"void main()\n"
		"{\n"
			"vec3 totalSize = vec3(size * (aspectRatio.y/100), size * (aspectRatio.x/100), size);\n"
			
			"vec3 posPre = vec3(totalSize * aPos);\n"
			"vec3 position = vec3(posPre.x + posAdd.x, posPre.y + posAdd.y, posPre.z);\n"
			
			"gl_Position = vec4(position, 1.0);\n"
			
			"TexCoord = atexCoords;\n"
		"}\0"
		;
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec2 TexCoord;\n"

		"uniform sampler2D font;\n"

		"void main()\n"
		"{\n"
			"vec4 texColor = texture(font, TexCoord);\n"
			"if(texColor.a < 0.1)\n"
				"discard;\n"
			"FragColor = vec4(texColor.rgb, 1.0);\n"
		"}\0"
		;

	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	textShader = glCreateProgram();
	glAttachShader(textShader, vertexShader);
	glAttachShader(textShader, fragmentShader);
	glLinkProgram(textShader);
	// check for linking errors
	glGetProgramiv(textShader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(textShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(textShader);
	glUniform1i(glGetUniformLocation(textShader, "font"), 0);

	font = LoadTexture("Assets/Sprites/Arial.png");

	glUseProgram(shader);
}

unsigned int LoadTexture(std::string str)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char* data = stbi_load(str.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

	return texture;
}

void ProcessInput()
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}



/*
void DrawQuad(Quad& q, std::vector<Transform> t)
{
	q.Draw(shader, t);
}
*/
void DrawScene(Scene& s)
{
	s.Draw(shader, deltaTime);
}