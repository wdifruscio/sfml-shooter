#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(800,600);
    RenderWindow window(vm,"Game Boilerplate", Style::Titlebar);

    Texture textureBackground;
    textureBackground.loadFromFile("assets/purple.png");
    
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0,0);
    spriteBackground.setScale(3.125,2.34);

    Texture textureShip;
    textureShip.loadFromFile("assets/player.png");

    Sprite playerShip;
    playerShip.setTexture(textureShip);
    playerShip.getLocalBounds();



    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();     
        }
        window.clear();
        window.draw(spriteBackground);
        window.display();
    }
    return 0;
}