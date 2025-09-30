//ship.cpp
#include "ship.hpp"

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
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(sf::Vector2f(16.f, 16.f));;
	setPosition(pos);
}

void Invader::update(const float& dt) {
	Ship::update(dt);
}