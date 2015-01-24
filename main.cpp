#include <SFML/Graphics.hpp>
#include "Player.h"
#include "WorldChunk.h"
#include "Camera.h"
#include "World.h"
#include <iostream>

void closeWindowEvent(sf::RenderWindow & window, sf::Event event);
void startGameLoop();
void handleInput();
void update(sf::Time elapsed);
void startGraphicsLoops();
void pollInput();

World world = World(0);
int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock clock;
    Camera camera (world.getPlayer().getCenter());

    //HUD stuff
    sf::Font font;
    if(!font.loadFromFile("font/FreeMono.ttf")) {
        std::cout << "Fail Whale!" << std::endl;
        //exit(1);
    }

    sf::Text coordinates;
    coordinates.setFont(font);
    coordinates.setCharacterSize(30);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            closeWindowEvent(window, event);
        }
        sf::Time elapsed = clock.restart();
        world.update(elapsed);
        update(elapsed);
        camera.setCenter(world.getPlayer().getCenter());
        std::string location = "(" + std::to_string((int)(world.getPlayer().getCenter().x)) + ", " 
            + std::to_string((int)(world.getPlayer().getCenter().y)) + ")";
        
        coordinates.setString(location);

       // std::cout << location << std::endl;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
            camera.zoomOut(0.05f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            camera.zoomIn(0.05f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
            camera.resetZoom();
        }

        window.setView(camera.getView());
        window.clear();
        //wc->draw(window);
        window.draw(shape);

        world.draw(window);
        window.setView(window.getDefaultView());
        window.draw(coordinates);
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
        world.getPlayer().keyToSwapIn = sf::Keyboard::A;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        world.getPlayer().keyToSwapIn = sf::Keyboard::S;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        world.getPlayer().doAction(sf::Keyboard::D);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        world.getPlayer().doAction(sf::Keyboard::F);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
        world.getPlayer().doAction(sf::Keyboard::J);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        world.getPlayer().swapOrDoAction(sf::Keyboard::F);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
        world.getPlayer().swapOrDoAction(sf::Keyboard::J);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
        world.getPlayer().swapOrDoAction(sf::Keyboard::K);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
        world.getPlayer().keyToSwapIn = sf::Keyboard::L;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)){
        world.getPlayer().keyToSwapIn = sf::Keyboard::SemiColon;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
        world.getPlayer().doAction(sf::Keyboard::G);
    }

}

void update(sf::Time elapsed) {
    handleInput();
}

void startGraphicsLoops() {
}

void pollInput() {
}
