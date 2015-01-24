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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
            camera.zoomOut(0.05f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            camera.zoomIn(0.05f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
            camera.resetZoom();
        }

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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        // swap
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        // swap
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        player.doAction(sf::Keyboard::D);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        player.doAction(sf::Keyboard::F);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
        player.doAction(sf::Keyboard::J);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
        player.doAction(sf::Keyboard::K);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
        // swap
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)){
        // swap
    }

}

void update(sf::Time elapsed) {
    handleInput();
}

void startGraphicsLoops() {
}

void pollInput() {
}
