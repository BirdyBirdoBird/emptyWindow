#pragma once
#include <iostream>
#include <list>
#include "Block.h"
class Chunk
{
public:
	std::vector<float> allVertices;       
	std::vector<unsigned int> allIndices;
	unsigned int VAO, VBO, EBO;
	int width = 16, height = 16, length = 16;

	Chunk(int x, int y);
	~Chunk();

	void fillBlockVec();
	void buildBuffers();    // sends data to GPU
	void render();          // binds VAO and draws

private:
	int X = 0, Y = 0;
};

