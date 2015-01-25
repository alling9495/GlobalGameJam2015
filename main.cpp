#include <SFML/Graphics.hpp>
#include "Player.h"
#include "WorldChunk.h"
#include "Camera.h"
#include "World.h"
#include "LinearBullet.h"
#include "VectorUtil.h"
#include <iostream>
#include <deque>
#define KEY_S(keyStroke) sf::Keyboard::Key::keyStroke

void closeWindowEvent(sf::RenderWindow & window, sf::Event event);
void startGameLoop();
void handleInput();
void update(sf::Time elapsed);
void startGraphicsLoops();
void pollInput();

std::deque<Bullet *> bullets;
sf::CircleShape bulletImage(10.0f);


World world = World(0);
int main()
{
    float particleCenterX = 200, particleCenterY = 200;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock, totalClock;
    Camera camera (world.getPlayer().getCenter());

    //HUD stuff
    sf::Font font;
    if(!font.loadFromFile("font/FreeSansBold.ttf")) {
        std::cout << "Fail Whale!" << std::endl;
        //exit(1);
    }

    sf::Text coordinates;
    coordinates.setFont(font);
    coordinates.setCharacterSize(30);
    
    camera.resetZoom();
        // Create the points
        // 
    /*SHADER MAGIC! Setup...*/
    sf::VertexArray m_points;
    m_points.setPrimitiveType(sf::Points);
    for (int i = 0; i < 40000; ++i)
    {
        float x = static_cast<float>(std::rand() % 800);
        float y = static_cast<float>(std::rand() % 600);
        sf::Uint8 r = std::rand() % 255;
        sf::Uint8 g = std::rand() % 255;
        sf::Uint8 b = std::rand() % 255;
        m_points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(r, g, b)));
    }
    /*giggity*/
    // Load the shader
    sf::Shader m_shader;
    m_shader.loadFromFile("storm.vert", "blink.frag");

    while (window.isOpen()) {
        if (!world.isPlayerAlive()) {
            window.close();
            //std::cout << "Player died" << std::endl;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            closeWindowEvent(window, event);
        }
        
        sf::Vector2f playerCenter = world.getPlayer().getCenter();

        sf::Time elapsed = clock.restart(), totalTime = totalClock.getElapsedTime();
        world.update(elapsed);
        update(elapsed);
        camera.setCenter(VectorUtil::offset(world.getPlayer().getCenter(), world.getPlayer().forward()*4.0f));
        std::string location = "(" + std::to_string((int)(world.getPlayer().getCenter().x)) + ", " 
            + std::to_string((int)(world.getPlayer().getCenter().y)) + ")\n" + "Number of Bullets" + 
            std::to_string(bullets.size());
        
        coordinates.setString(location);

       // std::cout << location << std::endl;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
            camera.zoomOut(0.05f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
            camera.zoomIn(0.05f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
            camera.resetZoom();
        }

        window.setView(camera.getView());
        window.clear();

        /*ANND the update!*/
        float radius = 150 /*std::cos(totalTime.asSeconds()) * 300*/;
        m_shader.setParameter("storm_position", playerCenter.x , playerCenter.y);
        m_shader.setParameter("storm_inner_radius", radius / 3);
        m_shader.setParameter("storm_total_radius", radius);
        m_shader.setParameter("blink_alpha", 1.0f /**std::cos(totalTime.asSeconds() * 3) * 0.25f*/);

        //come on...
        window.draw(m_points,&m_shader);
        window.draw(shape);

        world.draw(window, &m_shader);

        //BULLETZ
         
        for(int i = 0; i < bullets.size(); i++)
        {
            if(bullets[i]->move())
            {
                std::cout << "rendering" << std::endl;
                bullets[i]->render(window);
                std::cout << "DONE!" << std::endl;
            }
            else
            {
                std::cout << "erasing" << std::endl;
                delete bullets[i];
                 bullets.erase(bullets.begin() + i);
                 std::cout << "DONE!" << std::endl;
            }
        }
        

        //HUD VIEW
        window.setView(window.getDefaultView());
        window.draw(coordinates);
        window.display();
    }
    return 0;
};


void closeWindowEvent(sf::RenderWindow & window, sf::Event event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    // The escape key was pressed
    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
        window.close();
    }
};

void startGameLoop() {
};

void handleInput() {
    sf::Keyboard::Key keySet[] = {KEY_S(W), KEY_S(S), KEY_S(A), KEY_S(D), KEY_S(I), KEY_S(K), KEY_S(L), KEY_S(J)};
    
    bulletImage.setFillColor(sf::Color::Green);

    for (int i = 0; i < 8; i++) {
        if (sf::Keyboard::isKeyPressed(keySet[i])) {
            world.getPlayer().doAction(keySet[i]);
        }
    };
/*    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        world.getPlayer().doAction(sf::Keyboard::A);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        world.getPlayer().doAction(sf::Keyboard::S);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        world.getPlayer().doAction(sf::Keyboard::D);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        world.getPlayer().doAction(sf::Keyboard::F);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        bullets.push_front(new LinearBullet(bulletImage,1000,world.getPlayer().getCenter().x,world.getPlayer().getCenter().y,
            world.getPlayer().forward().x * 0.5,world.getPlayer().forward().y * 0.5));
    }*/

};

void update(sf::Time elapsed) {
    handleInput();
};

void startGraphicsLoops() {
};

void pollInput() {
};
