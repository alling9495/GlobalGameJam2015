#ifndef __WORLD_CHUNK__
#define __WORLD_CHUNK__
#include "Tile.h"
#include <SFML/Graphics.hpp>
#define CHUNK_SIZE 32

class WorldChunk{

public:
	WorldChunk(bool wall, int x, int y);
	~WorldChunk();
	void draw(sf::RenderWindow & window);
	int x;
	int y;
private:
	Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
	


};
#endif