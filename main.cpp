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
    int playerShipX = playerShip.getPosition().x;
    int playerShipY = playerShip.getPosition().y;
    float playerSpeed = 1.5;

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();     
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            playerShipX += -1 * playerSpeed;
            playerShip.setPosition(playerShipX, playerShipY);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            playerShipX += 1 * playerSpeed;
            playerShip.setPosition(playerShipX, playerShipY);
        }

        window.clear();

        //rendering
        window.draw(spriteBackground);
        window.draw(playerShip);

        window.display();
    }
    return 0;
}