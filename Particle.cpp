#include "Particle.h"

Particle::Particle() { 
    shape = sf::RectangleShape (sf::Vector2f(25.f, 25.f));
    lifeTime = sf::milliseconds(250);
    isAlive=false;
    texture.loadFromFile("player.png");
        // error!
        //std::cout << "unable to load player sprite" << std::endl;
    
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sf::Vector2u textureSize = texture.getSize();
    sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
    lifeTime = sf::milliseconds(255);
};

Particle::Particle(float x, float y, float angle): Particle() {
   previous = sf::Vector2f(x, y);
   shape.setRotation(angle);
   sprite.setRotation(angle+90);
};

void Particle::init(float x, float y, float angle){
   timeAlive = sf::Clock();
   previous = sf::Vector2f(x, y);
   sprite.setRotation(angle+90);
   sprite.setPosition(previous);
    sprite.setColor(sf::Color(255,255,255,200));    
   isAlive=true;
}

Particle::~Particle() {};

bool Particle::move(const sf::Vector2<float> & center) {
    /*float deltaX = (center.x + (rand() % 201 + (-100)) * 4 - previous.x ) / 15;
    float deltaY = (center.y + (rand() % 201 + (-100)) * 4 - previous.y ) / 15;*/
    float deltaX = (center.x - previous.x) / 10;
    float deltaY = (center.y - previous.y) / 10;
    //shape.setFillColor(sf::Color(rand()%244, 0, rand()%244));
    sprite.setColor(sf::Color(255,255,255,sprite.getColor().a*0.9));
    //std::cout << lifeTime.asMilliseconds() << std::endl;
    /*if (abs(deltaX) < 0.5f) {
        deltaX = 0;
    }
    if (abs(deltaY) < 0.1f) {
        deltaY = 0;
    }*/
    
    sf::Vector2f updatedCenter (previous.x - deltaX, previous.y - deltaY);
    //sprite.setPosition(updatedCenter);
    previous = updatedCenter;
    isAlive = stillAlive();
    return stillAlive();
};

void Particle::draw(sf::RenderWindow & window) {
    window.draw(sprite);
};

bool Particle::stillAlive() {
    return timeAlive.getElapsedTime().asMilliseconds() < lifeTime.asMilliseconds();
};
