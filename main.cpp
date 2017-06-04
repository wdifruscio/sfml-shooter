#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Player.hpp"

using namespace sf;

struct Bullet {
    int x, y, dy;
};

std::vector<Bullet> bullets;

int main()
{
    VideoMode vm(600,800);
    RenderWindow window(vm,"Game Boilerplate");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("assets/purple.png");
    t2.loadFromFile("assets/bullet.png");
    t3.loadFromFile("assets/player.png");

    t1.setRepeated(true);

    Sprite sBackground(t1), sBullet(t2);
    sBackground.setTextureRect(IntRect(0, 0, 600,800));
    Player player(t3, 300, 700, 5);

    int player_bullet_speed = 10;
    Event event;
    while (window.isOpen())
    {
        while(window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        if(Keyboard::isKeyPressed(Keyboard::Right)) player.x += player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Left))  player.x -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Up))    player.y -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Down))  player.y += player.speed;
        player.handleSprite();

        if(Keyboard::isKeyPressed(Keyboard::Space))
        {
            int x = player.x, y = player.y;
            Bullet bullet;
            bullet.x = x; bullet.y = y, bullet.dy = player_bullet_speed;
            bullets.push_back(bullet);
            std::cout << "BULLET CREATED Y POSITION: " << bullets[0].y << std::endl;
        }

        player.sprite.setPosition(player.x, player.y);
        window.clear();
        window.draw(sBackground);
        window.draw(player.sprite);

        for(unsigned i = 0; i > bullets.size(); i++) {
            sBullet.setPosition(bullets[i].x, bullets[i].y - bullets[i].dy);
            window.draw(sBullet);
            std::cout << "BULLET POS Y: " << bullets[i].y << std::endl;
            if(bullets[i].y < 0 || bullets[i].y)
                bullets.erase(bullets.begin() + i);
        }

        window.display();
    }
    return 0;
}
