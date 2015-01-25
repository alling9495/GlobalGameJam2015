#include "Tile.h"
#include <iostream>

using namespace std;

Tile::Tile(bool type, int x, int y){
	renderTile.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
	renderTile.setPosition(x*TILE_SIZE,y*TILE_SIZE);
	if(type){
		isWall = true;
		renderTile.setFillColor(sf::Color(115,115,115));
	}
	else{
		renderTile.setFillColor(
			sf::Color((abs(x/4)+abs(y/4))%2 * 55,0,0));
	}
	destroyDelay = 0.0f;
};
Tile::~Tile(){
	
}

const sf::Vector2f & Tile::getPosition(){
	return renderTile.getPosition();
}
void Tile::draw(sf::RenderWindow & window){
	window.draw(renderTile);
}

void Tile::update(sf::Time elapsed){
	if(isBeingDestoryed){
		destroyDelay-=elapsed.asMilliseconds();
		if(destroyDelay < 0){
			renderTile.setSize(renderTile.getSize() * 0.95f);
			renderTile.setRotation(renderTile.getRotation() + 3.0f);
		}
	}
}
void Tile::startDestoryAnimation(float delay){
	isBeingDestoryed=true;
	destroyDelay = delay;
}

bool Tile::isSafe() {
	return !isWall && destroyDelay >= 0;
}