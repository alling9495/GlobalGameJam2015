#include "WorldChunk.h"

WorldChunk::WorldChunk(int seed, int x, int y){

	for(int i = 0; i < CHUNK_WIDTH; i++){
		for(int j = 0; j < CHUNK_HEIGHT; j++){
			tiles[i][j] = Tile(0,i+x*CHUNK_WIDTH,j+y*CHUNK_HEIGHT);
		}
	}
}
WorldChunk::~WorldChunk(){

}
void WorldChunk::draw(sf::RenderWindow & window){
	for(int i = 0; i < CHUNK_WIDTH; i++){
		for(int j = 0; j < CHUNK_HEIGHT; j++){
			tiles[i][j].draw(window);
		}
	}
}