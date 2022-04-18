#include "CurserUIQuad.hpp"

UIQuad::UIQuad(glm::vec2 pos, glm::vec3 texCoords)
{
	if (texCoords.z == 1)
	{
		float vertsFull[30] =
		{
			 pos.x + 1.0f, pos.y + 1.0f, -1.0f,  texCoords.x + 0.1f, texCoords.y,				// top right
			 pos.x, pos.y + 1.0f,		 -1.0f,  texCoords.x, texCoords.y,						// top left
			 pos.x + 1.0f, pos.y,		 -1.0f,  texCoords.x + 0.1f, texCoords.y - 0.1f,		// bottom right
			 
			 pos.x + 1.0f, pos.y,		 -1.0f,  texCoords.x + 0.1f, texCoords.y - 0.1f,		// bottom right
			 pos.x, pos.y + 1.0f,		 -1.0f,  texCoords.x, texCoords.y,						// top left
			 pos.x, pos.y,				 -1.0f,  texCoords.x, texCoords.y - 0.1f				// bottom left 
		};
		for (int i = 0; i < 30; i++)
		{
			verts[i] = vertsFull[i];
		}
	}
	else //if (texCoords.z == 0)
	{
		float vertsFull[30] =
		{
			 pos.x + 0.5f, pos.y + 1.0f, -1.0f,  texCoords.x + 0.05f, texCoords.y,			// top right
			 pos.x, pos.y + 1.0f,		 -1.0f,  texCoords.x, texCoords.y,					// top left
			 pos.x + 0.5f, pos.y,		 -1.0f,  texCoords.x + 0.05f, texCoords.y - 0.1f,	// bottom right

			 pos.x + 0.5f, pos.y,		 -1.0f,  texCoords.x + 0.05f, texCoords.y - 0.1f,	// bottom right
			 pos.x, pos.y + 1.0f,		 -1.0f,  texCoords.x, texCoords.y,					// top left
			 pos.x, pos.y,				 -1.0f,  texCoords.x, texCoords.y - 0.1f			// bottom left 
		};
		for (int i = 0; i < 30; i++)
		{
			verts[i] = vertsFull[i];
		}
	}
}