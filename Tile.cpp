#include "Tile.h"
#include "WorldChunk.h"
#include <iostream>

using namespace std;

Tile::Tile(bool type, int x, int y):
	x(x),
	y(y),
	isWall(type)
{
	renderTile.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
	renderTile.setPosition(x*TILE_SIZE,y*TILE_SIZE);
	if(type){
		renderTile.setFillColor(sf::Color(abs(sin(x*y))*95,abs(sin(x*y))*95,abs(sin(x*y))*95));
	}
	else{
		renderTile.setFillColor(
			sf::Color(abs(sin(x/64.0f))*125,abs(cos(y/64.0f))*125,abs(sin(x*y))*155));
	}
	destroyDelay = 0.0f;
}
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
	if(isBeingColored){
		
		colorDelay-=elapsed.asMilliseconds();
		if(colorDelay < 0){
			isBeingColored = false;
			updateColor(nextColor);
		}
	}
}
void Tile::startDestoryAnimation(float delay){
	isBeingDestoryed=true;
	destroyDelay = delay;
}

void Tile::updateColor(sf::Color newColor){
	if(!isWall){
		float intensity = (rand()%16) / 32.0f + 0.5f;
		renderTile.setFillColor(
			sf::Color(intensity*newColor.r,intensity*newColor.g,intensity*newColor.b));
	}
}
void Tile::updateColorWithDelay(float delay, sf::Color c){
	if(!isWall){
		nextColor = c;
		colorDelay = delay;
		isBeingColored=true;
	}
}
bool Tile::isSafe() {
	return !isWall && destroyDelay >= 0;
}
