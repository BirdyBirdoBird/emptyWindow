#include "Chunk.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Chunk::Chunk(int x, int y) : X(x), Y(y) {
    initBlocks();
	fillBlockVec();
	buildBuffers();
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Chunk::initBlocks() {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < width; z++) {
                blockArray[x][y][z] = AIR; 
            }
        }
    }

    for (int x = 0; x < length; x++) {
        for (int z = 0; z < width; z++) {
            blockArray[x][0][z] = DIRT;
        }
    }
}

void Chunk::fillBlockVec() {
    unsigned int vertexOffset = 0;

    for (int x = 0; x < length; x++) {
        for (int y = 0; y < length; y++) {
            for (int z = 0; z < width; z++) {
                if (blockArray[x][y][z] != AIR) {
                    Block tempBlock(x, y, z);

                    //change block face bools when rendering them(culling)
                    alternateBlockFaces(&tempBlock, tempBlock.x, tempBlock.y, tempBlock.z);

                    //load vertecies and indecies to this alternated block
                    tempBlock.loadFaceVertecies();
                    tempBlock.loadFaceIndecies();

                    allVertices.insert(allVertices.end(), tempBlock.faceVertices.begin(), tempBlock.faceVertices.end());

                    for (unsigned int index : tempBlock.faceIndecies) {
                        allIndices.push_back(index + vertexOffset);
                    }

                    vertexOffset += tempBlock.faceVertices.size() / 6;  // 6 floats per vertex
                }
            }
        }
    }
}

void Chunk::alternateBlockFaces(Block* block, int x, int y, int z)
{
    // RIGHT (+X)
    if (getBlockType(x + 1, y, z) != AIR) {
        block->rightface = false;
    }
    // LEFT (-X)
    if (getBlockType(x - 1, y, z) != AIR) {
        block->leftface = false;
    }
    // FRONT (+Z)
    if (getBlockType(x, y, z + 1) != AIR) {
        block->frontface = false;
    }
    // BACK (-Z)
    if (getBlockType(x, y, z - 1) != AIR) {
        block->backface = false;
    }
    // TOP (+Y)
    if (getBlockType(x, y + 1, z) != AIR) {
        block->topface = false;
    }
    // BOTTOM (-Y)
    if (getBlockType(x, y - 1, z) != AIR) {
        block->bottomface = false;
    }
}

Chunk::blockType Chunk::getBlockType(int x, int y, int z)  {
    if (x < 0 || x >= width ||
        y < 0 || y >= height ||
        z < 0 || z >= length) {
        return AIR;  
    }
    return blockArray[x][y][z];
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

