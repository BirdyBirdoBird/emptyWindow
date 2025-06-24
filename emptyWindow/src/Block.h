#pragma once
#include <iostream>
#include <vector>
class Block
{
public:
	int faceCount = 0;
	std::vector<float> faceVertices;
	std::vector<int> faceIndecies;
	bool frontface, backface, leftface, rightface, topface, bottomface;
	int x = 0, y = 0, z = 0;
	
	
	Block(int x, int y, int z);
	~Block();
	void fillAll();
	void clearAll();
	void loadFaceVertecies();
	void loadFaceIndecies();
	void printProperties();
};

