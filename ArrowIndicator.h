#ifndef __ARROW_INDICATOR__
#define __ARROW_INDICATOR__ 
#include <SFML/Graphics.hpp>
class ArrowIndicator{

public:
	ArrowIndicator();
	~ArrowIndicator();
	void point(sf::Vector2f center, sf::Vector2f target);
	void draw(sf::RenderWindow & window);

private:
	sf::CircleShape indicator;

};
#endif