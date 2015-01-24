#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <SFML/Graphics.hpp>
#include <math.h>
#define RAD2DEGf (float)(180.0f/M_PI)
class Player{
public:
	Player();
	~Player();
	void move(const sf::Vector2<float>& dir);
	void rotate(float dir);
	void draw(sf::RenderWindow & window);
	void turn(float angle);
	const sf::Vector2<float> & getCenter();
	sf::Vector2<float> forward();
	const sf::Vector2f & getPosition();
private:
	sf::CircleShape triangle;
	sf::Vector2<float> pos;
	float angle;
}; 
#endif