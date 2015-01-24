#ifndef _CAMERA_H__
#define _CAMERA_H__
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Camera{
public:
	Camera();
	Camera(sf::Vector2<float> center);
	~Camera();
	void setCenter(const sf::Vector2<float> & center);
	sf::View getView();
	void zoomOut(float percentIncrement);
	void zoomIn(float percentIncrement);
	void resetZoom();
private:
	sf::View view;
	sf::Vector2<float> previous;
	sf::FloatRect panel;
	float width;
	float height;
	float percent;
	float previousLength;
	//sf::Vector2f<float> center;
};
#endif