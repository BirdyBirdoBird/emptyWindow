#include "World.h"
#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../glm/glm.hpp>
#include "FastNoiseLite.h"

World::World(glm::vec3 cameraPos) {
	srand(time(NULL));
	noise.SetSeed(rand() % 1337420);
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise.SetFrequency(0.01f);


	addNearbyChunks(cameraPos);
}

void World::addNearbyChunks(glm::vec3 location)
{
	int xPos = (int)floor(location.x / 16.0f);
	int zPos = (int)floor(location.z / 16.0f);

	deleteFarChunks(xPos, zPos);

	std::vector<Chunk*> newChunks;

	for (int x = -renderDistance; x < renderDistance; x++)
	{
		for (int z = -renderDistance; z < renderDistance; z++)
		{
			int cx = xPos + x;
			int cz = zPos + z;

			if (worldChunks.find({ cx, cz }) == worldChunks.end()) {
				Chunk* chunk = new Chunk(cx, cz, noise, &worldChunks);
				worldChunks[{cx, cz}] = chunk;
				newChunks.push_back(chunk);
			}
		}
	}

	for (Chunk* chunk : newChunks) {
		chunk->fillBlockVec(); 
		chunk->buildBuffers();   
	}
}

void World::deleteFarChunks(int xPos, int zPos) {
	std::map<std::pair<int, int>, Chunk*>::iterator it = worldChunks.begin();
	while (it != worldChunks.end())
	{
		int x = std::abs(xPos);
		int z = std::abs(zPos);
		int chunkX = std::abs(it->first.first);
		int chunkZ = std::abs(it->first.second);

		if (std::abs(x - chunkX) > renderDistance || std::abs(z - chunkZ) > renderDistance)
		{
			delete it->second;
			worldChunks.erase(it++);
		}
		else
		{
			++it;
		}
	}
}
