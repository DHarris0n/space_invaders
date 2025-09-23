#include <SFML/Graphics.hpp>

// Establishing controls
const sf::Keyboard::Key controls[4] = {
	sf::Keyboard::A,	//Player1 UP
	sf::Keyboard::Z,	//Player1 Down
	sf::Keyboard::Up,	//Player2 UP
	sf::Keyboard::Down	//Player2 Down
};

//Parameters
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f;	//60fps

sf::Vector2f ball_velocity;
bool is_player1_serving = true;
const float initial_velocity_x = 100.f;	// Horizontal velocity
const float initial_velocity_y = 60.f;	// Vertical velocity
const float velocity_multiplier = 1.1f; //how much the ball will speed up everytime it hits a paddle. Here, 10% every time.

//Objects of the game
sf::CircleShape ball;
sf::RectangleShape paddles[2];

void init() {
	// initialise all the objects needed for the game.
	for (sf::RectangleShape& p : paddles) {
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}
	//set size and origin of ball
	ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius, ballRadius);//should be half the ball width and height
}

void reset() {

	//reset all the objects

	//reset paddle conditions
	paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
	paddles[1].setPosition(gameWidth - (paddleOffsetWall + paddleSize.x / 2.f), gameHeight / 2.f);

	//reset ball position
	ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);

	//reset ball velocity
	ball_velocity = { (is_player1_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y };

}

void update(float dt) {

	// check paddle collision for paddle 1
	const float py1 = paddles[0].getPosition().y;

	// check paddle collision for player 2
	const float py2 = paddles[1].getPosition().y;


	// Handle paddle 1 movement
	float P1_direction = 0.0f;
	if (sf::Keyboard::isKeyPressed(controls[0]) && py1 >= 50) {
		P1_direction--;
	}
	else if (py1 < 50) {
		P1_direction += 1.f;
	}

	if (sf::Keyboard::isKeyPressed(controls[1]) && py1 <= (gameHeight - 50)) {
		P1_direction++;
	}
	else if (py1 > (gameHeight - 50)) {
		P1_direction -= 1.f;
	}

	paddles[0].move(sf::Vector2f(0.f, P1_direction * paddleSpeed * dt));

	// Handle paddle 2 movement
	float P2_direction = 0.0f;
	if (sf::Keyboard::isKeyPressed(controls[2]) && py2 >= 50) {
		P2_direction--;
	}
	else if (py2 < 50) {
		P2_direction += 1.f;
	}

	if (sf::Keyboard::isKeyPressed(controls[3]) && py2 <= (gameHeight - 50)) {
		P2_direction++;
	}
	else if (py2 > (gameHeight - 50)) {
		P2_direction -= 1.f;
	}

	paddles[1].move(sf::Vector2f(0.f, P2_direction * paddleSpeed * dt));

	//ball move script
	ball.move(ball_velocity * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	if (by > gameHeight) { //bottom wall
		// bottom wall
		ball_velocity.x *= velocity_multiplier;
		ball_velocity.y *= -velocity_multiplier;
		ball.move(sf::Vector2f(0.f, -10.f));
	}
	else if (by < 0) { //top wall
		// top wall
		ball_velocity.x *= velocity_multiplier;
		ball_velocity.y *= -velocity_multiplier;
		ball.move(sf::Vector2f(0.f, 10.f));
	}
	else if (bx > gameWidth) {
		// right wall
		ball_velocity.x *= -velocity_multiplier;
		ball_velocity.y *= velocity_multiplier;
		ball.move(sf::Vector2f(-10.f, 0.f));
		reset();
	}
	else if (bx < 0) {
		// left wall
		ball_velocity.x *= -velocity_multiplier;
		ball_velocity.y *= velocity_multiplier;
		ball.move(sf::Vector2f(10.f, 0.f));
		reset();
	}
	else if (
		//ball is inline or behind paddle AND
		bx < paddleSize.x + paddleOffsetWall &&
		//ball is below top edge of paddle AND
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
		{
			// bounce off left paddle
			ball_velocity.x *= -velocity_multiplier;
			ball_velocity.y *= velocity_multiplier;
			ball.move(sf::Vector2f(10.f, 0.f));

		}
	else if (
		//ball is inline or behind paddle AND
		bx > (gameWidth - (paddleOffsetWall + paddleSize.x)) &&
		//ball is below top edge of paddle AND
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
		{
			// bounce off right paddle
			ball_velocity.x *= -velocity_multiplier;
			ball_velocity.y *= velocity_multiplier;
			ball.move(sf::Vector2f(-10.f, 0.f));

		}
}

void render(sf::RenderWindow& window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

void clean() {
	//free up the memory if necessary.
}

int main() {
	//create the window
	sf::RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "PONG");
	//initialise and load
	init();
	reset();
	while (window.isOpen()) {
		//Calculate dt
		static sf::Clock clock;
		const float dt = clock.restart().asSeconds();
		window.clear();
		update(dt);
		render(window);
		//wait for the time_step to finish before displaying the next frame.
		sf::sleep(sf::seconds(time_step));
		//Wait for Vsync
		window.display();
	}
	//Unload and shutdown
	clean();
}