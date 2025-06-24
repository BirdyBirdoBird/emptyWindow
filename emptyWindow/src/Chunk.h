#pragma once
#include <iostream>
#include <list>
#include "Block.h"
class Chunk
{
public:
	std::list<Block*> blockList;
	int width = 16, height = 16, length = 16;
	int x = 0, y = 0;

	Chunk(int x, int y);
	~Chunk();
	void fillBlockQueue();
};

