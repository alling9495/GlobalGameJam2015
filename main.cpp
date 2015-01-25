#include <SFML/Graphics.hpp>
#include "Player.h"
#include "WorldChunk.h"
#include "Camera.h"
#include "World.h"

void closeWindowEvent(sf::RenderWindow & window, sf::Event event);
void startGameLoop();
void handleInput();
void update(sf::Time elapsed);
void startGraphicsLoops();
void pollInput();

World world = World(0);
int main()
{

    //WorldChunk* wc = new WorldChunk(0,0,0);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock clock;
    Camera camera (world.getPlayer().getCenter());


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            closeWindowEvent(window, event);
        }
        sf::Time elapsed = clock.restart();
        world.update(elapsed);
        update(elapsed);
        camera.setCenter(world.getPlayer().getCenter());
        window.setView(camera.getView());
        window.clear();
        //wc->draw(window);
        window.draw(shape);

        world.draw(window);
        window.display();
    }

    return 0;
}

void closeWindowEvent(sf::RenderWindow & window, sf::Event event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    // The escape key was pressed
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
        window.close();
    }
}

void startGameLoop() {
}

void handleInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        world.getPlayer().move(world.getPlayer().forward() * 0.15f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
        world.getPlayer().move(world.getPlayer().forward() * -0.05f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        world.getPlayer().turn(3);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
        world.getPlayer().turn(-3);
    }
}

void update(sf::Time elapsed) {
    handleInput();
}

void startGraphicsLoops() {
}

void pollInput() {
}
