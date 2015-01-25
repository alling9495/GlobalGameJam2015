#ifndef _PARTICLE_H
#define _PARTICLE_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
class Particle{
public:
    Particle();
    Particle(float x, float y, float angle);
    ~Particle();
    bool move(const sf::Vector2<float> & center);
    void draw(sf::RenderWindow & window);
    bool stillAlive();
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock timeAlive;
    sf::Time lifeTime;
    sf::Vector2f previous;
    //sf::Spite sprite;
};
#endif