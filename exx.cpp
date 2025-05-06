#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>  // Pour l'enregistrement du High Score
#include <SFML/Audio.hpp> // Pour la musique et les effets sonores

class Velo {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float vitesseY;
    bool enSaut;
    float vitesseX;
    float vitesseMaxX;
    const float vitesseMaxLimite;
    float acceleration;
    float deceleration;
    const float vitesseMin;

public:
    Velo(const std::string& chemin_image)
        : vitesseY(0.f), enSaut(false), vitesseX(0.f),
          vitesseMaxX(4.f), vitesseMaxLimite(20.f),
          acceleration(0.4f), deceleration(0.1f), vitesseMin(2.f) {

        if (!texture.loadFromFile(chemin_image)) {
            std::cerr << "Erreur : impossible de charger l'image du vélo !" << std::endl;
        } else {
            sprite.setTexture(texture);
            sprite.setScale(0.2f, 0.2f);
        }
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void afficher(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void deplacerDroite() {
        if (vitesseMaxX < vitesseMaxLimite)
            vitesseMaxX += acceleration;
        vitesseX = vitesseMaxX;
    }

    void freiner() {
        vitesseMaxX -= 0.5f;
        if (vitesseMaxX < vitesseMin)
            vitesseMaxX = vitesseMin;
        vitesseX = -1.f;
    }

    void arreterDeplacement() {
        vitesseX = 0.f;
        if (vitesseMaxX > vitesseMin) {
            vitesseMaxX -= deceleration;
            if (vitesseMaxX < vitesseMin)
                vitesseMaxX = vitesseMin;
        }
    }

    void sauter() {
        if (!enSaut) {
            vitesseY = -8.f;
            enSaut = true;
        }
    }

    void appliquerGravite(float gravite, float solY) {
        vitesseY += gravite;
        sprite.move(vitesseX, vitesseY);

        if (sprite.getPosition().y + sprite.getGlobalBounds().height >= solY) {
            sprite.setPosition(sprite.getPosition().x, solY - sprite.getGlobalBounds().height);
            vitesseY = 0.f;
            enSaut = false;
        }
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    float getVitesseX() {
        return vitesseX;
    }

    void resetVitesse() {
        vitesseX = 0.f;
        vitesseMaxX = 4.f;
    }
};

struct Obstacle {
    sf::RectangleShape forme;
    bool estFosse;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de Vélo SFML");
    window.setFramerateLimit(60);

    // ----------------- Musique de fond -----------------
    sf::Music musiqueFond;
    if (!musiqueFond.openFromFile("musique_fond.ogg")) {
        std::cerr << "Erreur : Impossible de charger la musique de fond !" << std::endl;
        return -1;
    }
    musiqueFond.setLoop(true);  // Répéter la musique en boucle
    musiqueFond.play();

    // ----------------- Effets sonores -----------------
    sf::SoundBuffer bufferCollision;
    if (!bufferCollision.loadFromFile("collision.wav")) {
        std::cerr << "Erreur : Impossible de charger l'effet sonore de collision !" << std::endl;
        return -1;
    }
    sf::Sound sonCollision;
    sonCollision.setBuffer(bufferCollision);

    /*sf::SoundBuffer bufferSaut;
    if (!bufferSaut.loadFromFile("saut.wav")) {
        std::cerr << "Erreur : Impossible de charger l'effet sonore de saut !" << std::endl;
        return -1;
    }
    sf::Sound sonSaut;
    sonSaut.setBuffer(bufferSaut);*/

    float solY = 500.f;

    // ---------------- Menu ----------------
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        return -1;
    }

    sf::Text startText("Start", font, 40);
    sf::Text quitText("Quitter", font, 40);
    startText.setPosition(300, 200);
    quitText.setPosition(300, 300);
    startText.setFillColor(sf::Color::Green);
    quitText.setFillColor(sf::Color::Red);

    bool inMenu = true;
    while (inMenu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mouse = sf::Mouse::getPosition(window);
                if (startText.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    inMenu = false;
                }
                if (quitText.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    window.close();
                    return 0;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(startText);
        window.draw(quitText);
        window.display();
    }

    // ----------------- JEU -----------------
    Velo monVelo("velo1.png");
    monVelo.setPosition(100.f, solY - 80.f);

    sf::RectangleShape sol(sf::Vector2f(5000.f, 100.f));
    sol.setFillColor(sf::Color(100, 250, 50));
    sol.setPosition(0.f, solY);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<Obstacle> obstaclesEtFosses;
    float departX = 800.f;
    int totalElements = 20;

    for (int i = 0; i < totalElements; ++i) {
        bool estFosse = (std::rand() % 3 == 0); // 1/3 fossé
        float x = departX + std::rand() % 300 + 200;

        Obstacle obs;
        obs.estFosse = estFosse;
        if (estFosse) {
            obs.forme.setSize(sf::Vector2f(100.f, 10.f));
            obs.forme.setFillColor(sf::Color(50, 50, 255));  // bleu
            obs.forme.setPosition(x, solY - 10.f);  // position correcte pour collision
        } else {
            obs.forme.setSize(sf::Vector2f(40.f, 60.f));
            obs.forme.setFillColor(sf::Color::Red);  // rouge
            obs.forme.setPosition(x, solY - 60.f);
        }

        obstaclesEtFosses.push_back(obs);
        departX += std::rand() % 400 + 300;
    }

    // Ligne d'arrivée
    sf::RectangleShape ligneArrivee(sf::Vector2f(10.f, 100.f));
    ligneArrivee.setFillColor(sf::Color::Yellow);
    ligneArrivee.setPosition(2500.f, solY - 100.f);

    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(20.f, 20.f);

    sf::Clock clock;
    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(20.f, 50.f);

    // High score
    int highScore = 0;
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> highScore;
        highScoreFile.close();
    }

    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(20);
    highScoreText.setFillColor(sf::Color::Black);
    highScoreText.setPosition(600.f, 20.f);

    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameOver) {
            // Gestion des touches
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                monVelo.deplacerDroite();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                monVelo.freiner();
            } else {
                monVelo.arreterDeplacement();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                monVelo.sauter();
                //sonSaut.play(); // Effet sonore de saut
            }

            monVelo.appliquerGravite(0.4f, solY);

            // Gestion des obstacles et points
            for (auto& obs : obstaclesEtFosses) {
                if (monVelo.getSprite().getGlobalBounds().intersects(obs.forme.getGlobalBounds())) {
                    if (obs.estFosse) {
                        std::cout << "💥 Vous êtes tombé dans un fossé !" << std::endl;
                        score = 0;
                        monVelo.resetVitesse();
                        monVelo.setPosition(100.f, solY - 80.f);
                        sonCollision.play(); // Effet sonore de collision
                    } else {
                        std::cout << "⚡ Collision avec un obstacle rouge !" << std::endl;
                        score -= 5;
                        sonCollision.play(); // Effet sonore de collision
                    }
                    break;
                }

                // Attribution de points pour les obstacles
                if (monVelo.getSprite().getPosition().x > obs.forme.getPosition().x + obs.forme.getSize().x) {
                    if (obs.estFosse) {
                        score += 1;
                    } else {
                        score += 3;
                    }
                }
            }

            // Mise à jour du score en fonction du temps
            score += 1;  // Augmenter le score d'1 point par seconde

            // Vérification du temps
            if (clock.getElapsedTime().asSeconds() >= 70.f) {
                gameOver = true;
            }

            // Vérification de la ligne d'arrivée
            if (monVelo.getSprite().getPosition().x > ligneArrivee.getPosition().x) {
                gameOver = true;
                float tempsArrivee = clock.getElapsedTime().asSeconds();
                std::cout << "Vous avez franchi la ligne d'arrivée en " << tempsArrivee << " secondes!" << std::endl;
                if (score > highScore) {
                    highScore = score;
                    std::ofstream highScoreFile("highscore.txt");
                    highScoreFile << highScore;
                    highScoreFile.close();
                }
            }

            // Affichage des informations
            std::stringstream scoreStream;
            scoreStream << "Score: " << score;
            scoreText.setString(scoreStream.str());

            int tempsEcoule = static_cast<int>(clock.getElapsedTime().asSeconds());
            std::stringstream timerStream;
            timerStream << "Temps: " << tempsEcoule << "s";
            timerText.setString(timerStream.str());

            std::stringstream highScoreStream;
            highScoreStream << "High Score: " << highScore;
            highScoreText.setString(highScoreStream.str());

            // Affichage de la caméra
            sf::View camera(sf::FloatRect(monVelo.getSprite().getPosition().x - 400.f, 0.f, 800.f, 600.f));
            window.setView(camera);

            // Affichage
            window.clear(sf::Color::White);
            window.draw(sol);
            for (auto& obs : obstaclesEtFosses)
                window.draw(obs.forme);
            window.draw(ligneArrivee);
            monVelo.afficher(window);

            window.setView(window.getDefaultView());
            window.draw(scoreText);
            window.draw(timerText);
            window.draw(highScoreText);

            window.display();
        } else {
            // Affichage du Game Over
            sf::Text gameOverText("Game Over", font, 40);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(300.f, 200.f);
            window.clear(sf::Color::White);
            window.draw(gameOverText);

            sf::Text replayText("Appuyez sur Y pour rejouer ou Q pour quitter", font, 20);
            replayText.setPosition(200.f, 300.f);
            window.draw(replayText);

            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                gameOver = false;
                score = 0;
                clock.restart();
                monVelo.setPosition(100.f, solY - 80.f);
                for (auto& obs : obstaclesEtFosses) {
                    obs.forme.setPosition(obs.forme.getPosition().x + 5000.f, obs.forme.getPosition().y);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                window.close();
            }
        }
    }

    return 0;
}



