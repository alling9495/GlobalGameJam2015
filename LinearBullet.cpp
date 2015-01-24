#include "LinearBullet.h"

bool LinearBullet::move(float x = 0, float y = 0)
{
	if(!usingSprite)
	{

		if(x == 0 && y == 0)
			shape.move(velX,velY);
		else
			shape.move(x,y);
	}
	else
	{

		if(x == 0 && y == 0)
			sprite.move(velX,velY);
		else
			sprite.move(x,y);	
	}
	return stillAlive();
}