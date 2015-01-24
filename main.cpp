#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Camera.h"

void closeWindowEvent(sf::RenderWindow & window, sf::Event event);
void startGameLoop();
void handleInput();
void update(sf::Time elapsed);
void startGraphicsLoops();
void pollInput();

Player player;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock clock;
    Camera camera (player.getCenter());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            closeWindowEvent(window, event);
        }
        sf::Time elapsed = clock.restart();
        update(elapsed);
        camera.setCenter(player.getCenter());
        window.setView(camera.getView());
        window.clear();
        window.draw(shape);
        player.draw(window);
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
        // TODO Swap keys
    } else {
        // Do action
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(0))){
            // TODO shield
        }
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(1))){
            // TODO flamethrower
        }
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(2))){
            player.turn(-3);
        }
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(3))){
            player.move(player.forward() * 0.15f);
        }
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(4))){
            player.move(player.forward() * -0.05f);
        }
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(5))){
            player.turn(3);
        }
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(6))){
            // TODO lazar
        }
        if(sf::Keyboard::isKeyPressed(player.getKeyAt(7))){
            // TODO LIMIT BREEEEEEEEEEAK!!!!!!
        }
    }
}

void update(sf::Time elapsed) {
    handleInput();
}

void startGraphicsLoops() {
}

void pollInput() {
}
