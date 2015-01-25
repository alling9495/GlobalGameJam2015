#include "World.h"
#include "WorldChunk.h"
#include "Tile.h"
#include <iostream>
using namespace std;

sf::Vector2f offset(const sf::Vector2f & a, const sf::Vector2f & off){
	return sf::Vector2f(a.x+off.x,a.y+off.y);
}

World::World(int seed):
	seed(seed)
{
	std::pair<int,int> origin = std::pair<int,int>(0,0);
	generateChunk(std::pair<int,int>(0,0),false);
	generateChunk(origin,1,0,true);
	generateChunk(origin,1,1,true);
	generateChunk(origin,0,1,true);
	generateChunk(origin,-1,1,true);
	generateChunk(origin,-1,0,true);
	generateChunk(origin,-1,-1,true);
	generateChunk(origin,0,-1,false);
	generateChunk(origin,1,-1,true);
}

void World::update(sf::Time elapsed){
	
	std::pair<int,int> chunk = getPlayerChunk();
	if(chunk != lastPlayerChunk){
		std::cout << "Player entered " << chunk.first << "," << chunk.second << endl;
		std::cout << "Chunks loaded: " << chunks.size() << endl;
		unloadChunks(chunk);
	
		lastPlayerChunk = chunk;
		getChunkWithOffset(0,0)->startDeallocationAnimation(offset(player.getCenter(),player.forward()*-3.0f));

		//Generate the square chunk around the player

		generateChunks();

		
	}

	for(std::vector<WorldChunk *>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++){
		(*it)->update(elapsed);
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

bool World::generateChunk(std::pair<int,int> pos, bool wall){
	if(!chunks.count(pos) != 0){

		chunks[pos] = new WorldChunk(wall,pos.first,pos.second);
		loadedChunks.push_back(chunks[pos]);
		return true;
	}
	return false;
}

bool World::generateChunk(std::pair<int,int> root, int x, int y, bool wall){
	cout<<"Wall is " << wall << endl;
	return generateChunk(std::pair<int,int>(root.first + x, root.second + y),wall);
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


void World::generateChunks(){

	//Pick one non'generated chunk and make it not a wall.
	int x, y;
	do{
		x = y = 0;
		if(rand()%2 > 0){
			x = round(rand()%3 -1);
		}
		else{
			y = round(rand()%3 -1);
		}

	}while(!generateChunk(lastPlayerChunk,x,y,false));


	for(x = -1; x < 2; x++){
		for(y = -1; y < 2; y++){
			if(rand()%4 == 0){
				if(generateChunk(lastPlayerChunk,x,y,false)){
					if(rand()%4 == 0){
						getChunkWithOffset(x,y)->startDeallocationAnimation();
					}
				}
			}
			else{
		
				if(generateChunk(lastPlayerChunk,x,y,true)){
					if(rand()%4 == 0){
						getChunkWithOffset(x,y)->startDeallocationAnimation();
					}
				}
			}
		}
	}
}