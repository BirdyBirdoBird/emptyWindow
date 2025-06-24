#pragma once
#include <iostream>
#include <list>
#include "Block.h"
class Chunk
{
private:
	int X = 0, Y = 0;
public:
	enum blockType : uint8_t { AIR, DIRT };
	int width = 16, height = 16, length = 16;
	blockType blockArray[16][16][16];
	std::vector<float> allVertices;       
	std::vector<unsigned int> allIndices;
	unsigned int VAO, VBO, EBO;

	Chunk(int x, int y);
	~Chunk();

	void initBlocks();
	void fillBlockVec();
	void alternateBlockFaces(Block *block, int x, int y, int z);
	Chunk::blockType getBlockType(int x, int y, int z);
	void buildBuffers();    // sends data to GPU
	void render();          // binds VAO and draws

};

