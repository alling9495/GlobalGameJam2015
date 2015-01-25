#include "World.h"
#include "WorldChunk.h"
#include "Tile.h"
#include <iostream>
#include "VectorUtil.h"
#define LEVELS 5
using namespace std;


float levelTimes[] = {35.0,40.0,50.0,60.0,70.0,70.0f};
float speedValues[] = {0.35f, 0.4f, 0.45f, 0.5f, 0.65f, 0.75f};
float dissolveSpeedValues[] = {1.15f,1.52f,1.6f,1.8f,2.0f,2.2f};
sf::Color tileColors[] = {
	sf::Color(125,25,125),
	sf::Color(25,125,25),
	sf::Color(125,25,125),
	sf::Color(125,25,60),
	sf::Color(200,25,25),
	sf::Color(0,255,0)
};


World::World(int seed):
	seed(seed)
{
	levelTime = levelTimes[0];
	std::pair<int,int> origin = std::pair<int,int>(0,0);
	generateChunk(std::pair<int,int>(0,0),false, tileColors[0]);
	generateChunk(origin,1,0,true,tileColors[0]);
	generateChunk(origin,1,1,true,tileColors[0]);
	generateChunk(origin,0,1,true,tileColors[0]);
	generateChunk(origin,-1,1,true,tileColors[0]);
	generateChunk(origin,-1,0,true,tileColors[0]);
	generateChunk(origin,-1,-1,true,tileColors[0]);
	generateChunk(origin,0,-1,false,tileColors[0]);
	generateChunk(origin,1,-1,true,tileColors[0]);
	colorTiles(tileColors[0]);   	

	player.move(sf::Vector2f(TILE_SIZE*CHUNK_SIZE / 2, TILE_SIZE*CHUNK_SIZE / 2));
	player.turn(-90);
}

void World::update(sf::Time elapsed){
	levelTime -= elapsed.asSeconds()*5;
	if(levelTime < 0){
		if(level < LEVELS){
			levelTime=levelTimes[++level];
			player.setSpeedMultiplier(speedValues[level]);
			colorTiles(tileColors[level]);
			cout<<"LEVEL UP"<<endl;
		}
	}
	std::pair<int,int> chunk = getPlayerChunk();
	if(chunk != lastPlayerChunk){
		std::cout << "Player entered " << chunk.first << "," << chunk.second << endl;
		std::cout << "Chunks loaded: " << chunks.size() << endl;
		unloadChunks(chunk);
	
		lastPlayerChunk = chunk;
		getChunkWithOffset(0,0)->startDeallocationAnimation(
			VectorUtil::offset(player.getCenter(),player.forward()*-3.0f),dissolveSpeedValues[level]);

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
	for(std::vector<WorldChunk *>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++){
		(*it)->draw(window);
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

bool World::generateChunk(std::pair<int,int> pos, bool wall, sf::Color &c){
	if(!chunks.count(pos) != 0){

		chunks[pos] = new WorldChunk(wall,pos.first,pos.second,c);
		loadedChunks.push_back(chunks[pos]);
		return true;
	}
	return false;
}

bool World::generateChunk(std::pair<int,int> root, int x, int y, bool wall, sf::Color & c){
	return generateChunk(std::pair<int,int>(root.first + x, root.second + y),wall,c);
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

	}while(!generateChunk(lastPlayerChunk,x,y,false,tileColors[level]));




	for(x = -1; x < 2; x++){
		for(y = -1; y < 2; y++){
			if(rand()%4 == 0){
				if(generateChunk(lastPlayerChunk,x,y,false,tileColors[level])){
					if(rand()%4 == 0){
						getChunkWithOffset(x,y)->startDeallocationAnimation();
					}
				}
			}
			else{
		
				if(generateChunk(lastPlayerChunk,x,y,true,tileColors[level])){
					if(rand()%4 == 0){
						getChunkWithOffset(x,y)->startDeallocationAnimation();
					}
				}
			}
		}
	}
}

void World::colorTiles(sf::Color color){
	for(std::vector<WorldChunk *>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++){
		(*it)->colorTiles(player.getCenter(),8,color);
	}

	
}

bool World::isPlayerAlive() {
	WorldChunk chunk = * chunks[getPlayerChunk()];
	const sf::Vector2f pos = player.getCenter();

	int i = (pos.x - (chunk.x * CHUNK_SIZE*TILE_SIZE)) / TILE_SIZE;
	int j = (pos.y - (chunk.y * CHUNK_SIZE*TILE_SIZE)) / TILE_SIZE;

	Tile tile = chunk.getTile(i, j);
	return tile.isSafe();
}
