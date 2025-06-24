#include "Chunk.h"
Chunk::Chunk(int x, int y) {
	this->x = x;
	this->y = y;
	fillBlockQueue();
}

Chunk::~Chunk() {
	for (Block* block : blockList) {
		delete block;
	}
}

void Chunk::fillBlockQueue() {
	for (int l = 0; l < length; l++)
	{
		for (int w = 0; w < width; w++)
		{
			blockList.push_front(new Block(l, 0, w));
		}
	}
}