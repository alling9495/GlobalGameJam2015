#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Main Window");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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

void startGameLoop() {

}

