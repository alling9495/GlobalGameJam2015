#include "Player.h"

Player::Player(){
	triangle = sf::CircleShape(80.0f,3);
	triangle.setOrigin(80.0f,80.0f);
	triangle.setScale(0.5,0.75);

	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::D, TurnCounter));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::F, Forward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::J, Backward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::K, TurnClockwise));
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

sf::Vector2<float> Player::forward(){
	return sf::Vector2<float>
		((float)cos(angle*1/RAD2DEGf) * RAD2DEGf,(float)sin(angle*1/RAD2DEGf) * RAD2DEGf);
}

void Player::doAction(sf::Keyboard::Key keyStroke) {
	switch(map[keyStroke]) {
		case TurnCounter:
			// turn counter-clockwise
            turn(-3);
			break;
		case Forward:
			// move forward
            move(forward() * 0.15f);
			break;
		case Backward:
			// move backwards
            move(forward() * -0.05f);
			break;
		case TurnClockwise:
			// turn clockwise
            turn(3);
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
			break;
	}
}
