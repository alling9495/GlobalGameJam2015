#include <SFML/Graphics.hpp>
#include <iostream>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

int main()
{
    //mandatory render window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "SFML works!");

    //circleEnemy
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100,100);
    shape.setOrigin(100,100);

    //shooting nozzle
    sf::RectangleShape aimingReticule(sf::Vector2f(130,8));
    aimingReticule.setPosition(100,100);

    //font setup
    sf::Font font;
    if(!font.loadFromFile("font/FreeMono.ttf"));
    {
        std::cout << "Fail Whale!" << std::endl;
        //exit(1);
    }
    std::cout << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
    //label setup
    sf::Text hello;

    hello.setFont(font);
    hello.setString("Hello World");
    hello.setCharacterSize(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        shape.rotate(1);
        aimingReticule.rotate(1);

        window.draw(shape);
        window.draw(hello);
        window.draw(aimingReticule);

        window.display();
    }

    return 0;
}
