#ifndef __TILE_H__
#define __TILE_H__
#include <SFML/Graphics.hpp>
#define TILE_SIZE 64

class Tile{
public:
	Tile(){};
	Tile(bool wall, int x, int y);
	~Tile();
	void draw(sf::RenderWindow & window);
private:
	sf::RectangleShape renderTile;
};
#endif