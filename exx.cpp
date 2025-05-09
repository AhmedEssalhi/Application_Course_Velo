#include <SFML/Graphics.hpp>
#include <c++/13/iostream>
#include <c++/13/vector>
#include <c++/13/random>
using namespace sf;
using namespace std;

int main() {
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

	vector<sf::Sprite> obstacles;
	random_device rd;								// Random number seed
	mt19937 gen(rd());								// Random number generator
	uniform_int_distribution<int> xDist(100, 700); // X range
	uniform_int_distribution<int> yDist(100, 500); // Y range

	sf::Sprite obstacle;
	obstacle.setScale(0.8f, 0.8f);
	float backgroundSpeed = 1.f;
	float obstacleSpeed = 1.f;

    Texture backgroundTexture1;
    Texture backgroundTexture2;
    Texture startButtonTexture;
    Texture exitButtonTexture;
    
    if (!backgroundTexture1.loadFromFile("assets/Backgrounds/1.png")) {
        return -1;
    }
    if (!backgroundTexture2.loadFromFile("assets/Backgrounds/2.png")) {
        return -1;
    }
    if (!startButtonTexture.loadFromFile("assets/pause&intro_pic/start_pic.png")) {
        return -1;
    }
    if (!exitButtonTexture.loadFromFile("assets/pause&intro_pic/exit_pic.png")) {
        return -1;
    }

    Sprite backgroundSprite(backgroundTexture1);
    Sprite backgroundSprite2(backgroundTexture2);
    Sprite startButtonSprite(startButtonTexture);
    Sprite exitButtonSprite(exitButtonTexture);

    backgroundSprite.setOrigin(backgroundSprite.getGlobalBounds().width / 2, backgroundSprite.getGlobalBounds().height / 2);
    backgroundSprite.setPosition(window.getSize().x /2, window.getSize().y /2 - 60);
    backgroundSprite2.setOrigin(backgroundSprite2.getGlobalBounds().width / 2, backgroundSprite2.getGlobalBounds().height / 2);
    backgroundSprite2.setPosition(window.getSize().x /2, window.getSize().y /2 - 60);
    startButtonSprite.setOrigin(startButtonSprite.getGlobalBounds().width / 2, startButtonSprite.getGlobalBounds().height / 2);
    startButtonSprite.setScale(.8f, .8f);
    startButtonSprite.setPosition(window.getSize().x /2, window.getSize().y /2 - 35);
    exitButtonSprite.setOrigin(exitButtonSprite.getGlobalBounds().width / 2, exitButtonSprite.getGlobalBounds().height / 2);
    exitButtonSprite.setPosition(window.getSize().x /2, window.getSize().y /2 + 155);

    bool showBackground = true; // Flag to toggle visibility
    bool isStartingGame = false;

    while (window.isOpen()) {
        sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (
                event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    showBackground = !showBackground;
                }
            }
            if (event.type == Keyboard::isKeyPressed(Keyboard::Enter))
            {
                isStartingGame = !isStartingGame;
                showBackground = !showBackground;
            }
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

		//vehiculeBoundingBox.setPosition(vehiculeSprite.getGlobalBounds().left, vehiculeSprite.getGlobalBounds().top);
		
		window.clear();

        if (showBackground && !isStartingGame) {
            window.draw(backgroundSprite); // Draw background only if enabled
        }
        else if (!showBackground && !isStartingGame)
        {
            window.draw(backgroundSprite2);
            window.draw(startButtonSprite);
            window.draw(exitButtonSprite);
        }
        else if (isStartingGame && !showBackground)
        {
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

            window.draw(gameBackgroundSprite);
            window.draw(gameBackgroundSprite2);
            window.draw(vehiculeSprite);

            for (const auto &obstacle : obstacles)
            {
                window.draw(obstacle); // Draw obstacles
            }
        }
        window.display();
    }

    return 0;
}
