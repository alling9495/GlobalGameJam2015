#ifndef _CAMERA_H__
#define _CAMERA_H__
#include <SFML/Graphics.hpp>

class Camera{
public:
	Camera();
	~Camera();
	void setCenter(sf::Vector2<float> center);
	sf::View getView();
private:
	sf::View view;
	//sf::Vector2f<float> center;
};
#endif