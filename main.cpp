#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "WorldChunk.h"
#include "Camera.h"
#include "World.h"
#include "LinearBullet.h"
#include "VectorUtil.h"
#include "Particle.h"
#include <iostream>
#include <deque>
#include <ctime>
#include "StartPoint.h"
#define KEY_S(keyStroke) sf::Keyboard::Key::keyStroke

void closeWindowEvent(sf::RenderWindow & window, sf::Event event);
void startGameLoop();
void handleInput();
void update(sf::Time elapsed);

std::deque<Particle *> particles;
int frames = 0;

World world = World(time(0));
bool playDown = false;
StartPoint* startPoint;

sf::Music music;
int main()
{
    for(int i = 0; i < 250; i++){
        particles.push_back(new Particle()); //Static particle array
    }
    world.getPlayer().move(sf::Vector2f(-565,495));
    float particleCenterX = 200, particleCenterY = 200;

    sf::RenderWindow window(sf::VideoMode(800, 600), "attack_vector");
    window.setFramerateLimit(60);

    sf::Clock clock, totalClock;
    Camera camera (sf::Vector2f(VectorUtil::offset(world.getPlayer().getCenter(), world.getPlayer().forward()*12.0f)));
    

    
    //HUD stuff
    sf::Font font;
    if(!font.loadFromFile("font/FreeMonoBold.ttf") || 
        !music.openFromFile("derezzed8bit.ogg")) {
        std::cout << "Fail Whale!" << std::endl;
        //exit(1);
    }
    sf::Texture texture;
    if (!texture.loadFromFile("winner2.png")) {
        // error!
        std::cout << "You're (not) winner" << std::endl;
    }
    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.move(
        (window.getSize().x - texture.getSize().x) / 2,
        (window.getSize().y - texture.getSize().y) / 2);

    sf::Font cmdFont;
    if(!cmdFont.loadFromFile("font/FreeMonoBold.ttf")) {
        std::cout << "couldn't load cmd prompt font" << std::endl;
        //exit(1);
    }

    sf::Text level;
    level.setFont(font);
    level.setCharacterSize(30);
    startPoint = new StartPoint(sf::Vector2f(-1,-1));
    camera.resetZoom();
        // Create the points
        // 
    /*SHADER MAGIC! Setup...*/
    sf::VertexArray m_points;
    m_points.setPrimitiveType(sf::Points);
    /*
    for (int i = 0; i < 40000; ++i)
    {
        float x = static_cast<float>(std::rand() % 800);
        float y = static_cast<float>(std::rand() % 600);
        sf::Uint8 r = std::rand() % 255;
        sf::Uint8 g = std::rand() % 255;
        sf::Uint8 b = std::rand() % 255;
        m_points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(r, g, b)));
    }
    */
    /*giggity*/
    // Load the shader
    sf::Shader m_shader, m_light;
    m_light.loadFromFile("simpleLight.glsl",sf::Shader::Fragment);
    m_shader.loadFromFile("storm.vert", "blink.frag");
    music.setLoop(true);
    music.play();
    while (window.isOpen()) {
        if (!world.isPlayerAlive()) {
            world.loseGame();
            std::pair<int,int> playerChunk = world.getPlayerChunk();
            startPoint->setChunk(sf::Vector2f(playerChunk.first,playerChunk.second));
            startPoint->fadeIn();
            //window.close();
            //std::cout << "Player died" << std::endl;
            //window.close();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            closeWindowEvent(window, event);
        }
        
        sf::Vector2f playerCenter = world.getPlayer().getCenter();

        sf::Time elapsed = clock.restart(), totalTime = totalClock.getElapsedTime();
        world.update(elapsed);
        update(elapsed);

        
        if(!particles.back()->isAlive && world.getPlayer().isDashing() && frames>1)
        {
            particles.push_front(particles.back());
            particles.pop_back();
            particles[0]->init(world.getPlayer().getCenter().x, world.getPlayer().getCenter().y, world.getPlayer().getAngle());
            frames = 0;
        }

        frames++;
    
        camera.setCenter(VectorUtil::offset(world.getPlayer().getCenter(), world.getPlayer().forward()*12.0f));
        /*
        std::string location = "(" + std::to_string((int)(world.getPlayer().getCenter().x)) + ", " 
            + std::to_string((int)(world.getPlayer().getCenter().y)) + ")\n" + "Number of Particles" + 
            std::to_string(particles.size());
        */
       std::string curLevel;
       char buf[100];
       switch(world.level) {
          case -2:
             sprintf(buf, "");
             break;
          case -1:
             sprintf(buf, "Segmentation fault");
             break;
          case 0:
            curLevel = "unauthorized";
             break;
          case 1:
            curLevel = "user";
             break;
          case 2:
            curLevel = "privileged";
             break;
          case 3:
            curLevel = "admin";
             break;
          case 4:
            curLevel = "su";
             break;
          case 5:
            curLevel = "/";
             break;
       }
       if (world.level >= 0) {
          std::sprintf(buf, "Accessing '%s'...", curLevel.c_str());
       }
       level.setString(buf);

       // std::cout << location << std::endl;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            world.startGame();
        }

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

       // m_light.setParameter("time",totalTime.asSeconds());
        //m_light.setParameter("surfacePosition",playerCenter);
        //come on...



        window.draw(m_points,&m_shader);
        world.draw(window,&m_shader);
        startPoint->draw(window);

        //BULLETZ
        /*
        for(int i = 0; i < bullets.size(); i++)
        {
            if(bullets[i]->move(player))
            {
                std::cout << "rendering" << std::endl;
                bullets[i]->render(window);
                std::cout << "DONE!" << std::endl;
            }
            else
            {
                std::cout << "erasing" << std::endl;
                bullet toBack = bullets[i];
                bullets.erase(bullets.begin() + i);
                bullets.push_back()
                std::cout << "DONE!" << std::endl;
            }
        }
        */
        // Intro command prompt spawn point
        sf::Text cmdPrompt;
        cmdPrompt.setFont(cmdFont);
        cmdPrompt.setCharacterSize(100);
        cmdPrompt.setPosition(-480, 420);

        cmdPrompt.setString("user@GGJ:~$ ./attack_vector\nChris Williams\nAlex Ling,\nLejon McGowan\nKyle Piddington");
        if(world.state == GAMESTATE::TUTORIAL){
            window.draw(cmdPrompt);
        }

        for(int i = 0; i < particles.size() && particles[i]->isAlive; i++)
        {
            if(particles[i]->move(world.getPlayer().getCenter()))
            {
                particles[i]->draw(window);
            }
            else
            {
                Particle* p = particles[i];
                particles.erase(particles.begin() + i);
                particles.push_back(p);
            }
        }

        world.getPlayer().resetMoveState();
        //HUD VIEW
        window.setView(window.getDefaultView());
        window.draw(level);
        if (world.state == GAMESTATE::WON) {
            window.draw(sprite);
        }
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
    if(world.state != GAMESTATE::WON){
        sf::Keyboard::Key keySet[] = {KEY_S(W), KEY_S(S), KEY_S(A), KEY_S(D), KEY_S(I), KEY_S(K), KEY_S(L), KEY_S(J)};

        for (int i = 0; i < (sizeof(keySet) / sizeof(keySet[0])); i++) {
            if (sf::Keyboard::isKeyPressed(keySet[i])) {
                world.getPlayer().doAction(keySet[i]);
            }
        };
        if(sf::Keyboard::isKeyPressed(KEY_S(Space)) && !playDown)
        {
            music.getStatus() == sf::SoundSource::Playing?music.pause():music.play();
            world.getPlayer().toggleSound();
            playDown = true;
        }
        else if(!sf::Keyboard::isKeyPressed(KEY_S(Space)))
        {
            playDown = false;
        }
    }
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
    startPoint->update(elapsed);
    if(startPoint->isActive() && startPoint->pointIn(world.getPlayer().getCenter())){
        world.startGame();
        startPoint->fadeOut();
    }
};



