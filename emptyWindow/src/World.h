#pragma once
#include "Chunk.h"
#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../glm/glm.hpp>
#include "FastNoiseLite.h"

class World
{
public: 
	int renderDistance = 4;
	std::map<std::pair<int, int>, Chunk*> worldChunks;
	World(glm::vec3 cameraPos);
	void addNearbyChunks(glm::vec3 pos);
private:
	FastNoiseLite noise;
	void deleteFarChunks(int x, int z);
	void addChunkAtLocation(int x, int z);
};

