#include <iostream>
#include "bullet.hpp"
#include "game_parameters.hpp"
#include "game_system.hpp"

using gs = GameSystem;
using param = Parameters;

unsigned char Bullet::_bulletPointer;
Bullet Bullet::_bullets[256];

Bullet::Bullet(){}

void Bullet::update(const float &dt){
    for(int i = 0; i < 256; i++)
        _bullets[i]._update(dt);
}

void Bullet::render(sf::RenderWindow &window){
    for(int i = 0; i < 256; i++)
        window.draw(_bullets[i]);
}

void Bullet::fire(const sf::Vector2f &pos, const bool mode){
    Bullet &bullet = _bullets[++_bulletPointer];
    if(mode)
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size,param::sprite_size),
            sf::Vector2i(param::sprite_size,param::sprite_size)));
    else
        bullet.setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size*2,param::sprite_size),
            sf::Vector2i(param::sprite_size,param::sprite_size)));
    bullet.setPosition(pos);
    bullet._mode = mode;
}
void Bullet::init(){
    for(int i = 0; i < 256; i++){
        _bullets[i].setTexture(gs::spritesheet);
        _bullets[i].setOrigin(param::sprite_size/2.f,param::sprite_size/2.f);
        _bullets[i].setPosition(-100,-100);   
    }
}

void Bullet::_update(const float &dt) {
    if (getPosition().y < -param::sprite_size || getPosition().y > param::game_height + param::sprite_size) {
        //off screen - do nothing
        return;
    } else {
        move(sf::Vector2f(0, dt * param::bullet_speed * (_mode ? -1.0f : 1.0f)));
        const sf::FloatRect boundingBox = getGlobalBounds();
        std::shared_ptr<Ship> &player = gs::ships[0]; //we know that the first ship is the player
        for (std::shared_ptr<Ship> &s : gs::ships) {
            if (_mode && s == player) {
                //player bullets don't collide with player
                continue;
            }
            if (!_mode && s != player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() && 
                s->getGlobalBounds().intersects(boundingBox)) {
                  //Explode the ship
                  s->explode();
                  //warp bullet off-screen
				  setPosition(sf::Vector2f(-100, -100));
                  return;
            }
        }
    }
}