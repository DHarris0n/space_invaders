#include <iostream>
#include "ship.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

using param = Parameters;
using gs = GameSystem;

bool Invader::direction = true;
float Invader::speed = 10.f;
float Invader::firetime = 0.0f;
float Player::firetime = 0.0f;

Ship::Ship(){}

Ship::Ship(const Ship &s) : 
  _sprite(s._sprite), _exploded(s._exploded){}

Ship::Ship(sf::IntRect ir) : sf::Sprite() {
  _sprite = ir;
  setTexture(gs::spritesheet);
  setTextureRect(_sprite);
};

void Ship::update(const float &dt) {
    if(_exploded)
      explosion_time-=dt;
    if(explosion_time <= 0)
      setPosition(-100,-100);
}
void Ship::explode() {
	setTextureRect(sf::IntRect(sf::Vector2i(param::sprite_size*4.f, param::sprite_size), sf::Vector2i(param::sprite_size, param::sprite_size)));
  Invader::speed+=param::acc;
  _exploded = true;
}
//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

bool Ship::is_exploded() const {
  return _exploded;
}

void Ship::move_down(){
  move(sf::Vector2f(0.0f, param::down));
}

Invader::Invader() : Ship() {}

Invader::Invader(const Invader &inv): Ship(inv){}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(param::sprite_size/2.f,param::sprite_size/2.f);;
    setPosition(pos);
}

void Invader::update(const float &dt) {
  Ship::update(dt);

  if(_exploded)
    return;

  firetime -= dt;

  move(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f);
    
  if ((direction && getPosition().x > param::game_width - param::sprite_size/2.f) ||
      (!direction && getPosition().x < param::sprite_size/2.f)) {
        direction = !direction;
        for (std::shared_ptr<Ship> &ship: gs::ships) {
					 ship->move_down();
        }
    }

  if (getPosition().y > param::game_height)
  {
      gs::reset();
      gs::clean();
  }
    
    if (firetime <= 0 && rand() % 100 == 0) {
      Bullet::fire(getPosition(), false);
      firetime = 4.0f + (rand() % 60);
    }

}

Player::Player() : 
  Ship(sf::IntRect(sf::Vector2i(param::sprite_size*5, param::sprite_size), 
       sf::Vector2i(param::sprite_size, param::sprite_size))){
  setOrigin(param::sprite_size/2.f, param::sprite_size/2.f);;
  setPosition(param::game_width/2.f, param::game_height 
    - static_cast<float>(param::sprite_size));
}

void Player::update(const float &dt) {
    Ship::update(dt);

    if(_exploded)
      return;

    firetime -= dt;

    //Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 
        getPosition().x > param::sprite_size/2.f) {
        move(-param::player_speed*dt,0);
    }
    //Move Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        getPosition().x < param::game_width - param::sprite_size/2.f) {
        move(param::player_speed*dt,0);
    }

    if (firetime <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      Bullet::fire(getPosition(), true);
      firetime = 0.7f;
    }
}