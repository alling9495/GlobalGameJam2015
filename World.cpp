#include "World.h"
#include "WorldChunk.h"
#include "Tile.h"
#include <iostream>
#include "VectorUtil.h"
#define LEVELS 6
using namespace std;

float levelTimes[] = {35.0,40.0,50.0,60.0,50.0,50.0f};
float speedValues[] = {0.35f, 0.45f, 0.5f, 0.5f, 0.65f, 0.75f,0.0};
float dissolveSpeedValues[] = {1.0f,1.32f,1.4f,1.6f,1.8f,2.0f};

sf::Color tileColors[] = {
	sf::Color(125,25,125),
	sf::Color(25,125,25),
	sf::Color(125,25,125),
	sf::Color(125,25,60),
	sf::Color(200,25,25),
	sf::Color(0,255,0),
	sf::Color(255,255,255),
};


World::World(int seed):
	seed(seed),
	state(GAMESTATE::PLAYING)
{
	srand(seed);
	sf::Color startColor = sf::Color(125,25,125);
	levelTime = levelTimes[0];
	std::pair<int,int> origin = std::pair<int,int>(0,0);
	generateChunk(std::pair<int,int>(0,0),TYPE::FLOOR, startColor);
	generateChunk(origin,1,0,TYPE::WALL,tileColors[0]);
	generateChunk(origin,1,1,TYPE::WALL,tileColors[0]);
	generateChunk(origin,0,1,TYPE::WALL,tileColors[0]);
	generateChunk(origin,-1,1,TYPE::WALL,tileColors[0]);
	generateChunk(origin,-1,0,TYPE::WALL,tileColors[0]);
	generateChunk(origin,-1,-1,TYPE::WALL,tileColors[0]);
	generateChunk(origin,0,-1,TYPE::FLOOR,startColor);
	generateChunk(origin,1,-1,TYPE::WALL,tileColors[0]); 	

	player.move(sf::Vector2f(TILE_SIZE*CHUNK_SIZE / 2, TILE_SIZE*CHUNK_SIZE / 2));
	//player.turn(-90);
}

void World::update(sf::Time elapsed){
	levelTime -= elapsed.asSeconds()*3;
	if(levelTime < 0){
		/*
		if(level < LEVELS){
			levelTime=levelTimes[++level];
			player.setSpeedMultiplier(speedValues[level]);
			colorTiles(tileColors[level]);
			cout<<"LEVEL UP"<<endl;
		}
		*/
	}
	if(state == GAMESTATE::PLAYING){
		std::pair<int,int> chunk = getPlayerChunk();
		
		if(chunk != lastPlayerChunk){
			std::cout << "Player entered " << chunk.first << "," << chunk.second << endl;
			std::cout << "Chunks loaded: " << chunks.size() << endl;
			if(chunks[chunk]->isNewLevel()){
				cout << "LEVEL " << level;
				if(level+1 == LEVELS){
					endGame(chunk);
				}
				else{
					levelTime=levelTimes[++level];
					player.setSpeedMultiplier(speedValues[level]);
					player.setColor(sf::Color(0,0,0));
					colorTiles(tileColors[level]);
					cout<<"LEVEL UP"<<endl;	
				}
			}
			else{
				player.setColor(sf::Color(255,255,255));
			}
			//Second check if game is won.
			if(state == GAMESTATE::PLAYING){
				getChunkWithOffset(0,0)->startDeallocationAnimation(
			
				VectorUtil::offset(player.getCenter(),player.forward()*-3.0f),dissolveSpeedValues[level]);
				unloadChunks(chunk);
				
				lastPlayerChunk = chunk;
				getChunkWithOffset(0,0)->startDeallocationAnimation(
				VectorUtil::offset(player.getCenter(),player.forward()*-3.0f),dissolveSpeedValues[level]);

				//Generate the square chunk around the player

				generateChunks();
			}
		}
	}

	for(std::vector<WorldChunk *>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++){
		(*it)->update(elapsed);
	}
		
	
	

}
World::~World(){
	//Clear map
}
void World::draw(sf::RenderWindow & window, sf::Shader* shader, sf::Shader* playerShader){
	bool top = isPlayerNearTop();
	bool left = isPlayerNearLeft();
	bool bottom = isPlayerNearBottom();
	bool right = isPlayerNearRight();
	std::vector<WorldChunk *>::iterator it = loadedChunks.begin();
	while(it != loadedChunks.end()){

		(*it)->draw(window,shader);
		it++;
	}

	
	
	
	player.draw(window,playerShader);
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

bool World::generateChunk(std::pair<int,int> pos, TYPE tileType, sf::Color c){
	if(chunks.count(pos) == 0){

		chunks[pos] = new WorldChunk(tileType,pos.first,pos.second,c);
		loadedChunks.push_back(chunks[pos]);
		return true;
	}
	return false;
}

void World::forceGenerateChunk(std::pair<int,int> root, int x, int y, TYPE tileType, sf::Color color){
	forceGenerateChunk(std::pair<int,int>(root.first + x, root.second + y),tileType,color);
}
void World::forceGenerateChunk(std::pair<int,int> pos, TYPE tileType, sf::Color c){
	if(chunks.count(pos) != 0){
		freeChunk(pos);
	}

	chunks[pos] = new WorldChunk(tileType,pos.first,pos.second,c);
	loadedChunks.push_back(chunks[pos]);
	
	

}


bool World::generateChunk(std::pair<int,int> root, int x, int y, TYPE tileType, sf::Color c){
	return generateChunk(std::pair<int,int>(root.first + x, root.second + y),tileType,c);
}

WorldChunk * World::getChunkWithOffset(int x, int y){
	return chunks[std::pair<int,int>(lastPlayerChunk.first + x, lastPlayerChunk.second + y)];
}

bool World::hasChunkWithOffset(int x, int y){
	cout << "Checking " << lastPlayerChunk.first + x << "," << lastPlayerChunk.second + y <<endl;
	return chunks.count(
		std::pair<int,int>(lastPlayerChunk.first + x, lastPlayerChunk.second + y)) > 0;
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
	//Initial scan, guarentee at least 2 walls are open. (enterance and one exit)
	int openCount = 0;
	if(hasChunkWithOffset(-1,0) && getChunkWithOffset(-1,0)->isSafe()){
		openCount++;
	}
	if(hasChunkWithOffset(1,0)&&getChunkWithOffset(1,0)->isSafe()){
		openCount++;
	}
	if(hasChunkWithOffset(0,-1)&&getChunkWithOffset(0,-1)->isSafe()){
		openCount++;
	}
	if(hasChunkWithOffset(0,1)&&getChunkWithOffset(0,1)->isSafe()){
		openCount++;
	}
	cout << "OPEN COUNT: " <<openCount << endl;
	if(openCount < 1){
		bool didGen=false;
		do{
			x = y = 0;
			if(rand()%2 > 0){
				x = round(rand()%3 -1);
			}
			else{
				y = round(rand()%3 -1);
			}
			if(levelTime < 0 && rand()%6 == 0){
				didGen=generateChunk(lastPlayerChunk,x,y,TYPE::GOAL,tileColors[level+1]);
			}
			else{
				didGen=generateChunk(lastPlayerChunk,x,y,TYPE::FLOOR,tileColors[level]);
			}
		}while(!didGen);
	}


	for(x = -1; x < 2; x++){
		for(y = -1; y < 2; y++){
			if(rand()%4 == 0){
				if(generateChunk(lastPlayerChunk,x,y,TYPE::FLOOR,tileColors[level])){
					if(rand()%4 == 0){
						getChunkWithOffset(x,y)->startDeallocationAnimation();
						getChunkWithOffset(x,y)->isWall=true;//Sorry
					}
				}
			}
			else{
		
				if(generateChunk(lastPlayerChunk,x,y,TYPE::WALL,tileColors[level])){
					if(rand()%4 == 0){
						getChunkWithOffset(x,y)->startDeallocationAnimation();

					}
				}
			}
		}
	}
}

void World::forceColorTiles(sf::Color color){
	for(std::vector<WorldChunk *>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++){
		(*it)->forceColorTiles(player.getCenter(),4,color);
	}
}

void World::colorTiles(sf::Color color){
	for(std::vector<WorldChunk *>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++){
		(*it)->colorTiles(player.getCenter(),4,color);
	}

	
}

bool World::isPlayerAlive() {
	if(state == GAMESTATE::LOST){
		return true;
	}
	WorldChunk chunk = * chunks[getPlayerChunk()];
	const sf::Vector2f pos = player.getCenter();

	int i = (pos.x - (chunk.x * CHUNK_SIZE*TILE_SIZE)) / TILE_SIZE;
	int j = (pos.y - (chunk.y * CHUNK_SIZE*TILE_SIZE)) / TILE_SIZE;

	Tile tile = chunk.getTile(i, j);
	return tile.isSafe();
}

void World::endGame(std::pair<int,int> endingTile){
	cout<<"GAME END"<<endl;
	player.setColor(sf::Color(255,255,255,0));
	player.setSpeedMultiplier(0);
	state=GAMESTATE::WON;				
	sf::Color c = sf::Color(0,0,0);
	forceGenerateChunk(endingTile,TYPE::FLOOR, c);
	forceGenerateChunk(endingTile,1,0,TYPE::FLOOR,c);
	forceGenerateChunk(endingTile,1,1,TYPE::FLOOR,c);
	forceGenerateChunk(endingTile,0,1,TYPE::FLOOR,c);
	forceGenerateChunk(endingTile,-1,1,TYPE::FLOOR,c);
	forceGenerateChunk(endingTile,-1,0,TYPE::FLOOR,c);
	forceGenerateChunk(endingTile,-1,-1,TYPE::FLOOR,c);
	forceGenerateChunk(endingTile,0,-1,TYPE::FLOOR,c);
	forceGenerateChunk(endingTile,1,-1,TYPE::FLOOR,c);
	forceColorTiles(sf::Color(255,255,255)); 	
}

void World::loseGame()
{
	player.setColor(sf::Color(255,0,0));
	state= GAMESTATE::LOST;
	player.setSpeedMultiplier(speedValues[0]);
	level = 0;
	forceColorTiles(sf::Color(0,0,0));
}

