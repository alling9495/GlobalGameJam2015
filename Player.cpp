#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(){

	triangle = sf::CircleShape(80.0f,3);
	triangle.setOrigin(80.0f,80.0f);
	triangle.setScale(0.5,0.75);

	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::A, TurnCounter));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::W, Forward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::S, Backward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::D, TurnClockwise));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::G, SuperBoost));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::J, StrafeLeft));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::L, StrafeRight));

	// Keys to swap
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::A, Flamethrower));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::S, Lazer));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::L, Shield));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::SemiColon, LimitBreak));

	keyToSwapIn = sf::Keyboard::Unknown;
}
Player::~Player(){

}

void Player::move(const sf::Vector2<float>& dir){
	pos += dir;

	triangle.setPosition(pos.x,pos.y);
}
void Player::draw(sf::RenderWindow & window){
	window.draw(triangle);
}
void Player::turn(float deg){
	angle += deg;
	triangle.setRotation(angle+90);
}

const sf::Vector2<float> & Player::getCenter(){
	return pos;
}

sf::Vector2f Player::forward(){
	triangle.setRotation(angle+90);	
	return sf::Vector2f
		((float)cos(angle*1/RAD2DEGf) * RAD2DEGf,(float)sin(angle*1/RAD2DEGf) * RAD2DEGf);
}

void Player::doAction(sf::Keyboard::Key keyStroke) {
	switch(map[keyStroke]) {
		case TurnCounter:
			// turn counter-clockwise
            turn(-7);
			break;
		case Forward:
			// move forward
            move(forward() * 0.35f);
			break;
		case Backward:
			// move backwards
            move(forward() * -0.05f);
			break;
		case TurnClockwise:
			// turn clockwise
            turn(7);
			break;
		case Flamethrower:
			// TODO flamethrower
			break;
		case Lazer:
			// TODO lazer
			break;
		case Shield:
			// TODO shield
			break;
		case LimitBreak:
			// TODO LIMIT BREAK
		case SuperBoost:
			move(forward() * 1.5f);
			break;
		case StrafeLeft:
			move(left() * 0.3f);
			break;
		case StrafeRight:
			move(left() * -0.3f);
			break;
		default:
			break;
	}
}

void Player::swapKey(sf::Keyboard::Key keyToSwapOut) {
	Action actionToSwapOut = map[keyToSwapOut];

	map[keyToSwapOut] = map[keyToSwapIn];
	map[keyToSwapIn] = actionToSwapOut;

	keyToSwapIn = sf::Keyboard::Unknown;
}

void Player::swapOrDoAction(sf::Keyboard::Key keyStroke) {
	doAction(keyStroke);
    /*
    if (keyToSwapIn == sf::Keyboard::Unknown) {
        doAction(keyStroke);
    } else {
        swapKey(keyStroke);
    }
    */
}
sf::Vector2f Player::left(){
	sf::Vector2f fwd = forward();
	sf::Vector2f left = sf::Vector2f(
		(cos(M_PI/2)*fwd.x + sin(M_PI/2)*fwd.y),
		(-sin(M_PI/2)*fwd.x + cos(M_PI/2)*fwd.y));
	return left;
}
