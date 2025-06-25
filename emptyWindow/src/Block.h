#pragma once
#include <iostream>
#include <vector>
#include "BlockTypes.h"
class Block
{
private:
	int faceCount = 0;
public:
	std::vector<float> faceVertices;
	std::vector<int> faceIndecies;
	bool frontface, backface, leftface, rightface, topface, bottomface;
	int x = 0, y = 0, z = 0;
	
	
	Block(int x, int y, int z);
	virtual ~Block();
	void fillAll();
	void clearAll();
	virtual void loadFaceVertecies();
	void loadFaceIndecies();
	void printProperties();
};

