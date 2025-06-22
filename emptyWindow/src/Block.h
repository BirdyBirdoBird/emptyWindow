#pragma once
#include <iostream>
#include <vector>
class Block
{
public:
	int faceCount = 0;
	std::vector<float> faceVertecies;
	std::vector<int> faceIndecies;
	bool frontface, backface, leftface, rightface, topface, bottomface;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	
	Block();
	~Block();
	void fillAll();
	void clearAll();
	void loadFaceVertecies(bool frontface, bool backface, bool leftface, bool rightface, bool topface, bool bottomface);
	void loadFaceIndecies(bool frontface, bool backface, bool leftface, bool rightface, bool topface, bool bottomface);
	void attachToVAO();
	void use();
};

