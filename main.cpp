#include <SFML/Graphics.hpp>

void closeWindowEvent(sf::RenderWindow, sf::Event);

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Main Window");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            closeWindowEvent(window, event)
        }
        // The window was resized
        /*if (event.type == sf::Event::Resized) {
            doSomethingWithTheNewSize(event.size.width, event.size.height);
        }*/

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

void closeWindowEvent(sf::RenderWindow window, sf::Event event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    // The escape key was pressed
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
        window.close();
    }
}

/*void startGameLoop() {

}

void startGraphicsLoops() {

}

void pollInput() {

}*/

