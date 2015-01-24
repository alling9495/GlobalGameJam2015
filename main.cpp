#include <SFML/Graphics.hpp>
#include "Player.h"
void update(sf::Time elapsed);
void handleInput();
Player player;
int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Request for closing the window

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // The escape key was pressed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        sf::Time elapsed = clock.restart();
        update(elapsed);

    // The window was resized
    /*if (event.type == sf::Event::Resized) {
        doSomethingWithTheNewSize(event.size.width, event.size.height);
    }*/

        window.clear();
        window.draw(shape);
        player.draw(window);
        window.display();
    }

    return 0;
}

void startGameLoop() {


}

void update(sf::Time elapsed){
    handleInput();
}
void handleInput(){
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


