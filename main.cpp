#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Player.hpp"

using namespace sf;

struct Bullet {
    int x, y, dy;
};

int main() {
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
    float player_bullet_timer = 0.0f, delay = 0.2f, time = 0.0f;
    Clock clock;
    std::vector<Bullet> bullets;

    while (window.isOpen()) {
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        player_bullet_timer += time;

        Event event;
        while(window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        if(Keyboard::isKeyPressed(Keyboard::Right)) player.x += player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Left))  player.x -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Up))    player.y -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Down))  player.y += player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        player.handleSprite();

        if(Keyboard::isKeyPressed(Keyboard::Space) && delay < player_bullet_timer) {
            int x = player.x, y = player.y;
            Bullet bullet;
            bullet.x = x; bullet.y = y, bullet.dy = player_bullet_speed;
            std::cout << "PLAYER Y: " << player.y << "\t" << "BULLET Y: " << bullet.y << std::endl;
            bullets.push_back(bullet);
            player_bullet_timer = 0;
            std::cout << "BULLET CREATED Y POSITION: " << bullets[bullets.size() - 1].y << "\tBULLETS SIZE: " << bullets.size() << std::endl;
        }

        player.sprite.setPosition(player.x, player.y);
        window.clear();
        window.draw(sBackground);
        window.draw(player.sprite);
        
            std::vector<Bullet>::iterator i = bullets.begin();
            while(i != bullets.end()) {
                sBullet.setPosition(i->x, i->y - i->dy);
                i->y -= i->dy;
                std::cout << "BULLET POS Y: " << i->y << std::endl;
                if(i->y > 0 ) {
                    window.draw(sBullet);
                    i++;
                }
                else {
                    bullets.erase(bullets.begin());
                }
                        
            }

        window.display();
    }
    return 0;
}
