#include <iostream>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

using param = Parameters;

std::vector<std::shared_ptr<Ship>> GameSystem::ships;
sf::Texture GameSystem::spritesheet;

void GameSystem::init() {
  if (!spritesheet.loadFromFile("../../../../resources/img/invaders_sheet.png")) {
    std::cerr << "Failed to load spritesheet!" << std::endl;
  }
  reset();
}

void GameSystem::reset(){
  Bullet::init();
  std::shared_ptr<Ship> player = std::make_shared<Player>();
  ships.push_back(player);
  for (int r = 0; r < param::rows; ++r) {
    sf::IntRect rect(sf::Vector2i(32*r, 0), sf::Vector2i(32, 32));
    for (int c = 0; c < param::columns; ++c) {
        sf::Vector2f position(c*(param::sprite_size+param::spacing)+param::sprite_size/2.f,
                              r*(param::sprite_size+param::spacing)+param::sprite_size/2.f);
        std::shared_ptr<Invader> inv = std::make_shared<Invader>(rect, position);
        inv->speed = 10.f;
        ships.push_back(inv);
    }
  }
}

void GameSystem::clean(){
  for(std::shared_ptr<Ship> &ship: ships)
    ship.reset();
  ships.clear();
}

void GameSystem::update(const float &dt){
  if(ships[0]->is_exploded()){
    clean();
    reset();
  }
  for (std::shared_ptr<Ship> &s : ships) 
    s->update(dt);
  Bullet::update(dt);
}

void GameSystem::render(sf::RenderWindow &window){
    for (const std::shared_ptr<Ship> &s : ships) 
      window.draw(*(s.get()));
    Bullet::render(window);
}
