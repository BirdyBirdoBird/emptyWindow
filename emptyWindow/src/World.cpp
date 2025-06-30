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
	// Get current player position in chunk coords
	int xPos = (int)ceil(location.x / 16);
	int zPos = (int)ceil(location.z / 16);

	deleteFarChunks(xPos, zPos);

	for (int x = -renderDistance; x < renderDistance; x++)
	{
		for (int z = -renderDistance; z < renderDistance; z++)
		{
			addChunkAtLocation(xPos + x, zPos + z);
		}
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
void World::addChunkAtLocation(int x, int z) {
	if (worldChunks.find(std::make_pair(x, z)) != worldChunks.end())
		return;

	Chunk* chunk = new Chunk(x, z, noise);
	worldChunks.insert(std::make_pair(std::make_pair(x, z), chunk));
}