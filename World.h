#ifndef __WORLD_H__
#define __WORLD_H__
#import "Player.h"
#import "WorldChunk.h"
#import "Tile.h"
class World{
public:
	World(int seed);
	~World();
	void draw(sf::RenderWindow & window);
	void update(int elapsed);
private:
	int seed;
	Player player;
	std::map<pair<int,int>, WorldChunk *> chunks;
	std::vector<WorldChunk * > loadedChunks;
	pair<int,int> getPlayerChunk();
	pair<int,int> lastPlayerChunk;
	void generate(pair<int,int>); //Generate tiles around when the player moves to a new chunk.
	

};
#endif