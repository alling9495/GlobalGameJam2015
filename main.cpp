#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Tile.h"

void closeWindowEvent(sf::RenderWindow & window, sf::Event event);
void startGameLoop();
void handleInput();
void update(sf::Time elapsed);
void startGraphicsLoops();
void pollInput();

Player player;

int main()
{

    Tile test1 = Tile(0,1,1);
    Tile test2 = Tile(0,1,2);
    Tile test3 = Tile(0,2,1);
    Tile test4 = Tile(0,2,2);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            closeWindowEvent(window, event);
        }

        sf::Time elapsed = clock.restart();
        update(elapsed);

        window.clear();
        window.draw(shape);
        player.draw(window);
        test1.draw(window);
        test2.draw(window);
        test3.draw(window);
        test4.draw(window);
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
        player.move(player.forward() * 0.15f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
        player.move(player.forward() * -0.05f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        player.turn(3);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
        player.turn(-3);
    }
}

void update(sf::Time elapsed) {
    handleInput();
}

void startGraphicsLoops() {
}

void pollInput() {
}