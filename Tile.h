#ifndef __TILE_H__
#define __TILE_H__
#include <SFML/Graphics.hpp>
#include "ChunkType.h"
#define TILE_SIZE 64

class Tile{
public:
	Tile(){};
	Tile(TYPE tileType, int x, int y);
	Tile(TYPE tileType, int x, int y, sf::Color color);
	~Tile();
	const sf::Vector2f & getPosition();
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow & window, sf::Shader* shader = NULL);
	void startDestoryAnimation(float delay);
	void updateColor(sf::Color color);
	void updateColorWithDelay(float delay, sf::Color newCol);	
	void forceUpdateColorWithDelay(float delay, sf::Color newCol);	
	
	bool isSafe();
private:
	int x;
	int y;
	sf::RectangleShape renderTile;
	bool isBeingDestoryed=false;
	bool isBeingColored=false;
	bool isBeingForceColored=false;
	float destroyDelay;
	float colorDelay;
	sf::Color nextColor;
	bool isWall = false;
	TYPE myType;
};
#endif
