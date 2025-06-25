#pragma once
#include "Block.h"

class GrassBlock : public Block {
public:
    GrassBlock(int x, int y, int z) : Block(x, y, z) {}


    void loadFaceVertecies() override {
		if (frontface) {
			faceVertices.insert(faceVertices.end(),
				{
					0.5f + x,  0.5f + y, 0.5f + z, 1.0f, 1.0f, 0.0f,
					0.5f + x, -0.5f + y, 0.5f + z, 1.0f, 0.0f, 0.0f,
				   -0.5f + x, -0.5f + y, 0.5f + z, 0.0f, 0.0f, 0.0f,
				   -0.5f + x,  0.5f + y, 0.5f + z, 0.0f, 1.0f, 0.0f
				});
		}
		if (backface) {
			faceVertices.insert(faceVertices.end(),
				{
					0.5f + x,  0.5f + y, -0.5f + z, 1.0f, 1.0f, 0.0f,
					0.5f + x, -0.5f + y, -0.5f + z, 1.0f, 0.0f, 0.0f,
				   -0.5f + x, -0.5f + y, -0.5f + z, 0.0f, 0.0f, 0.0f,
				   -0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 1.0f, 0.0f
				});
		}
		if (leftface) {
			faceVertices.insert(faceVertices.end(),
				{
				   -0.5f + x,  0.5f + y,  0.5f + z, 1.0f, 1.0f, 0.0f,
				   -0.5f + x, -0.5f + y,  0.5f + z, 1.0f, 0.0f, 0.0f,
				   -0.5f + x, -0.5f + y, -0.5f + z, 0.0f, 0.0f, 0.0f,
				   -0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 1.0f, 0.0f
				});
		}
		if (rightface) {
			faceVertices.insert(faceVertices.end(),
				{
					0.5f + x,  0.5f + y,  0.5f + z, 1.0f, 1.0f, 0.0f,
					0.5f + x, -0.5f + y,  0.5f + z, 1.0f, 0.0f, 0.0f,
					0.5f + x, -0.5f + y, -0.5f + z, 0.0f, 0.0f, 0.0f,
					0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 1.0f, 0.0f
				});
		}
		if (topface) {
			faceVertices.insert(faceVertices.end(),
				{
					0.5f + x,  0.5f + y,  0.5f + z, 1.0f, 1.0f, 1.0f,
				   -0.5f + x,  0.5f + y,  0.5f + z, 0.0f, 1.0f, 1.0f,
				   -0.5f + x,  0.5f + y, -0.5f + z, 0.0f, 0.0f, 1.0f,
					0.5f + x,  0.5f + y, -0.5f + z, 1.0f, 0.0f, 1.0f
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
};