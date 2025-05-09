#include "Game.h"

Game::Game() : 
    window(sf::VideoMode(1000, 700), "Pixel Car Game"), 
    player(
        window.getSize().x / 2,
        window.getSize().y - 100, 1.f), 
        road("assets/road/road.png", 1.0f) 
{
    state = GameState::MainMenu; // Start in main menu
    obstacleSpawnTime = 2.0f;

    if (!backgroundTexture.loadFromFile("assets/backgrounds/menu.png")) {
        throw std::runtime_error("Failed to load background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, -100);
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
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
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

        if (obstacleClock.getElapsedTime().asSeconds() > obstacleSpawnTime) {
            obstacles.push_back(Obstacle("assets/obstacle/rock.png", rand() % 700, -50, 1.0f));
            obstacleClock.restart();
        }

        for (auto& obstacle : obstacles) {
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
    }

    window.display();
}

void Game::changeState(GameState newState) {
    state = newState;

    if (state == GameState::MainMenu) {
        backgroundTexture.loadFromFile("assets/backgrounds/menu.png");
    } else if (state == GameState::GameOver) {
        backgroundTexture.loadFromFile("assets/backgrounds/gameover.png");
    } else if (state == GameState::Paused) {
        backgroundTexture.loadFromFile("assets/backgrounds/paused.png");
    } else if (state == GameState::About) {
        backgroundTexture.loadFromFile("assets/backgrounds/about.png");
    }
}

void Game::resetGame() {
    obstacles.clear();
    player = Car(
        window.getSize().x / 2,
        window.getSize().y - 100, 5.f);
    obstacleClock.restart();
    changeState(GameState::Playing);
}