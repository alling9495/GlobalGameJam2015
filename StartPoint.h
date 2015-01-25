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
	bool pointIn(sf::Vector2f point);
private:
	bool fadeDir;
	float alpha;
	sf::RectangleShape square1;
	sf::RectangleShape square2;
	sf::Vector2f position;
	float angle;

};
#endif