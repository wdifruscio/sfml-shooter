#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

int main()
{
    VideoMode vm(1920,1080);
    RenderWindow window(vm,"Game Boilerplate");
    window.setFramerateLimit(60);

    //instantiate textures

    Texture textureBackground;
    textureBackground.loadFromFile("assets/purple.png");
    textureBackground.setRepeated(true);

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setTextureRect(IntRect(0, 0, 1920, 1080));
    
    Texture textureShip;
    textureShip.loadFromFile("assets/player.png");

    Sprite playerShip;
    playerShip.setTexture(textureShip);
    playerShip.setPosition(1920 / 2.0f , 900);
    float playerSpeed = 2;

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
                }
            }
        }

        if(leftArrowPressed)
        {
            playerShip.move(Vector2f(-playerSpeed, 0));
        }
        else if(rightArrowPressed)
        {
            playerShip.move(Vector2f(playerSpeed, 0));
        }


        window.clear();

        //rendering
        window.draw(spriteBackground);
        window.draw(playerShip);

        window.display();
    }
    return 0;
}