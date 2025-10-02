//ship.cpp
#include "ship.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"
#include <iostream>

//renaming with using holds only for the current scope (here the whole file)
using param = Parameters; //renaming the struct Parameters into param to have a more compact and readable code
using gs = GameSystem; //renaming the struct GameSystem into gs to have a more compact and readable code

bool Invader::direction;
float Invader::speed = 1.f;
float Player::speed = 400.f;

const sf::Keyboard::Key controls[2] = {
	sf::Keyboard::Left,	//Player Left
	sf::Keyboard::Right	//Player Right
};

Ship::Ship() {};

Ship::Ship(const Ship& s) :
	_sprite(s._sprite) {
}

Ship::Ship(sf::IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;


Invader::Invader() : Ship() {}
Invader::Invader(const Invader& inv) : Ship(inv) {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) 
{
	setOrigin(sf::Vector2f(16.f, 16.f));
	setPosition(pos);
}

void Ship::move_down() 
{
	if (auto ship = dynamic_cast<Invader*>(this))
	{
		move(0.0f, 32.f);
	}
}

void Invader::update(const float& dt) {
	Ship::update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f);

	if ((direction && getPosition().x > param::game_width - param::sprite_size / 2.f) ||
		(!direction && getPosition().x < param::sprite_size / 2.f)) {
		direction = !direction;
		speed *= Invader::acc;
		for (std::shared_ptr<Ship>& ship : gs::ships) 
		{
			ship->move_down();
		}
	}
}

Player::Player() : Ship(sf::IntRect(sf::Vector2i(param::sprite_size * 5, param::sprite_size), sf::Vector2i(param::sprite_size, param::sprite_size)))
{
	setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
	setPosition(param::game_width / 2.f, param::game_height - static_cast<float>(param::sprite_size));
}

Player::Player(sf::IntRect(ir), sf::Vector2f (pos)) : Ship(ir)
{
	setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
	setPosition(param::game_width / 2.f, param::game_height - static_cast<float>(param::sprite_size));
}

void Player::update(const float& dt) {
	
	Ship::update(dt);

	const float px1 = Player().getPosition().x;
	//Move left
	float P1_direction = 0.0f;
	if (sf::Keyboard::isKeyPressed(controls[0]) && px1 >= (param::sprite_size /2)) {
		P1_direction--;
		std::cerr << px1 << std::endl;
	}
	else if (px1 < (param::sprite_size / 2)) {
		P1_direction += 1000.f;
	};

	//Move Right
	if (sf::Keyboard::isKeyPressed(controls[1]) && px1 <= (param::game_width - (param::sprite_size / 2))) {
		P1_direction++;
		std::cerr << "right" << std::endl;
	}
	else if (px1 > (param::game_width - (param::sprite_size / 2))) {
		P1_direction -= 1000.f;
	};
	move(P1_direction * speed * dt, 0.f);
}