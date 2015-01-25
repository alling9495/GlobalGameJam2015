#ifndef __WORLD_CHUNK__
#define __WORLD_CHUNK__
#include "Tile.h"
#include <SFML/Graphics.hpp>
#define CHUNK_SIZE 16

class WorldChunk{

public:
	WorldChunk(bool wall, int x, int y);
	WorldChunk(bool wall, int x, int y, sf::Color tileColor);
	~WorldChunk();
	void startDeallocationAnimation();
	void startDeallocationAnimation(sf::Vector2f startingPosition, float speed);
	void colorTiles(sf::Vector2f startingPosition, float speed,sf::Color color);

	void update(sf::Time elapsed);
	void draw(sf::RenderWindow & window);
	int x;
	int y;
	Tile & getTile(int i, int j);
private:
	Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
	bool isBeingDestroyed = false;



};
#endif