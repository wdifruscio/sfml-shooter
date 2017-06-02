#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

void update()
{
    
}

int main()
{
    
    VideoMode vm(600,800);
    RenderWindow window(vm,"Game Boilerplate");
    window.setFramerateLimit(60);
    //instantiate textures
    Texture textureBackground;
    textureBackground.loadFromFile("assets/purple.png");
    textureBackground.setRepeated(true);

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setTextureRect(IntRect(0, 0, 600,800));
    
    Texture textureShip;
    textureShip.loadFromFile("assets/player.png");

    Sprite playerShip;
    playerShip.setTexture(textureShip);
    playerShip.setPosition(600 / 2.0f , 700);
    float playerSpeed = 5;
    bool leftArrowPressed = false, rightArrowPressed = false, upArrowPressed = false, downArrowPressed = false;

    while (window.isOpen())
    {
        /* USER INPUT */
        Event event;

        while(window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case Keyboard::Escape:
                    window.close();
                    break;

                    case Keyboard::Left:
                    leftArrowPressed = true;
                    break;

                    case Keyboard::Right:
                    rightArrowPressed = true;
                    break;

                    case Keyboard::Up:
                    upArrowPressed = true;
                    break;

                    case Keyboard::Down:
                    downArrowPressed = true;
                    break;

                }
            }
            
            if(event.type == Event::KeyReleased)
            {
                switch(event.key.code)
                {
                    case Keyboard::Left:
                    leftArrowPressed = false;
                    break;

                    case Keyboard::Right:
                    rightArrowPressed = false;
                    break;

                    case Keyboard::Up:
                    upArrowPressed = false;
                    break;                    

                    case Keyboard::Down:
                    downArrowPressed = false;
                    break;
                }
            }
        }

        if(leftArrowPressed)
        {
            playerShip.move(Vector2f(-playerSpeed, 0));
        }
        if(rightArrowPressed)
        {
            playerShip.move(Vector2f(playerSpeed, 0));
        }
        if(upArrowPressed)
        {
            playerShip.move(Vector2f(0, -playerSpeed));
        }
        if(downArrowPressed)
        {
            playerShip.move(Vector2f(0, playerSpeed));
        }

        //handle out of bounds

        if(playerShip.getPosition().x > 525)
        {
            playerShip.setPosition(525, playerShip.getPosition().y);
        }

        if(playerShip.getPosition().x < -20)
        {
            playerShip.setPosition(-20,playerShip.getPosition().y);
        }

        if(playerShip.getPosition().y < 0) {
            playerShip.setPosition(playerShip.getPosition().x, 0);
        }
        
        if(playerShip.getPosition().y > 725) {
            playerShip.setPosition(playerShip.getPosition().x, 725);
        }

        window.clear();

        //rendering
        window.draw(spriteBackground);
        window.draw(playerShip);

        window.display();
    }
    return 0;
}