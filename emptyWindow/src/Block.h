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
	unsigned int VAO, VBO, EBO;
	int x = 0, y = 0, z = 0;
	
	
	Block(int x, int y, int z);
	~Block();
	void fillAll();
	void clearAll();
	void loadFaceVertecies(bool frontface, bool backface, bool leftface, bool rightface, bool topface, bool bottomface);
	void loadFaceIndecies(bool frontface, bool backface, bool leftface, bool rightface, bool topface, bool bottomface);
	void attachToVAO();
	void use();
	void printProperties();
};

