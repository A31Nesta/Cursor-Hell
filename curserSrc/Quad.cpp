#include "Quad.hpp"


Quad::Quad()
{
    GenerateObjects();

    LoadTexture("Assets/Sprites/checker.png");
}

void Quad::Draw(unsigned int& shader, std::vector<Bullet>& t, int numberOfBullets)
{
    glBindVertexArray(VAO);

    int NoB = numberOfBullets;

    if (numberOfBullets < 0) {
        NoB = t.size();
    }

    //std::cout << "NoB: " << std::to_string(NoB) << std::endl;

    for (int i = 0; i < NoB; i++) // 10, 5
    {
        glm::mat4 m4 = t[i].GetMat();

        if (t[i].HasTexture()) glBindTexture(GL_TEXTURE_2D, t[i].GetTexture());
        else glBindTexture(GL_TEXTURE_2D, texture);

        glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(m4));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Quad::Draw(unsigned int& shader, glm::vec2 pos, glm::vec2 scale)
{
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 m4(1.0f);
    m4 = glm::translate(m4, glm::vec3(pos.x, pos.y, 1.0f));
    m4 = glm::scale(m4, glm::vec3(scale.x, scale.y, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(m4));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::Draw()
{
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::ValidateQuad(unsigned int& shader)
{
    glUniform1i(glGetUniformLocation(shader, "texture1"), 0);
}

void Quad::GenerateObjects()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Quad::LoadTexture(std::string path)
{
    stbi_set_flip_vertically_on_load(true);
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
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
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
}