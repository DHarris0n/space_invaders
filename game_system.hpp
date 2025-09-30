//game_system.hpp
#include <vector>
#include <memory>
#include "ship.hpp"
struct GameSystem {

	static std::vector<std::shared_ptr<Ship>> ships; //vector of shared pointers to Ships.
		
	//game system functions
	static void init();
	static void clean();
	static void update(const float& dt);
	static void render(sf::RenderWindow& window);
	static void reset();
};