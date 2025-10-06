#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ship.hpp"

struct GameSystem{
    static std::vector<std::shared_ptr<Ship>> ships;
    static sf::Texture spritesheet;

    static void init();
    static void reset();
    static void clean();
    static void update(const float &dt);
    static void render(sf::RenderWindow &window);
};