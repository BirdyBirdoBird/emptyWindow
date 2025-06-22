#include "Block.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
Block::Block() {
	fillAll();
	loadFaceVertecies(frontface, backface, leftface, rightface, topface, bottomface);
	loadFaceIndecies(frontface, backface, leftface, rightface, topface, bottomface);
	attachToVAO();
}

Block::~Block()
{
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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

void Block::loadFaceVertecies(bool frontface, bool backface, bool leftface, bool rightface, bool topface, bool bottomface) {
	if (frontface)
	{
		faceVertecies.insert(faceVertecies.end(),
			{
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f 
			}
			);
	}
	if (backface)
	{
		faceVertecies.insert(faceVertecies.end(),
			{
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0,
			}
		);
	}
	if (leftface)
	{
		faceVertecies.insert(faceVertecies.end(),
			{
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0,
			-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0,
			}
		);
	}
	if (rightface)
	{
		faceVertecies.insert(faceVertecies.end(),
			{
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0,
			0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0,
			0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0,
			}
		);
	}
	if (topface)
	{
		faceVertecies.insert(faceVertecies.end(),
			{
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0,
			-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0,
			0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0,
			}
		);
	}
	if (bottomface)
	{
		faceVertecies.insert(faceVertecies.end(),
			{
			0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 2.0,
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 2.0,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 2.0,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 2.0
			}
		);
	}
}

void Block::loadFaceIndecies(bool frontface, bool backface, bool leftface, bool rightface, bool topface, bool bottomface) {
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

void Block::attachToVAO() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, faceVertecies.size() * sizeof(float), &faceVertecies.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceIndecies.size() * sizeof(float), &faceIndecies.front(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//ID
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Block::use() {
	glBindVertexArray(VAO);
}
