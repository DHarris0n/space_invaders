#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string>
#include <memory>
#include <vector>
#include "game_parameters.hpp"
#include "game_system.hpp"
#include "ship.hpp"

//main.cpp
int main();

std::vector<std::shared_ptr<Ship>> GameSystem::ships;
sf::Texture spritesheet;
sf::Sprite invader;
 //vector of shared pointers to Ships.

void GameSystem::init() {
	if (!spritesheet.loadFromFile("C:/Users/User/git/space_invaders/res/invaders_sheet.png")) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}
	/*invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));*/
	
	std::cout << "print on the standard output of the console" <<  std::endl; //end of line
	std::cerr << "print on the error output of the console" << std::endl; 

	int rows = 5;
	int columns = 11;
	const int spacing = 50;

	for (int r = 0; r < rows; r++) 
	{
		for (int c = 0; c < columns; c++)
		{
			sf::IntRect rect(sf::Vector2i(0,0), sf::Vector2i(32,32));
			sf::Vector2f pos{ 100.f + c * spacing, 100.f + r * spacing};
			std::shared_ptr<Invader> inv = std::make_shared<Invader>(rect, pos);
			inv->setTexture(spritesheet);
			ships.push_back(inv); //This is when the copy constructor is called.
		}
	}

}


void GameSystem::reset() {

}

void GameSystem::update(const float& dt) {

	for (std::shared_ptr<Ship>& s : GameSystem::ships) {
		s-> update(dt);
	}
}

void GameSystem::render(sf::RenderWindow& window) {
	window.draw(invader);
	for (const std::shared_ptr<Ship>& s : GameSystem::ships) {
		window.draw(*(s.get()));
	}
}

void GameSystem::clean() {
	//free up the memory if necessary.
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