#ifndef __WORLD_H__
#define __WORLD_H__
#include "Player.h"
#include "WorldChunk.h"
#include "Tile.h"
class World{
public:
	World(int seed);
	~World();
	void draw(sf::RenderWindow & window);
	void update(sf::Time elapsed);
	Player & getPlayer();
	bool isPlayerAlive();
private:
	int level = 0;
	float levelTime;
	int seed;
	Player player;
	std::map<std::pair<int,int>, WorldChunk *> chunks;
	std::vector<WorldChunk *> loadedChunks;
	std::pair<int,int> getPlayerChunk();
	std::pair<int,int> lastPlayerChunk;

	bool generateChunk(std::pair<int,int> key, bool wall, sf::Color & color); //Generate tiles around when the player moves to a new chunk.
	bool generateChunk(std::pair<int,int> root, int offsetx, int offsetY, bool wall, sf::Color& color);
	WorldChunk *  getChunkWithOffset(int offsetX, int offsetY);
	bool isPlayerNearTop();
	bool isPlayerNearBottom();
	bool isPlayerNearLeft();
	bool isPlayerNearRight();
	void unloadChunks(std::pair<int,int> newPos);
	void freeChunk(std::pair<int,int> key);
	void generateChunks();
	void colorTiles(sf::Color color);

};
#endif