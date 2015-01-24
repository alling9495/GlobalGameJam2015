#include "Camera.h"

#define DEFAULTPERCENT 02.5f
Camera::Camera(){
	width = 800;
	height = 600;
	percent = DEFAULTPERCENT;
	panel = sf::FloatRect(100, 100, width, height);
	view.reset(panel);
};

Camera::Camera(sf::Vector2<float> center): Camera() {
	view.reset(panel);
	previousLength = sqrt((center.x * center.x) + (center.y * center.y));
	previous = center;
};

Camera::~Camera(){
	
};

void Camera::setCenter(const sf::Vector2<float> & center){
	//sf::Vector2<float> direction = center;
	float length = sqrt((center.x * center.x) + (center.y * center.y));
	//float delta = previousLength - length;
	float deltaX = (center.x - previous.x) / 15;
	float deltaY = (center.y - previous.y) / 15;
	if (abs(deltaX) < 0.5f) {
		deltaX = 0;
	}
	if (abs(deltaY) < 0.1f) {
		deltaY = 0;
	}
	
	sf::Vector2<float> updatedCenter (previous.x + deltaX, previous.y + deltaY);
	view.setCenter(updatedCenter);
	previous = updatedCenter;
	previousLength = length;
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
	percent = DEFAULTPERCENT;
	panel.width = width * percent;
	panel.height = height * percent;
	view.reset(panel);
}

sf::View Camera::getView(){
	return view;
};
