#include "game.hpp"
#include "player.hpp"
#include "coin.hpp"

int main() {
	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 345, (sf::VideoMode::getDesktopMode().height / 2) - 450);

	window.create(sf::VideoMode(900, 900), "SFML Gravity", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	//Player Object:
	Player player({ 40, 40 });
	player.setPos({ 50, 700 });

	//Coin Objects:
	std::vector<Coin*> coinVec;
	Coin coin1({ 20, 20 });
	Coin coin2({ 20, 20 });
	coinVec.push_back(&coin1);
	coinVec.push_back(&coin2);

	coin1.setPos({ 50, 600 });
	coin2.setPos({ 100, 600 });

	//Score Objects:

	int score = 0;

	sf::Font arial;
	arial.loadFromFile("../assets/fonts/gameoverfont.ttf");

	std::ostringstream ssScore;
	ssScore << "Score: " << score;

	sf::Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition({ 10, 10 });
	lblScore.setFont(arial);
	lblScore.setString(ssScore.str());
	bool isJumping = false;

	//Gravity Variables:
	/*
	const int groundHeight = 700;
	const float gravitySpeed = 0.3;
	*/

	//Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		const float moveSpeed = 0.2;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player.move({ 0, -moveSpeed });
			isJumping = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move({ moveSpeed, 0 });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move({ -moveSpeed, 0 });
		}

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();

			case sf::Event::KeyReleased:
				isJumping = false;
			}
		}

		//Gravity Logic:
		/*
		if (player.getY() < groundHeight && isJumping == false) {
			player.move({ 0, gravitySpeed });
		}*/

		//Coin Logic:
		for (int i = 0; i < coinVec.size(); i++) {
			if (player.isCollidingWithCoin(coinVec[i])) {
				coinVec[i]->setPos({ 422234, 423432 });
				score++;
				ssScore.str("");
				ssScore << "Score " << score;
				lblScore.setString(ssScore.str());
			}
		}

		window.clear();
		coin1.drawTo(window);
		window.draw(lblScore);
		coin2.drawTo(window);
		player.drawTo(window);
		window.display();
	}
}