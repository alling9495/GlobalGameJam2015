#include "Tile.h"
#include "WorldChunk.h"
#include <iostream>
#include <cmath>

using namespace std;

Tile::Tile(TYPE tileType, int x, int y):
	x(x),
	y(y),
	myType(tileType),
	isWall(tileType==TYPE::WALL)
{
	renderTile.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
	renderTile.setPosition(x*TILE_SIZE,y*TILE_SIZE);
	if(tileType==TYPE::WALL){
		renderTile.setFillColor(sf::Color(abs(sin(x*y))*95,abs(sin(x*y))*95,abs(sin(x*y))*95));
	}
	else if(tileType == TYPE::GOAL){
		renderTile.setFillColor(sf::Color(255,255,255));	
	}
	else{
		renderTile.setFillColor(
			sf::Color(abs(sin(x/64.0f))*125,abs(cos(y/64.0f))*125,abs(sin(x*y))*155));
	}
	destroyDelay = 0.0f;
}
Tile::Tile(TYPE tileType, int x, int y, sf::Color color):
x(x),
y(y),
myType(tileType),
isWall(tileType==TYPE::WALL){
	renderTile.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
	renderTile.setPosition(x*TILE_SIZE,y*TILE_SIZE);
	if(tileType==TYPE::WALL){
		renderTile.setFillColor(sf::Color(abs(sin(x*y))*95,abs(sin(x*y))*95,abs(sin(x*y))*95));
	}
	else if(tileType == TYPE::GOAL){
		renderTile.setFillColor(sf::Color(
			min(color.r+50,255),
			min(color.g+50,255),
			min(color.b+50,255)));	
	}
	else{
		float intensity = (rand()%16) / 32.0f + 0.5f;
		renderTile.setFillColor(
			sf::Color(intensity*color.r,intensity*color.g,intensity*color.b));
	}

}
Tile::~Tile(){
	
}

const sf::Vector2f & Tile::getPosition(){
	return renderTile.getPosition();
}
void Tile::draw(sf::RenderWindow & window, sf::Shader* shader){
	if(isWall){
		window.draw(renderTile);
	}
	else{
		window.draw(renderTile, shader);
	}
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
	if(isBeingForceColored){
		renderTile.setFillColor(newColor);
	}
	else{
		if(!isWall){
			if(myType == TYPE::GOAL){
				renderTile.setFillColor(newColor);
			}
			else{
				float intensity = (rand()%16) / 32.0f + 0.5f;
				renderTile.setFillColor(
					sf::Color(intensity*newColor.r,intensity*newColor.g,intensity*newColor.b));
			}
		}
	}
}
void Tile::updateColorWithDelay(float delay, sf::Color c){
	if(myType!=TYPE::WALL){
		if(myType == TYPE::GOAL){
			nextColor=sf::Color(255,255,255);
		}
		else{
			nextColor = c;
		}
		colorDelay = delay;
		isBeingColored=true;
	}
}



void Tile::forceUpdateColorWithDelay(float delay, sf::Color c){
	nextColor = c;
	colorDelay = delay;
	isBeingColored=true;
	isBeingForceColored=true;
}
bool Tile::isSafe() {
	return !isWall && destroyDelay >= 0;
}
