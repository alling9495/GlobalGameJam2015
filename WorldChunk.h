#ifndef __WORLD_CHUNK__
#define __WORLD_CHUNK__
#include "Tile.h"
#include <SFML/Graphics.hpp>
#define CHUNK_WIDTH 64
#define CHUNK_HEIGHT 64

class WorldChunk{

public:
	WorldChunk(int seed, int x, int y);
	~WorldChunk();
	void draw(sf::RenderWindow & window);
private:
	Tile tiles[CHUNK_WIDTH][CHUNK_HEIGHT];



};
#endif