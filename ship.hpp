#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
public:
    Ship();
    //Copy constructor
    Ship(const Ship &s);
    //Constructor that takes a sprite
    Ship(sf::IntRect ir);
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Ship() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void update(const float &dt);
    virtual void explode();
    virtual void move_down();

    bool is_exploded() const;
    
    float explosion_time = 0.1f;

protected:
    sf::IntRect _sprite;
    bool _exploded = false;
};

class Invader : public Ship {
public:
    Invader();
    Invader(const Invader& inv);
    Invader(sf::IntRect ir, sf::Vector2f pos);
    void update(const float &dt) override;

    static bool direction;
    static float speed;
    static float firetime;
};

class Player : public Ship {
public:
  Player();
  void update(const float &dt) override;
  void move_down() override{}
  static float firetime;
  static constexpr int speed = 100.f;
};
