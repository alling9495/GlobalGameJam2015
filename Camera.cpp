#include "Camera.h"

Camera::Camera(){
	view.reset(sf::FloatRect(100, 100, 800, 600));
};
Camera::~Camera(){

};

void Camera::setCenter(sf::Vector2<float> center){
	view.setCenter(center);
}

sf::View Camera::getView(){
	return view;
};
