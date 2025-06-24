#include "Chunk.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Chunk::Chunk(int x, int y) : X(x), Y(y) {
	fillBlockVec();
	buildBuffers();
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Chunk::fillBlockVec() {
    unsigned int vertexOffset = 0;

    for (int l = 0; l < length; l++) {
        for (int w = 0; w < width; w++) {
            Block tempBlock(l, 0, w);  // create temp block

            // Append vertices
            allVertices.insert(allVertices.end(), tempBlock.faceVertices.begin(), tempBlock.faceVertices.end());

            // Append indices with offset
            for (unsigned int index : tempBlock.faceIndecies) {
                allIndices.push_back(index + vertexOffset);
            }

            vertexOffset += tempBlock.faceVertices.size() / 6;  // 6 floats per vertex
        }
    }
}

void Chunk::buildBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(float), allVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, allIndices.size() * sizeof(unsigned int), allIndices.data(), GL_STATIC_DRAW);

    // Set vertex attrib pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Chunk::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, allIndices.size(), GL_UNSIGNED_INT, 0);
}