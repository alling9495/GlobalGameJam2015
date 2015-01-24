#include "Camera.h"
#include <stdio.h>
#include <math.h>

Camera::Camera(){
	view.reset(sf::FloatRect(100, 100, 800, 600));
};

Camera::Camera(sf::Vector2<float> center) {
	view.reset(sf::FloatRect(100, 100, 800, 600));
	previous = center;
};

Camera::~Camera(){
	
};

void Camera::setCenter(const sf::Vector2<float> & center){
	//sf::Vector2<float> direction = center;
	float length = sqrt((center.x * center.x) + (center.y * center.y));
	float centerX = center.x * 100;
	float centerY = center.y * 100;
	printf("%f, %f, %f\n", &length, &centerX, &centerY);
	view.setCenter(center);
	previous = center;
};

sf::View Camera::getView(){
	return view;
};
