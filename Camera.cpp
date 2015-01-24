#include "Camera.h"
#include <stdio.h>
#include <math.h>

Camera::Camera(){
	width = 800;
	height = 600;
	percent = 1.0f;
	panel = sf::FloatRect(100, 100, width, height);
	view.reset(panel);
};

Camera::Camera(sf::Vector2<float> center): Camera() {
	view.reset(panel);
	previous = center;
};

Camera::~Camera(){
	
};

void Camera::setCenter(const sf::Vector2<float> & center){
	//sf::Vector2<float> direction = center;
	float length = sqrt((center.x * center.x) + (center.y * center.y));
	float centerX = center.x * 100;
	float centerY = center.y * 100;
	printf("%f, %f, %f\n", length, centerX, centerY);
	view.setCenter(center);
	previous = center;
};

void Camera::zoomOut(float percentIncrement) {
	percent += percentIncrement;
	panel.width = width * percent;
	panel.height = height * percent;
	view.reset(panel);
};

void Camera::zoomIn(float percentIncrement) {
	percent -= percentIncrement;
	panel.width = width * percent;
	panel.height = height * percent;
	view.reset(panel);
};

void Camera::resetZoom() {
	percent = 1.0f;
	panel.width = width * percent;
	panel.height = height * percent;
	view.reset(panel);
}

sf::View Camera::getView(){
	return view;
};
