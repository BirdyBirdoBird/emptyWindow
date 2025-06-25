#include "Block.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Block::Block(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
	fillAll();
}

Block::~Block()
{
	glBindVertexArray(0);
}

void Block::fillAll() {
	frontface = true;
	backface = true;
	leftface = true;
	rightface = true;
	topface = true;
	bottomface = true;
}

void Block::clearAll() {
	frontface = false;
	backface = false;
	leftface = false;
	rightface = false;
	topface = false;
	bottomface = false;
}

void Block::loadFaceVertecies() {
	if (frontface) {
		faceVertices.insert(faceVertices.end(),
			{
				0.5f + x,  0.5f + y, 0.5f + z, 1.0f, 1.0f, 2.0f,
				0.5f + x, -0.5f + y, 0.5f + z, 1.0f, 0.0f, 2.0f,
			   -0.5f + x, -0.5f + y, 0.5f + z, 0.0f, 0.0f, 2.0f,
			   -0.5f + x,  0.5f + y, 0.5f + z, 0.0f, 1.0f, 2.0f
			});
	}
	if (backface) {
		faceVertices.insert(faceVertices.end(),
			{
				0.5f + x,  0.5f + y, -0.5f + z, 1.0f, 1.0f, 2.0f,
				0.5f + x, -0.5f + y, -0.5f + z, 1.0f, 0.0f, 2.0f,
			   -0.5f + x, -0.5f + y, -0.5f + z, 0.0f, 0.0f, 2.0f,
			   -0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 1.0f, 2.0f
			});
	}
	if (leftface) {
		faceVertices.insert(faceVertices.end(),
			{
			   -0.5f + x,  0.5f + y,  0.5f + z, 1.0f, 1.0f, 2.0f,
			   -0.5f + x, -0.5f + y,  0.5f + z, 1.0f, 0.0f, 2.0f,
			   -0.5f + x, -0.5f + y, -0.5f + z, 0.0f, 0.0f, 2.0f,
			   -0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 1.0f, 2.0f
			});
	}
	if (rightface) {
		faceVertices.insert(faceVertices.end(),
			{
				0.5f + x,  0.5f + y,  0.5f + z, 1.0f, 1.0f, 2.0f,
				0.5f + x, -0.5f + y,  0.5f + z, 1.0f, 0.0f, 2.0f,
				0.5f + x, -0.5f + y, -0.5f + z, 0.0f, 0.0f, 2.0f,
				0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 1.0f, 2.0f
			});
	}
	if (topface) {
		faceVertices.insert(faceVertices.end(),
			{
				0.5f + x,  0.5f + y,  0.5f + z, 1.0f, 1.0f, 2.0f,
			   -0.5f + x,  0.5f + y,  0.5f + z, 0.0f, 1.0f, 2.0f,
			   -0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 0.0f, 2.0f,
				0.5f + x,  0.5f + y, -0.5f + z, 1.0f, 0.0f, 2.0f
			});
	}
	if (bottomface) {
		faceVertices.insert(faceVertices.end(),
			{
				0.5f + x, -0.5f + y,  0.5f + z, 1.0f, 1.0f, 2.0f,
			   -0.5f + x, -0.5f + y,  0.5f + z, 0.0f, 1.0f, 2.0f,
			   -0.5f + x, -0.5f + y, -0.5f + z, 0.0f, 0.0f, 2.0f,
				0.5f + x, -0.5f + y, -0.5f + z, 1.0f, 0.0f, 2.0f
			});
	}
}

void Block::loadFaceIndecies() {
	int indicesCount = -1;

	if (frontface)
	{
		faceCount++;
		indicesCount += 4;

		faceIndecies.insert(faceIndecies.end(),
			{
			indicesCount - 3, indicesCount, indicesCount - 2,
			indicesCount - 2, indicesCount, indicesCount - 1
			}
		);
	}
	if (backface)
	{
		faceCount++;
		indicesCount += 4;

		faceIndecies.insert(faceIndecies.end(),
			{
			indicesCount - 3, indicesCount - 2, indicesCount,
			indicesCount - 2, indicesCount - 1, indicesCount
			}
		);
	}
	if (leftface)
	{
		faceCount++;
		indicesCount += 4;

		faceIndecies.insert(faceIndecies.end(),
			{
			indicesCount - 3, indicesCount, indicesCount - 2,
			indicesCount - 2, indicesCount, indicesCount - 1
			}
		);
	}
	if (rightface)
	{
		faceCount++;
		indicesCount += 4;

		faceIndecies.insert(faceIndecies.end(),
			{
			indicesCount - 3, indicesCount - 2, indicesCount,
			indicesCount - 2, indicesCount - 1, indicesCount
			}
		);
	}
	if (topface)
	{
		faceCount++;
		indicesCount += 4;

		faceIndecies.insert(faceIndecies.end(),
			{
			indicesCount - 3, indicesCount, indicesCount - 2,
			indicesCount - 2, indicesCount, indicesCount - 1
			}
		);
	}
	if (bottomface)
	{
		faceCount++;
		indicesCount += 4;

		faceIndecies.insert(faceIndecies.end(),
			{
			indicesCount - 3, indicesCount - 2, indicesCount,
			indicesCount - 2, indicesCount - 1, indicesCount
			}
		);
	}
}

void Block::printProperties() {
	std::cout << "Block x: " << x << "\n";
	std::cout << "Block y: " << y << "\n";
	std::cout << "Block z: " << z << "\n";
}
