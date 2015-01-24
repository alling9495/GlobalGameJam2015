#include "LinearBullet.h"

bool LinearBullet::move(float x = 0, float y = 0)
{
	sf::Transformable bullet;
	if(usingSprite)
		bullet = sprite;
	else
		bullet = shape;

	if(x == 0 && y == 0)
		bullet.move(velX,velY);
	else
		bullet.move(x,y);

	return stillAlive();
}