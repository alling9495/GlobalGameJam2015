
class LinearBullet: public Bullet
{
public:
	LinearBullet(sf::Shape shape, int lifeCycle, float startX = 0, float startY = 0, 
		float vX = 1, float vX = 1): 
	LinearBullet(shape, lifeCycle, startX, startY, vX, vY)
	{
	
	}

	virtual bool move(float x = vX, float y = vY);


private:
}