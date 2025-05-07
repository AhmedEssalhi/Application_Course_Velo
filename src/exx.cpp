#include "exx.h"
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML"),
      inMenu(true), isPaused(false), score(0), velocityY(0), isJumping(false), selectedBike(0) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police.\n";
        exit(-1);
    }

    bikeTextures = {"moto1.png", "moto2.png", "velo1.png"};

    // Initialisation de la musique de fond
    if (!musiqueFond.openFromFile("musique_fond.ogg")) {
        std::cerr << "Erreur : Impossible de charger la musique de fond !\n";
    } else {
        musiqueFond.setLoop(true);
        musiqueFond.play();
    }

    // Initialisation du son de collision
    if (!bufferCollision.loadFromFile("collision.wav")) {
        std::cerr << "Erreur : Impossible de charger l'effet sonore de collision !\n";
    }
    sonCollision.setBuffer(bufferCollision);

    // Initialisation des éléments du menu
    if (!bikePreviewTexture.loadFromFile(bikeTextures[selectedBike])) {
        std::cerr << "Erreur : Impossible de charger l'image du vélo/moto.\n";
    }
    bikePreviewSprite.setTexture(bikePreviewTexture);
    bikePreviewSprite.setPosition(WINDOW_WIDTH / 2 - 100, 200);

    title.setFont(font);
    title.setString("Choisir votre véhicule");
    title.setCharacterSize(30);
    title.setPosition(WINDOW_WIDTH / 2 - 150, 50);

    chooseText.setFont(font);
    chooseText.setString("Utilisez Gauche/Droite pour choisir, Entrer pour démarrer");
    chooseText.setCharacterSize(20);
    chooseText.setPosition(WINDOW_WIDTH / 2 - 250, 500);

    // Initialisation du sol
    sol.setSize(sf::Vector2f(WINDOW_WIDTH, GROUND_HEIGHT));
    sol.setFillColor(sf::Color(50, 200, 50));
    sol.setPosition(0, WINDOW_HEIGHT - GROUND_HEIGHT);

    // Initialisation du texte du score
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        if (!isPaused) {
            update();
        }
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                togglePause();
            }

            if (inMenu) {
                if (event.key.code == sf::Keyboard::Right) {
                    selectedBike = (selectedBike + 1) % bikeTextures.size();
                    if (!bikePreviewTexture.loadFromFile(bikeTextures[selectedBike])) {
                        std::cerr << "Erreur : Impossible de charger l'image du vélo/moto.\n";
                    }
                    bikePreviewSprite.setTexture(bikePreviewTexture);
                } else if (event.key.code == sf::Keyboard::Left) {
                    selectedBike = (selectedBike - 1 + bikeTextures.size()) % bikeTextures.size();
                    if (!bikePreviewTexture.loadFromFile(bikeTextures[selectedBike])) {
                        std::cerr << "Erreur : Impossible de charger l'image du vélo/moto.\n";
                    }
                    bikePreviewSprite.setTexture(bikePreviewTexture);
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (!joueurTexture.loadFromFile(bikeTextures[selectedBike])) {
                        std::cerr << "Erreur : Impossible de charger le sprite du joueur.\n";
                        exit(-1);
                    }
                    joueur.setTexture(joueurTexture);
                    joueur.setPosition(100, WINDOW_HEIGHT - GROUND_HEIGHT - joueurTexture.getSize().y);
                    inMenu = false;
                }
            }
        }
    }
}

void Game::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        velocityY = JUMP_STRENGTH;
        isJumping = true;
    }

    velocityY += GRAVITY;
    joueur.move(0, velocityY);

    if (joueur.getPosition().y >= WINDOW_HEIGHT - GROUND_HEIGHT - joueur.getGlobalBounds().height) {
        joueur.setPosition(joueur.getPosition().x, WINDOW_HEIGHT - GROUND_HEIGHT - joueur.getGlobalBounds().height);
        isJumping = false;
    }

    if (obstacleClock.getElapsedTime().asSeconds() > 2.0f) {
        Obstacle obs;
        obs.shape.setSize(sf::Vector2f(40, 40));
        obs.shape.setFillColor(sf::Color::Red);
        obs.shape.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT - GROUND_HEIGHT - 40);
        obstacles.push_back(obs);
        obstacleClock.restart();
    }

    for (auto& obs : obstacles) {
        obs.shape.move(-5, 0);

        if (!obs.passed && obs.shape.getPosition().x + obs.shape.getSize().x < joueur.getPosition().x) {
            obs.passed = true;
            score++;
        }

        if (joueur.getGlobalBounds().intersects(obs.shape.getGlobalBounds())) {
            sonCollision.play();
            score = 0;
            obstacles.clear();
            break;
        }
    }

    scoreText.setString("Score: " + std::to_string(score));
}

void Game::render() {
    window.clear();
    
    if (isPaused) {
        sf::Text pauseText("Jeu en Pause\nAppuyez sur Échap pour reprendre", font, 30);
        pauseText.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 50);
        window.draw(pauseText);
    } else {
        window.draw(sol);
        for (auto& obs : obstacles) window.draw(obs.shape);
        window.draw(joueur);
        window.draw(scoreText);
    }

    if (inMenu) {
        window.draw(title);
        window.draw(bikePreviewSprite);
        window.draw(chooseText);
    }

    window.display();
}

void Game::
togglePause() {
    isPaused = !isPaused;
}

int main() {
    Game game;
    game.run();
    return 0;
}











    






