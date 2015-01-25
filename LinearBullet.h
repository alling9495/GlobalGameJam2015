#include "Bullet.h"

class LinearBullet: public Bullet
{
public:
	LinearBullet(sf::Shape& shape, int lifeCycle, float startX = 0, float startY = 0, 
		float vX = 1, float vY = 1): 
	Bullet(shape, lifeCycle, startX, startY, vX, vY)
	{
		
	}

	virtual bool move(float x, float y);


private:
};