#ifndef __WORLD_H__
#define __WORLD_H__
#import "Player.h"
#import "WorldChunk.h"
class World{
public:
	World(int xSize, int ySize, Seed s);
	~World();
	void draw(sf::RenderWindow & window);

private:
	Player player;
	std::map<pair<int,int>, WorldChunk *> chunks;
	void generate() //Generate tiles around when the player moves to a new chunk.
	

};
#endif