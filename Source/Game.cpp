#include "Game.h"

Game::Game() : 
    window(sf::VideoMode(1000, 700), "Pixel Car Game"), 
    player(
        window.getSize().x / 2,
        window.getSize().y - 100, 2.f), 
        road("assets/road/road.png", 2.f) 
{
    score = 0;
    obstacleSpawnTime = 1.5f;

    state = GameState::MainMenu;
    if (!backgroundTexture.loadFromFile("assets/backgrounds/1.png")) {
        std::cerr << ("Failed to load background texture") << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, -120);

    if (!backgroundMusic.openFromFile("assets/audio/musique_fond.ogg")) {
        std::cerr << ("Failed to load background music!") << std::endl; ;
    }
    backgroundMusic.setLoop(true); // Loop the music
    backgroundMusic.setVolume(50); // Adjust volume
    backgroundMusic.play();

    if (!font.loadFromFile("assets/font/font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOrigin(
        scoreText.getGlobalBounds().width / 2,
        scoreText.getGlobalBounds().height / 2
    );
    scoreText.setPosition(
        100, //- scoreText.getGlobalBounds().width / 2, 
        20
    );
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
        )
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                if (state == GameState::MainMenu || state == GameState::GameOver)
                    resetGame();
                else if (state == GameState::Paused)
                    changeState(GameState::Playing);
            } else if (event.key.code == sf::Keyboard::P && state == GameState::Playing) {
                changeState(GameState::Paused);
            } else if (event.key.code == sf::Keyboard::P && state == GameState::Paused) {
                changeState(GameState::Playing);
            } else if (event.key.code == sf::Keyboard::Escape && state == GameState::About) {
                changeState(GameState::MainMenu);
            } else if (event.key.code == sf::Keyboard::M && (state == GameState::GameOver || state == GameState::Paused)) {
                changeState(GameState::MainMenu);
            }
            else if(state == GameState::MainMenu && event.key.code == sf::Keyboard::A)
                changeState(GameState::About);
        }
    }
}

void Game::update() {
    if (state == GameState::Playing) {
        road.update();
        player.update();
        score += 1;
        //player.draw(window);

        if (obstacleClock.getElapsedTime().asSeconds() > obstacleSpawnTime) {
            obstacles.push_back(Obstacle("assets/obstacle/rock.png", rand() % 700, -50, .5f));
            obstacleClock.restart();
        }

        for (auto& obstacle : obstacles) {
            hearts = 3;
            obstacle.update();
            if (obstacle.checkCollision(player.getBounds()))
                changeState(GameState::GameOver);
        }
    }
}

void Game::render() {
    window.clear();

    if (state == GameState::MainMenu) {
        backgroundSprite.setTexture(backgroundTexture);
        window.draw(backgroundSprite);
    } else if (state == GameState::Playing) {
        road.draw(window);
        player.draw(window);
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        for (auto& obstacle : obstacles)
            obstacle.draw(window);
    } else if (state == GameState::Paused) {
        backgroundSprite.setTexture(backgroundTexture);
        window.draw(backgroundSprite);
    } else if (state == GameState::GameOver) {
        backgroundSprite.setTexture(backgroundTexture);
        window.draw(backgroundSprite);
    } else if (state == GameState::About){
        backgroundSprite.setTexture(backgroundTexture);
        window.draw(backgroundSprite);
    }

    window.display();
}

void Game::changeState(GameState newState) {
    state = newState;

    if (state == GameState::MainMenu) {
        backgroundTexture.loadFromFile("assets/backgrounds/1.png");
    } else if (state == GameState::GameOver) {
        backgroundTexture.loadFromFile("assets/backgrounds/3.png");
    } else if (state == GameState::Paused) {
        backgroundTexture.loadFromFile("assets/backgrounds/2.png");
    } else if (state == GameState::About) {
        backgroundTexture.loadFromFile("assets/backgrounds/4.png");
    }
}

void Game::resetGame() {
    obstacles.clear();
    player = Car(
        window.getSize().x / 2,
        window.getSize().y - 100, 2.f);
    obstacleClock.restart();
    changeState(GameState::Playing);
    score = 0;
}