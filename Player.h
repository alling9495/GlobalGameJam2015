#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <map>

#define MAX_SCALE 1
#define MIN_SCALE 0.6

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
	void draw(sf::RenderWindow & window, sf::Shader* shader = NULL);
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
	bool isDashing();
	void resetMoveState();
	void setColor(sf::Color c);
	void toggleSound();
	sf::Sprite& getSprite();
private:
	void flipEffect();
	sf::SoundBuffer sfxBuffer;
	bool mute;
	sf::Sound sfx;
	float speedMult = 0.35f;
	sf::CircleShape triangle;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2<float> pos;
	float angle;
	bool moving = false;
	bool dashing = false;
	std::map<sf::Keyboard::Key, Action> map;
};
#endif
