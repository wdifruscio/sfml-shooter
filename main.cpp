#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include "Entities/Entity.hpp"
#include "Entities/Asteroid.hpp"
#include "Entities/Bullet.hpp"
#include "Entities/Player.hpp"
#include "Entities/EntityFactory.hpp"
#include "ParticleSystem.cpp"
#include "Animation.hpp"

using namespace sf;

int main() {
    ParticleSystem particles(1000);
    int gWindow_w = 1440; int gWindow_h = 900;
    VideoMode vm(gWindow_w, gWindow_h);
    RenderWindow window(vm,"Space Shooter");
    window.setFramerateLimit(60);

    Texture t2,t4, bg1, bg2, explosion;
    t2.loadFromFile("assets/bullet.png");
    bg1.loadFromFile("assets/background-stars.png");
    bg2.loadFromFile("assets/background-nebula.png");
    explosion.loadFromFile("assets/type_A.png");
    // bg3.loadFromFile("assets/starlayer3.png");

    Sprite sBullet(t2), sAsteroid(t4), sBg1(bg1), sBg2(bg2), sBg2_copy(bg2);
    FloatRect sBulletBounds = sBullet.getLocalBounds();

    float Frame = 0;
    int frames = 20;
    int animSpeed = 0.4;

    int player_bullet_speed = 10;
    float player_bullet_timer = 0.0f, delay = 0.2f, time = 0.0f, asteroid_timer = 0.0f, asteroid_delay = 0.2f, explosion_delay = 0.0f;
    float sBg2_dx = 0.1f;
    Clock clock;
    std::srand ((unsigned)std::time(NULL));
    std::vector<Animation> explosions;
    std::list<Entities::Entity*> entities;

    Entities::EntityFactory entityFactory;

    class Entities::Player::Player *player = entityFactory.GeneratePlayer();
    entities.push_back(player);

    while (window.isOpen()) {
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        player_bullet_timer += time;
        asteroid_timer += time;

        Event event;
        while(window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        if(Keyboard::isKeyPressed(Keyboard::Right))    player->handleSprite(Keyboard::Right);
        if(Keyboard::isKeyPressed(Keyboard::Left))     player->handleSprite(Keyboard::Left);
        if(Keyboard::isKeyPressed(Keyboard::Up))       player->handleSprite(Keyboard::Up);
        if(Keyboard::isKeyPressed(Keyboard::Down))     player->handleSprite(Keyboard::Down);
        if(Keyboard::isKeyPressed(Keyboard::Escape))   window.close();

        if(Keyboard::isKeyPressed(Keyboard::Space) && delay < player_bullet_timer) {
            Entities::Bullet *bullet = new Entities::Bullet();
            sf::Vector2f bulpos(player->getPosition().x, player->getSprite().getPosition().y + ( player->getSprite().getLocalBounds().height/2) - (bullet->getSprite().getLocalBounds().height / 2));
            bullet->setPosition(bulpos);
            entities.push_back(bullet);
            player_bullet_timer = 0;
        }
        if(std::rand() % 10 + 1 > 1 && asteroid_delay < asteroid_timer) {
            int x = gWindow_w, y = std::rand() % gWindow_h;
            Entities::Asteroid *asteroid = new Entities::Asteroid();
            Vector2f pos(x,y);
            Vector2f vel(rand() % 10 - 4, rand() % 8 - 4);
            asteroid->setPosition(pos);
            asteroid->setVelocity(vel);
            entities.push_back(asteroid);
            std::cout << "asteroid made.. num of entities: " << entities.size() << std::endl;
            asteroid_timer = 0;
        }
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        window.clear();

        if(sBg2.getPosition().x < -sBg2.getLocalBounds().width) sBg2.setPosition(0, 0);
        if(sBg2_copy.getPosition().x < 0) sBg2_copy.setPosition(sBg2.getLocalBounds().width, 0);

        sBg2.move(-sBg2_dx, 0);
        sBg2_copy.move(-sBg2_dx, 0);

        sf::Vector2f thrusterPos(player->getPosition().x + 10, player->getPosition().y + (player->getSprite().getLocalBounds().height / 2));
        particles.setEmitter(thrusterPos);
        window.draw(particles);

        for(auto a : entities) {
            a->update();
            a->draw(window);
        }


        window.draw(sBg1);
        window.draw(sBg2);
        window.draw(sBg2_copy);
        
        // window.draw(player->getSprite());
        // update it

        // for(unsigned i = 0;  i < bullets.size(); i++) {
        //     for(unsigned j = 0; j < asteroids.size(); j++ ) {
        //         if(bullets[i].x > asteroids[j].x && bullets[i].x < asteroids[j].x + sAsteroidBounds.width
        //             && bullets[i].y > asteroids[j].y && bullets[i].y < asteroids[j].y + sAsteroidBounds.height) {
        //             std::cout << "HIT!" << " ASTEROIDS: "<< asteroids.size() << std::endl;
        //             Animation sExplosion(explosion ,0,0,50,50,20,0.75,0.75);
        //             sExplosion.sprite.setPosition(bullets[i].x,bullets[i].y);
        //             explosions.push_back(sExplosion);
        //             asteroids.erase(asteroids.begin() + j);
        //             bullets.erase(bullets.begin() + i);
        //         }
        //     }
        // }

        for(unsigned i = 0; i < explosions.size(); i++) {
            if(!explosions[i].isEnd()) {
                explosions[i].update();
                explosions[i].draw(window);
            }
            else {
                explosions.erase(explosions.begin() + i);
            }
        }

        // for(unsigned i = 0;  i < bullets.size(); i++) {
        //     sBullet.setPosition(bullets[i].x, bullets[i].y - bullets[i].dx);
        //     // std::cout << "BULLET POS Y: " << bullets[i].y << std::endl;
        //     if(bullets[i].x > gWindow_w) {
        //         bullets.erase(bullets.begin()+i);
        //         break;
        //     }
        //     else {
        //         bullets[i].x += bullets[i].dx;
        //     }
        //     window.draw(sBullet);
        // }

        // for(unsigned i = 0;  i < asteroids.size(); i++) {
        //     sAsteroid.setPosition(asteroids[i].x, asteroids[i].y);
        //     // std::cout << "BULLET POS Y: " << asteroids[i].y << std::endl;
        //     if(asteroids[i].y > gWindow_h || asteroids[i].y < 0 || asteroids[i].x < 0) {
        //         asteroids.erase(asteroids.begin()+i);
        //         break;
        //     }
        //     else {
        //         asteroids[i].y -= 1 * asteroids[i].dy;
        //         asteroids[i].x += 1 * asteroids[i].dx;
        //     }
        //         // if(asteroids[i].x > player->getSprite().getPosition().x && asteroids[i].x < player->getSprite().getPosition().x + player->getSprite().getLocalBounds().width
        //         //     && asteroids[i].y > player.spirte.getPosition().y && asteroids[i].y < player.spirte.getPosition().y + player->getSprite().getLocalBounds().height) {
        //         //     std::cout << "PLAYER HIT!" << std::endl;
        //         // }
        //     window.draw(sAsteroid);
        // }
        window.display();
    }
    return 0;
}
