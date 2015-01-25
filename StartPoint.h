#ifndef __START_H__
#define __START_H__ 
#include <SFML/Graphics.hpp>
#include "WorldChunk.h"
class StartPoint{
public:
	StartPoint(sf::Vector2f center);
	~StartPoint();
	void fadeIn();
	void fadeOut();
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow & window);
	void setChunk(sf::Vector2f chunk);
	bool pointIn(sf::Vector2f point);
	bool isActive();
	int x, y;
	sf::Vector2f position;

private:

	bool fadeDir;
	int alpha;
	sf::RectangleShape square1;
	sf::RectangleShape square2;
	float angle;

};
#endif