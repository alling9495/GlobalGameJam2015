#include "Particle.h"

Particle::Particle() { 
    shape = sf::RectangleShape (sf::Vector2f(25.f, 25.f));
    lifeTime = sf::milliseconds(250);
};

Particle::Particle(float x, float y, float angle): Particle() {
   previous = sf::Vector2f(x, y);
   shape.setRotation(angle);
};

Particle::~Particle() {};

bool Particle::move(const sf::Vector2<float> & center) {
    float deltaX = (center.x + (rand() % 201 + (-100)) * 4 - previous.x ) / 15;
    float deltaY = (center.y + (rand() % 201 + (-100)) * 4 - previous.y ) / 15;

    shape.setFillColor(sf::Color(rand()%244, 0, rand()%244));
    /*if (abs(deltaX) < 0.5f) {
        deltaX = 0;
    }
    if (abs(deltaY) < 0.1f) {
        deltaY = 0;
    }*/
    
    sf::Vector2f updatedCenter (previous.x - deltaX, previous.y - deltaY);
    shape.setPosition(updatedCenter);
    previous = updatedCenter;
    return stillAlive();
};

void Particle::draw(sf::RenderWindow & window) {
    window.draw(shape);
};

bool Particle::stillAlive() {
    return timeAlive.getElapsedTime().asMilliseconds() < lifeTime.asMilliseconds();
};