#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <SFML/Graphics.hpp>
#include <math.h>
#include <map>
#define RAD2DEGf (float)(180.0f/M_PI)
// Indexes an array, do not touch
enum Action {
	TurnCounter = 0,
	TurnClockwise,
	Forward,
	Backward,
	Flamethrower,
	Lazer,
	Shield,
	LimitBreak,
	SuperBoost,
	StrafeLeft,
	StrafeRight,
};

class Player{
public:
	Player();
	~Player();
	void move(const sf::Vector2<float>& dir);
	void rotate(float dir);
	void draw(sf::RenderWindow & window);
	void turn(float angle);
	const sf::Vector2<float> & getCenter();
	float getAngle();
	sf::Vector2f forward();
	void doAction(sf::Keyboard::Key keyStroke);
	sf::Keyboard::Key keyToSwapIn;
	void swapKey(sf::Keyboard::Key keyToSwapOut);
	void swapOrDoAction(sf::Keyboard::Key keyStroke);
	sf::Vector2<float> left();
	void setSpeedMultiplier(float mul);
	bool isMoving();
private:
	float speedMult = 0.35f;
	sf::CircleShape triangle;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2<float> pos;
	float angle;
	bool moving = false;
	std::map<sf::Keyboard::Key, Action> map;
};
#endif
