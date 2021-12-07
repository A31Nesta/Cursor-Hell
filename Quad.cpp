#include "Quad.hpp"


Quad::Quad()
{
    GenerateObjects();
}

void Quad::Draw(unsigned int& shader, std::vector<Transform> t)
{
    glBindVertexArray(VAO);

    for (int i = 0; i < t.size(); i++)
    {
        setTransform(t[i]);
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(t[i].position.x, t[i].position.y, 1.0f));
        transform = glm::rotate(transform, glm::radians(t[i].rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(t[i].size.x, t[i].size.y, 1.0f));

        unsigned int transformLoc = glGetUniformLocation(shader, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
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