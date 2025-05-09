#include <SFML/Graphics.hpp>
#include <c++/13/random>
#include <c++/13/vector>
#include <c++/13/iostream>
using namespace sf;
using namespace std;

int main()
{
	Clock clock;
	float generateTime = 2.f;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Random Obstacles");

	// Load the texture
	sf::Texture gameBackgroundTexture;
	if (!gameBackgroundTexture.loadFromFile("assets/roads/road4.png"))
	{
		return -1; // Error handling
	}

	// Create a sprite and apply the texture
	sf::Sprite gameBackgroundSprite;
	sf::Sprite gameBackgroundSprite2;
	gameBackgroundSprite.setTexture(gameBackgroundTexture);
	gameBackgroundSprite2.setTexture(gameBackgroundTexture);

	gameBackgroundSprite.setPosition(0, 0);
	gameBackgroundSprite2.setPosition(0, -gameBackgroundSprite.getGlobalBounds().height);

	sf::Texture vehiculeTexture;
	if (!vehiculeTexture.loadFromFile("assets/cars/car1.png"))
	{
		return -1; // Error handling
	}

	// Create a sprite and apply the texture
	Sprite vehiculeSprite;
	FloatRect vehiculeBounds;
	//vehiculeBounds = vehiculeSprite.getGlobalBounds();
	//vehiculeBounds.width = .35f;
	//vehiculeBounds.height = .4f;
	vehiculeSprite.setTexture(vehiculeTexture);
	vehiculeBounds = vehiculeSprite.getGlobalBounds();
	vehiculeSprite.setPosition(550, 400);
	vehiculeSprite.setScale(
		vehiculeSprite.getScale().x * 0.8f,
		vehiculeSprite.getScale().y * 0.8f
	);


	// Optionally scale to fit the window
	gameBackgroundSprite.setScale(
		window.getSize().x / gameBackgroundSprite.getGlobalBounds().width,
		window.getSize().y / gameBackgroundSprite.getGlobalBounds().height);
	gameBackgroundSprite2.setScale(
		window.getSize().x / gameBackgroundSprite2.getGlobalBounds().width,
		window.getSize().y / gameBackgroundSprite2.getGlobalBounds().height);
	// Load texture (replace "obstacle.png" with your actual image)
	sf::Texture obstacleTexture;
	if (!obstacleTexture.loadFromFile("assets/obstacles/obs2.png"))
	{
		return -1;
	}

	std::vector<sf::Sprite> obstacles;
	std::random_device rd;								// Random number seed
	std::mt19937 gen(rd());								// Random number generator
	std::uniform_int_distribution<int> xDist(100, 700); // X range
	std::uniform_int_distribution<int> yDist(100, 500); // Y range

	sf::Sprite obstacle;
	obstacle.setScale(0.8f, 0.8f);
	float backgroundSpeed = 1.f;
	float obstacleSpeed = 1.f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (
                event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape
            ))
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > generateTime)
		{
			obstacle.setTexture(obstacleTexture);
			obstacle.setPosition(xDist(gen), -50.f);
			obstacles.push_back(obstacle);
			clock.restart();
		}
		gameBackgroundSprite.move(0, backgroundSpeed);
        gameBackgroundSprite2.move(0, backgroundSpeed);

        // When the first sprite moves out of view, reset its position
        if (gameBackgroundSprite.getPosition().y >= window.getSize().y) {
            gameBackgroundSprite.setPosition(0, gameBackgroundSprite2.getPosition().y - gameBackgroundSprite.getGlobalBounds().height);
        }

        // When the second sprite moves out of view, reset its position
        if (gameBackgroundSprite2.getPosition().y >= window.getSize().y) {
            gameBackgroundSprite2.setPosition(0, gameBackgroundSprite.getPosition().y - gameBackgroundSprite2.getGlobalBounds().height);
        }
		if (Keyboard::isKeyPressed(Keyboard::Right))
			vehiculeSprite.move(.8f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			vehiculeSprite.move(-.8f, 0.f);

		for (auto& obstacle : obstacles)
		{
			obstacle.move(0, obstacleSpeed);
			if (obstacle.getGlobalBounds().intersects(vehiculeSprite.getGlobalBounds()))
			{
				cout << "Game Over !, You lose" << endl;
				//window.close();
				return 0;
			}
		}
		obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                                       [](const sf::Sprite& obs) { return obs.getPosition().y > 600; }),
                        obstacles.end());
		//vehiculeBoundingBox.setPosition(vehiculeSprite.getGlobalBounds().left, vehiculeSprite.getGlobalBounds().top);
		
		window.clear();
		window.draw(gameBackgroundSprite);
		window.draw(gameBackgroundSprite2);
		window.draw(vehiculeSprite);

		for (const auto &obstacle : obstacles)
		{
			window.draw(obstacle); // Draw obstacles
		}
		window.display();
	}

	return 0;
}
