#include "Player.h"

Player::Player(){
	triangle = sf::CircleShape(80.0f,3);
	triangle.setOrigin(80.0f,80.0f);
	triangle.setScale(0.5,0.75);

	actions[0] = 0;
	actions[1] = 1;
	actions[2] = 2;
	actions[3] = 3;
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

void Player::doAction(int index) {
	switch(actions[index]) {
		case 0:
			// turn counter-clockwise
            turn(-3);
			break;
		case 1:
			// move forward
            move(forward() * 0.15f);
			break;
		case 2:
			// move backwards
            move(forward() * -0.05f);
			break;
		case 3:
			// turn clockwise
            turn(3);
			break;
		case 4:
			// TODO flamethrower
			break;
		case 5:
			// TODO lazer
			break;
		case 6:
			// TODO shield
			break;
		case 7:
			// TODO LIMIT BREAK
			break;
	}
}
