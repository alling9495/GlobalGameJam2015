#ifndef __TILE_H__
#define __TILE_H__
#include <SFML/Graphics.hpp>
#define TILE_SIZE 64

class Tile{
public:
	Tile(){};
	Tile(bool wall, int x, int y);
	~Tile();
	const sf::Vector2f & getPosition();
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow & window, sf::Shader* shader = NULL);
	void startDestoryAnimation(float delay);
	bool isSafe();
private:
	sf::RectangleShape renderTile;
	bool isBeingDestoryed;
	float destroyDelay;
	bool isWall;
};
#endif