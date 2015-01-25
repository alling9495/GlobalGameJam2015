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
	void draw(sf::RenderWindow & window);
	void startDestoryAnimation(float delay);
	void updateColor(sf::Color color);
	void updateColorWithDelay(float delay, sf::Color newCol);	
private:
	int x;
	int y;
	sf::RectangleShape renderTile;
	bool isBeingDestoryed=false;
	bool isBeingColored=false;
	float destroyDelay;
	float colorDelay;
	sf::Color nextColor;
};
#endif