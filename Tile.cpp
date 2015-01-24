#include "Tile.h"
#include <iostream>

using namespace std;

Tile::Tile(int type, int x, int y){
	renderTile.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
	renderTile.setPosition(x*TILE_SIZE,y*TILE_SIZE);
	renderTile.setFillColor(
		sf::Color((x*64)%256,(y*64)%256,256));
};
Tile::~Tile(){}
void Tile::draw(sf::RenderWindow & window){
	window.draw(renderTile);
}