#include "Chunk.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "FastNoiseLite.h"
#include "GrassBlock.h"
#include "Constants.h"
#include "map"
using namespace Constants;


Chunk::Chunk(int x, int z, FastNoiseLite& noise, std::map<std::pair<int, int>, Chunk*>* worldChunks) : noise(noise), chunkX(x), chunkZ(z), worldChunks(worldChunks) {
    chunkBlockOffsetX = x * 16;
    chunkBlockOffsetZ = z * 16;

    std::cout << "Created Chunk at (" << chunkX << ", " << chunkZ << ")\n";
    initBlocks();
	//fillBlockVec();
	//buildBuffers();
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Chunk::initBlocks() {
    for (int x = 0; x < CHUNK_LENGTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                blockArray[x][y][z] = AIR; 
            }
        }
    }

    for (int x = 0; x < CHUNK_LENGTH; x++) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            int h = generateHeight(x + chunkBlockOffsetX, z + chunkBlockOffsetZ);
            blockArray[x][h][z] = GRASS;
            fillDown(x, h, z);
        }
    }
}

void Chunk::fillBlockVec() {
    unsigned int vertexOffset = 0;

    for (int x = 0; x < CHUNK_LENGTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {

                if (blockArray[x][y][z] != AIR) {
                    Block* tempBlock;
                    if (blockArray[x][y][z] == GRASS) {
                        tempBlock = new GrassBlock(x + chunkBlockOffsetX, y, z + chunkBlockOffsetZ);
                    }
                    else {
                        tempBlock = new Block(x + chunkBlockOffsetX, y, z + chunkBlockOffsetZ);
                    }

                    //change block face bools when rendering them(culling)
                    alternateBlockFaces(tempBlock, x, y, z);

                    //load vertecies and indecies to this alternated block
                    tempBlock->loadFaceVertecies(); 
                    tempBlock->loadFaceIndecies();

                    allVertices.insert(allVertices.end(), tempBlock->faceVertices.begin(), tempBlock->faceVertices.end());

                    for (unsigned int index : tempBlock->faceIndecies) {
                        allIndices.push_back(index + vertexOffset);
                    }

                    vertexOffset += tempBlock->faceVertices.size() / 6;  // 6 floats per vertex

                    delete tempBlock;
                }
                
            }
        }
    }
}

void Chunk::alternateBlockFaces(Block* block, int x, int y, int z)
{
    // Lambda to check neighbor block type, even outside current chunk
    auto getBlockTypeWithChunk = [&](int nx, int ny, int nz) -> blockType {
        // If inside current chunk
        if (nx >= 0 && nx < CHUNK_WIDTH &&
            ny >= 0 && ny < CHUNK_HEIGHT &&
            nz >= 0 && nz < CHUNK_LENGTH) {
            return blockArray[nx][ny][nz];
        }

        // Outside current chunk, check neighboring chunk
        int neighborChunkX = chunkX;
        int neighborChunkZ = chunkZ;
        int localX = nx, localZ = nz;

        if (nx < 0) {
            neighborChunkX -= 1;
            localX = CHUNK_WIDTH - 1;
        }
        else if (nx >= CHUNK_WIDTH) {
            neighborChunkX += 1;
            localX = 0;
        }

        if (nz < 0) {
            neighborChunkZ -= 1;
            localZ = CHUNK_LENGTH - 1;
        }
        else if (nz >= CHUNK_LENGTH) {
            neighborChunkZ += 1;
            localZ = 0;
        }

        // Check if neighbor chunk exists
        auto it = worldChunks->find({ neighborChunkX, neighborChunkZ });
        if (it != worldChunks->end()) {
            Chunk* neighbor = it->second;
            if (ny >= 0 && ny < CHUNK_HEIGHT) {
                return neighbor->getBlockType(localX, ny, localZ);
            }
        }

        return AIR; // No neighbor chunk means air
        };

    // Check all 6 directions
    if (getBlockTypeWithChunk(x + 1, y, z) != AIR) block->rightface = false;
    if (getBlockTypeWithChunk(x - 1, y, z) != AIR) block->leftface = false;
    if (getBlockTypeWithChunk(x, y, z + 1) != AIR) block->frontface = false;
    if (getBlockTypeWithChunk(x, y, z - 1) != AIR) block->backface = false;
    if (getBlockTypeWithChunk(x, y + 1, z) != AIR) block->topface = false;
    if (getBlockTypeWithChunk(x, y - 1, z) != AIR) block->bottomface = false;
}

Chunk::blockType Chunk::getBlockType(int x, int y, int z)  {
    if (x < 0 || x >= CHUNK_WIDTH ||
        y < 0 || y >= CHUNK_HEIGHT ||
        z < 0 || z >= CHUNK_LENGTH) {
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

int Chunk::generateHeight(int x, int z) {
    float n = noise.GetNoise(float(x), float(z));
    return n = (n + 1.0f) / 2.0f * CHUNK_HEIGHT / 2;
}

void Chunk::fillDown(int x, int h, int z) {
    for (int i = h - 1; i > 0; i--)
    {
        blockArray[x][i][z] = DIRT;
    }
}
