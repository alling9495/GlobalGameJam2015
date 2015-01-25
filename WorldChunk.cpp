#include "WorldChunk.h"

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
WorldChunk::~WorldChunk(){
	
}
void WorldChunk::draw(sf::RenderWindow & window){
	for(int i = 0; i < CHUNK_SIZE; i++){
		for(int j = 0; j < CHUNK_SIZE; j++){
			tiles[i][j].draw(window);
		}
	}
}

void WorldChunk::startDeallocationAnimation(){
	isBeingDestroyed=true;
	for(int i = 0; i < CHUNK_SIZE; i++){
		for(int j = 0; j < CHUNK_SIZE; j++){
			tiles[i][j].startDestoryAnimation((rand()%300)/1000f);
		}
	}
}