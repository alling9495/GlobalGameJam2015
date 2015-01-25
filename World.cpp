#include "World.h"
#include "WorldChunk.h"
#include "Tile.h"
#include <iostream>
using namespace std;
World::World(int seed):
	seed(seed)
{
	std::pair<int,int> origin = std::pair<int,int>(0,0);
	generateChunk(std::pair<int,int>(0,0));
	generateChunk(origin,1,0);
	generateChunk(origin,1,1);
	generateChunk(origin,0,1);
	generateChunk(origin,-1,1);
	generateChunk(origin,-1,0);
	generateChunk(origin,-1,-1);
	generateChunk(origin,0,-1);
	generateChunk(origin,1,-1);
}

void World::update(sf::Time elapsed){
	
	std::pair<int,int> chunk = getPlayerChunk();
	if(chunk != lastPlayerChunk){
		std::cout << "Player entered " << chunk.first << "," << chunk.second << endl;
		std::cout << "Chunks loaded: " << chunks.size() << endl;
		unloadChunks(chunk);
		lastPlayerChunk = chunk;
		//Generate the square chunk around the player

		generateChunk(lastPlayerChunk);
		
		generateChunk(lastPlayerChunk,1,0);
		generateChunk(lastPlayerChunk,1,1);
		generateChunk(lastPlayerChunk,0,1);
		generateChunk(lastPlayerChunk,-1,1);
		generateChunk(lastPlayerChunk,-1,0);
		generateChunk(lastPlayerChunk,-1,-1);
		generateChunk(lastPlayerChunk,0,-1);
		generateChunk(lastPlayerChunk,1,-1);
		
	}


}
World::~World(){
	//Clear map
}
void World::draw(sf::RenderWindow & window){
	bool top = isPlayerNearTop();
	bool left = isPlayerNearLeft();
	bool bottom = isPlayerNearBottom();
	bool right = isPlayerNearRight();
	std::vector<WorldChunk *>::iterator it = loadedChunks.begin();
	while(it != loadedChunks.end()){

		(*it)->draw(window);
		it++;
	}
	
	
	player.draw(window);
}

bool World::isPlayerNearTop(){
	const sf::Vector2f pos = player.getCenter();
	return  ((float)(((int)pos.y)%(CHUNK_SIZE * TILE_SIZE))
		/(CHUNK_SIZE*TILE_SIZE) < 0.25);
}
bool World::isPlayerNearBottom(){
	const sf::Vector2f pos = player.getCenter();
	return  ((float)(((int)pos.y)%(CHUNK_SIZE * TILE_SIZE))
		/(CHUNK_SIZE*TILE_SIZE) > 0.75);
}

bool World::isPlayerNearLeft(){
	const sf::Vector2f pos = player.getCenter();
	return  ((float)(((int)pos.x)%(CHUNK_SIZE * TILE_SIZE))
		/(CHUNK_SIZE*TILE_SIZE) < 0.25);
}
bool World::isPlayerNearRight(){
	const sf::Vector2f pos = player.getCenter();
	return  ((float)(((int)pos.y)%(CHUNK_SIZE * TILE_SIZE))
		/(CHUNK_SIZE*TILE_SIZE) > 0.75);
}

std::pair<int,int> World::getPlayerChunk(){
	const sf::Vector2f pos = player.getCenter();
	return std::pair<int,int>(
		(int)floor((pos.x/(CHUNK_SIZE*TILE_SIZE))),
		(int)floor((pos.y/(CHUNK_SIZE*TILE_SIZE))));
}

void World::freeChunk(std::pair<int,int> key){
	if(chunks[key] != NULL){
		free(chunks[key]);
		chunks.erase(key);
	}
}

void World::generateChunk(std::pair<int,int> pos){
	if(chunks[pos] == NULL){
		chunks[pos] = new WorldChunk(seed,pos.first,pos.second);
		loadedChunks.push_back(chunks[pos]);
	}
}

void World::generateChunk(std::pair<int,int> root, int x, int y){
	generateChunk(std::pair<int,int>(root.first + x, root.second + y));
}

WorldChunk * World::getChunkWithOffset(int x, int y){
	return chunks[std::pair<int,int>(lastPlayerChunk.first + x, lastPlayerChunk.second + y)];
}

Player & World::getPlayer(){
	return player;
}

void World::unloadChunks(std::pair<int,int> next){
	std::vector<WorldChunk *>::iterator it = loadedChunks.begin();
	while(it != loadedChunks.end()){
		if(abs((*it)->x - next.first) > 1 || abs((*it)->y - next.second) > 1)
		{
			cout << "Free : "  << (*it)->x << " ," << (*it)->y << endl;
			freeChunk(std::pair<int,int>((*it)->x,(*it)->y));
			it=loadedChunks.erase(it);

		}
		else{
			++it;
		}
	}
}
