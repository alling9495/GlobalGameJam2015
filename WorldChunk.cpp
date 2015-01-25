#include "WorldChunk.h"
#include <iostream>
#include <math.h>
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

void WorldChunk::startDeallocationAnimation(sf::Vector2f startingPosition){
	isBeingDestroyed=true;
	for(int i = 0; i < CHUNK_SIZE; i++){
		for(int j = 0; j < CHUNK_SIZE; j++){
			float dist = getDist(startingPosition,tiles[i][j].getPosition());
			cout << "dist" <<  dist << endl;
			tiles[i][j].startDestoryAnimation(dist + 100);
		}
	}
}


Tile & WorldChunk::getTile(int i, int j) {
	return tiles[i][j];
}
