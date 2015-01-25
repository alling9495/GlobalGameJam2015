#include "ArrowIndicator.h"
#include <math.h>
#define RAD2DEG 180.0f/M_PI
ArrowIndicator::ArrowIndicator(){
	indicator = sf::CircleShape(80,3);
	indicator.setOrigin(80,80);
	indicator.setFillColor(sf::Color(0,0,0,0));
	indicator.setOutlineColor(sf::Color(0,255,0));
	indicator.setOutlineThickness(5);
	indicator.setScale(1,1.2);
}
ArrowIndicator::~ArrowIndicator(){}
void ArrowIndicator::point(sf::Vector2f center, sf::Vector2f target){
	indicator.setPosition(center);
	float angle = atan2(target.y-center.y,target.x-center.x);
	angle *= RAD2DEG;
	indicator.setRotation(angle+90);
}

void ArrowIndicator::draw(sf::RenderWindow & window){
	window.draw(indicator);
}