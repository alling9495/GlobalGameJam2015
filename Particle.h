#ifndef _PARTICLE_H
#define _PARTICLE_H
#include <SFML/Graphics.hpp>
#include <math.h>
class Particle{
public:
    Particle();
    Particle(float x, float y, float angle);
    void init(float x, float y, float angle);
    ~Particle();
    bool move(const sf::Vector2<float> & center);
    void draw(sf::RenderWindow & window);
    bool stillAlive();
    bool isAlive = false;
private:
    sf::RectangleShape shape;
    sf::Clock timeAlive;
    sf::Time lifeTime;
    sf::Vector2f previous;

    //sf::Spite sprite;
};
#endif