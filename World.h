#ifndef __WORLD_H__
#define __WORLD_H__
#include "Player.h"
#include "WorldChunk.h"
#include "Tile.h"
#include "ChunkType.h"
#include "GameState.hpp"
class World{
public:
	World(int seed);
	~World();
	void draw(sf::RenderWindow & window, sf::Shader *, sf::Shader* playShader = NULL);
	void update(sf::Time elapsed);
	Player & getPlayer();
	bool isPlayerAlive();
	void loseGame();
	void startGame();
	GAMESTATE state;
	std::pair<int,int> getPlayerChunk();
	int level = -2;
	
private:
	float levelTime;
	int seed;
	Player player;
	std::map<std::pair<int,int>, WorldChunk *> chunks;
	std::vector<WorldChunk *> loadedChunks;

	std::pair<int,int> lastPlayerChunk;
	//sf::SoundBuffer sfxBuffer;


	bool generateChunk(std::pair<int,int> key, TYPE wall, sf::Color color); //Generate tiles around when the player moves to a new chunk.
	bool generateChunk(std::pair<int,int> root, int offsetx, int offsetY, TYPE wall, sf::Color color);
	WorldChunk *  getChunkWithOffset(int offsetX, int offsetY);
	WorldChunk * getChunkWithOffset(std::pair<int,int> base, int x, int y);
	bool isPlayerNearTop();
	bool isPlayerNearBottom();
	bool isPlayerNearLeft();
	bool isPlayerNearRight();
	void unloadChunks(std::pair<int,int> newPos);
	void freeChunk(std::pair<int,int> key);
	void generateChunks();
	bool hasChunkWithOffset(int x, int y);
	bool hasChunkWithOffset(std::pair<int,int>,int x,int y);

	void colorTiles(sf::Color color);
	void forceColorTiles(sf::Color c);
	void forceGenerateChunk(std::pair<int,int> pos, TYPE tileType, sf::Color c);
	void forceGenerateChunk(std::pair<int,int> root, int offsetx, int offsetY, TYPE wall, sf::Color color);
	void clearChunks();
	void endGame(std::pair<int,int> endingTile);
};
#endif