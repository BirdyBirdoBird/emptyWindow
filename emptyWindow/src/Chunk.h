#pragma once
#include <iostream>
#include <list>
#include "Block.h"
#include "FastNoiseLite.h"

class Chunk
{
private:
	FastNoiseLite noise;
public:
	enum blockType : uint8_t { AIR, DIRT };
	int width = 16, height = 16, length = 16;
	blockType blockArray[16][16][16];
	std::vector<float> allVertices;       
	std::vector<unsigned int> allIndices;
	unsigned int VAO, VBO, EBO;
	int chunkOffsetX = 0, chunkOffsetZ;

	Chunk(int x, int z, FastNoiseLite& noise);
	~Chunk();

	void initBlocks();
	void fillBlockVec();
	void alternateBlockFaces(Block *block, int x, int y, int z);
	Chunk::blockType getBlockType(int x, int y, int z);
	void buildBuffers();    
	void render();     
	int generateHeight(int x, int y);
	void fillDown(int x, int z, int h);
};

