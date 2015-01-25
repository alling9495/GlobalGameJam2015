#include "WorldChunk.h"
#include <iostream>
using namespace std;
WorldChunk::WorldChunk(bool wall, int x, int y):
x(x),
y(y)
{

	for(int i = 0; i < CHUNK_SIZE; i++){
		for(int j = 0; j < CHUNK_SIZE; j++){
			tiles[i][j] = Tile(wall,i+x*CHUNK_SIZE,j+y*CHUNK_SIZE);
		}
	}
}

WorldChunk::WorldChunk(bool wall, int x, int y,sf::Color color):
x(x),
y(y)
{

	for(int i = 0; i < CHUNK_SIZE; i++){
		for(int j = 0; j < CHUNK_SIZE; j++){
			tiles[i][j] = Tile(wall,i+x*CHUNK_SIZE,j+y*CHUNK_SIZE);
			tiles[i][j].updateColor(color);
		}
	}
}
float getDist(const sf::Vector2f & a, const sf::Vector2f & b){
	return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

WorldChunk::~WorldChunk(){
	
}
void WorldChunk::draw(sf::RenderWindow & window){
	for(int i = 0; i < CHUNK_SIZE; i++){
		for(int j = 0; j < CHUNK_SIZE; j++){
			tiles[i][j].draw(window);
		}
	}
}
void WorldChunk::update(sf::Time elapsed){
	if(isBeingDestroyed){
		for(int i = 0; i < CHUNK_SIZE; i++){
			for(int j = 0; j < CHUNK_SIZE; j++){
				tiles[i][j].update(elapsed);
			}
		}	
	}
}

void WorldChunk::startDeallocationAnimation(){
	isBeingDestroyed=true;
	for(int i = 0; i < CHUNK_SIZE; i++){
		for(int j = 0; j < CHUNK_SIZE; j++){
			tiles[i][j].startDestoryAnimation((rand()%300));
		}
	}
}

void WorldChunk::startDeallocationAnimation(sf::Vector2f startingPosition, float speed){
	if(!isBeingDestroyed){
	isBeingDestroyed=true;
		for(int i = 0; i < CHUNK_SIZE; i++){
			for(int j = 0; j < CHUNK_SIZE; j++){
				float dist = getDist(startingPosition,tiles[i][j].getPosition());
				tiles[i][j].startDestoryAnimation((dist + 100) * (1.0f/speed));
			}
		}
	}
}


void WorldChunk::colorTiles(sf::Vector2f startingPosition, float speed,sf::Color color){
	if(!isBeingDestroyed){
	isBeingDestroyed=true;
		for(int i = 0; i < CHUNK_SIZE; i++){
			for(int j = 0; j < CHUNK_SIZE; j++){
				float dist = getDist(startingPosition,tiles[i][j].getPosition());
				tiles[i][j].updateColorWithDelay((dist + 100) * (1.0f/speed),color);
			}
		}
	}
}



