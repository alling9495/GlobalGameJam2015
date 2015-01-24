#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Shape& shape, int lifeCycle, float startX = 0, float startY = 0, 
		float vX  = 1, float vY = 1):
	shape(shape),
	posX(startX),
	posY(startY),
	velX(vX),
	velY(vY),
	usingSprite(false)
	{
		lifeTime = sf::milliseconds(lifeCycle);
		shape.setPosition(posX,posY);
		timeAlive.restart();
	}

	virtual bool move(float x = 0, float y = 0) = 0;

	void render(sf::RenderWindow& window)
	{
		if(usingSprite)
			window.draw(sprite);
		else
			window.draw(shape);
	}
	~Bullet(){};


protected:
	bool usingSprite;
	sf::Time lifeTime;
	sf::Clock timeAlive;
	sf::Shape& shape;
	sf::Sprite sprite;
	float posX, posY; 
	float velX,velY;//future use	

	bool stillAlive()
	{
		return timeAlive.getElapsedTime().asMilliseconds() < lifeTime.asMilliseconds();
	}

};