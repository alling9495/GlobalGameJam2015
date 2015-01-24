#include "Player.h"

Player::Player(){
	triangle = sf::CircleShape(80.0f,3);
	triangle.setOrigin(80.0f,80.0f);
	triangle.setScale(0.5,0.75);

	keys[0] = sf::Keyboard::A; // shield?
	keys[1] = sf::Keyboard::S; // flamethrower?
	keys[2] = sf::Keyboard::D; // turn counter-clockwise
	keys[3] = sf::Keyboard::F; // forward
	keys[4] = sf::Keyboard::J; // back
	keys[5] = sf::Keyboard::K; // turn clockwise
	keys[6] = sf::Keyboard::L; // lazer?
	keys[7] = sf::Keyboard::SemiColon; // LIMIT BREEEEEEEEAK!!!!
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

sf::Keyboard::Key Player::getKeyAt(int index) {
	return keys[index];
}
