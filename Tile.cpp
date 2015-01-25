#include "Tile.h"
#include <iostream>

using namespace std;

Tile::Tile(bool type, int x, int y){
	renderTile.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
	renderTile.setPosition(x*TILE_SIZE,y*TILE_SIZE);
	if(type){
		renderTile.setFillColor(sf::Color(115,115,115));
	}
	else{
		renderTile.setFillColor(
			sf::Color((abs(x/4)+abs(y/4))%2 * 55,0,0));
	}
};
Tile::~Tile(){
	
}
void Tile::draw(sf::RenderWindow & window){
	window.draw(renderTile);
}