#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string>
#include <memory>
#include <vector>
#include "game_parameters.hpp"
#include "game_system.hpp"
#include "ship.hpp"

using param = Parameters;
float gw = param::game_width;
float gh = param::game_height;

//main.cpp
int main();

std::vector<std::shared_ptr<Ship>> GameSystem::ships;
std::unique_ptr<Player> GameSystem::player;
sf::Texture spritesheet;
sf::Sprite invader;
sf::Sprite player;
 //vector of shared pointers to Ships.

void GameSystem::init() {
	if (!spritesheet.loadFromFile("C:/Users/User/git/space_invaders/res/invaders_sheet.png")) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}
	/*invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));*/
	
	std::cout << "print on the standard output of the console" <<  std::endl; //end of line
	std::cerr << "print on the error output of the console" << std::endl; 

	sf::Vector2i sprite_size_vector = {param::sprite_size, param::sprite_size};

	sf::Vector2i smallAlien = {32,0};
	sf::Vector2i mediumAlien = {64,0};
	sf::Vector2i bigAlien = {96,0};

	int rows = 5;
	int columns = 11;
	const int spacing = 25;

	for (int r = 0; r < rows; r++) 
	{
		for (int c = 0; c < columns; c++)
		{
			sf::Vector2i startingPos;
			if (r < 1) 
			{
				startingPos = smallAlien;
			}
			else if (r < 3)
			{
				startingPos = mediumAlien;
			}
			else
			{
				startingPos = bigAlien;
			}
			sf::IntRect rect(startingPos, sprite_size_vector);
			sf::Vector2f pos{ 100.f + c * spacing, 100.f + r * spacing};

			std::shared_ptr<Invader> inv = std::make_shared<Invader>(rect, pos);
			inv->setTexture(spritesheet);
			ships.push_back(inv); //This is when the copy constructor is called.
		}
	}

	sf::IntRect rect(sf::Vector2i(160, 32), sf::Vector2i(32, 32));
	sf::Vector2f pos{ param::sprite_size / 2.f, param::sprite_size / 2.f };
	std::shared_ptr<Player> player = std::make_shared<Player>(rect, pos);
	player->setTexture(spritesheet);
	ships.push_back(player); //This is when the copy constructor is called.
}


void GameSystem::reset() {

	Invader::speed = 50.f;

}

void GameSystem::update(const float& dt) {

	for (std::shared_ptr<Ship>& s : GameSystem::ships) {
		s-> update(dt);
	}
}

void GameSystem::render(sf::RenderWindow& window) {
	for (const std::shared_ptr<Ship>& s : ships)
	{
		window.draw(*(s.get()));
	}
}

void GameSystem::clean() {
	for (std::shared_ptr<Ship>& ship : ships)
	{
		ship.reset();//free up the memory of this shared pointer
		ships.clear();//clear the vector to be sure we free up any memory left.
	}
}

int main() {
	//create the window
	sf::RenderWindow window(sf::VideoMode({ Parameters::game_width, Parameters::game_height }), "SPACE INVADERS");
	//initialise and load
	GameSystem::init();
	GameSystem::reset();
	while (window.isOpen()) {
		//Calculate dt
		static sf::Clock clock;
		const float dt = clock.restart().asSeconds();
		window.clear();
		GameSystem::update(dt);
		GameSystem::render(window);
		//wait for the time_step to finish before displaying the next frame.
		sf::sleep(sf::seconds(Parameters::time_step));
		//Wait for Vsync
		window.display();
	}
	//Unload and shutdown
	GameSystem::clean();
}