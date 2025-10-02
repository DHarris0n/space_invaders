//ship.hpp
#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
public:
	Ship();
	//Copy constructor
	Ship(const Ship& s);
	//Constructor that takes a sprite
	Ship(sf::IntRect ir);
	//Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
	virtual ~Ship() = 0;
	//Update, virtual so can be overridden, but not pure virtual
	virtual void update(const float& dt);

	void move_down();
protected:
	sf::IntRect _sprite;
	sf::Texture spritesheet;
	sf::Sprite invader;

};

class Invader : public Ship {
public:
	static bool direction;
	static float speed;

	Invader();
	Invader(const Invader& inv);
	Invader(sf::IntRect ir, sf::Vector2f pos);
	void update(const float& dt) override;

	const float acc = 1.2f;
};

class Player : public Ship {
public:
	static float speed;
	Player();
	Player(sf::IntRect ir, sf::Vector2f pos);
	void update(const float& dt) override;
};