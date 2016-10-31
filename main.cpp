#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "WorldChunk.h"
#include "Camera.h"
#include "World.h"
#include "LinearBullet.h"
#include "VectorUtil.h"
#include "Particle.h"
#include "StartPoint.h"
#include "ArrowIndicator.h"
#include "FlavorText.h"

#include <iostream>
#include <deque>
#include <ctime>
#define KEY_S(keyStroke) sf::Keyboard::Key::keyStroke

void closeWindowEvent(sf::RenderWindow & window, sf::Event event);
void startGameLoop();
void handleInput();
void update(sf::Time elapsed);

std::deque<Particle *> particles;
int frames = 0;

World world = World(time(0));
bool playDown = false, immDown = false;
StartPoint* startPoint;
ArrowIndicator * indicator;
sf::Music music;
FlavorText terminalLines = FlavorText("flavortext.txt");
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
    level.setCharacterSize(15);
    startPoint = new StartPoint(sf::Vector2f(0,0));
    indicator = new ArrowIndicator();
    level.setPosition(0,20);

    sf::Text terminalMessage;
    terminalMessage.setFont(font);
    terminalMessage.setCharacterSize(20);
    

    terminalMessage.setString(terminalLines.randomLine());


    camera.resetZoom();
      
    /*SHADER MAGIC! Setup...*/
    sf::VertexArray m_points;
    m_points.setPrimitiveType(sf::Points);
    
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
        bool changed = false;
        if((int)totalTime.asSeconds() % 5 == 0)
        {
            if(!changed)
            {
                terminalMessage.setString(terminalLines.randomLine()); 
                changed = true;
            }
        }
        else
        {
            changed = false;
        }
        world.update(elapsed);
        update(elapsed);

        sf::Sprite& sprite = world.getPlayer().getSprite();
        if(!particles.back()->isAlive && world.getPlayer().isDashing() && frames>1)
        {
            particles.push_front(particles.back());
            particles.pop_back();
            particles[0]->init(world.getPlayer().getCenter().x, world.getPlayer().getCenter().y, world.getPlayer().getAngle());
            frames = 0;
            if(sprite.getScale().x > MIN_SCALE)
            {
                sprite.scale(0.9,1.0);
                particles[0]->getSprite().scale(0.9,1.0);
                if(sprite.getScale().x > MAX_SCALE)
                {
                    sprite.setScale(MAX_SCALE,1.0);
                    particles[0]->getSprite().setScale(MAX_SCALE,1.0);
                }
            }


        }
        
        if(!world.getPlayer().isDashing())
        {
            if(sprite.getScale().x  < MAX_SCALE)
            {
                sprite.scale(1.1,1.0);
                particles[0]->getSprite().scale(1.1,1.0);
                if(sprite.getScale().x < MIN_SCALE)
                {
                    sprite.setScale(MIN_SCALE,1.0);
                    particles[0]->getSprite().setScale(MIN_SCALE,1.0);
                }
            }
        }

        frames++;
    
        camera.setCenter(VectorUtil::offset(world.getPlayer().getCenter(), world.getPlayer().forward()*12.0f));
       
       std::string curLevel;
       char buf[100];
       switch(world.level) {
          case -2:
             sprintf(buf, " ");
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
       //terminalMessage.setString(terminalLines.randomLine());
       // std::cout << location << std::endl;
       // Debug controls

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
        if(startPoint->isActive() && (
         (abs(startPoint->x - world.getPlayerChunk().first) > 1) || (abs(startPoint->y - world.getPlayerChunk().second) > 1))) {
            indicator->point(world.getPlayer().getCenter(), startPoint->position);
            indicator->draw(window);
        }
        
        // Intro command prompt spawn point
        sf::Text cmdPrompt;
        cmdPrompt.setFont(cmdFont);
        cmdPrompt.setCharacterSize(100);
        cmdPrompt.setPosition(-480, 420);

        cmdPrompt.setString("user@GGJ:~$ ./attack_vector\
            \n@controls\n\tWASD / Arrows: move\n\tM: mute\n\tR: reset\n\tSpace / I: boost\
            \n@author\n\tChris Williams\n\tAlex Ling,\n\tLejon McGowan\n\tKyle Piddington\
            \n@story\
            \n\tYou're a loose pointer\
            \n\trunning away from the\
            \n\tgarbage collector as you\
            \n\tare trying to gain greater\
            \n\taccess to the system.\
            \n\tAchieve root access to\
            \n\tbeat the system!\
            \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nTODO easter egg");
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
        //window.draw(level);
        window.draw(terminalMessage);
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
        sf::Keyboard::Key keySet[] = {KEY_S(W), KEY_S(Up), KEY_S(A), KEY_S(Left), KEY_S(D), KEY_S(Right), KEY_S(Space), KEY_S(I)};

        for (int i = 0; i < (sizeof(keySet) / sizeof(keySet[0])); i++) {
            if (sf::Keyboard::isKeyPressed(keySet[i])) {
                // No double up/right/left/boost
                if (i%2 == 1 && sf::Keyboard::isKeyPressed(keySet[i-1])) {
                    continue;
                }
                world.getPlayer().doAction(keySet[i]);
            }
        };
        if(sf::Keyboard::isKeyPressed(KEY_S(M)) && !playDown)
        {
            music.getStatus() == sf::SoundSource::Playing?music.pause():music.play();
            world.getPlayer().toggleSound();
            playDown = true;
        }
        else if(!sf::Keyboard::isKeyPressed(KEY_S(M)))
        {
            playDown = false;
        }

        if(sf::Keyboard::isKeyPressed(KEY_S(G)) && !immDown)
        {
            world.toggleImmortality();
            immDown = true;
        }
        else if(!sf::Keyboard::isKeyPressed(KEY_S(G)))
        {
            immDown = false;
        }
    }


};



void update(sf::Time elapsed) {
    handleInput();
    startPoint->update(elapsed);
    if(startPoint->isActive() && startPoint->pointIn(world.getPlayer().getCenter())){
        world.startGame();
        startPoint->fadeOut();

    }

};




