#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

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

    void changerImage(const std::string& chemin_image) {
        if (!texture.loadFromFile(chemin_image)) {
            std::cerr << "Erreur : Impossible de charger l'image du vélo choisi." << std::endl;
        } else {
            sprite.setTexture(texture);
        }
    }
};

struct Obstacle {
    sf::RectangleShape forme;
    bool estFosse;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de Vélo SFML");
    window.setFramerateLimit(60);

    float solY = 500.f;

    // Liste des vélos disponibles
    std::vector<std::string> velosDisponibles = {"moto1.png", "moto2.png", "velo1.png"};
    std::string veloChoisi = velosDisponibles[0];  // Par défaut

    // Police
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        return -1;
    }

    // ----------- Menu principal -----------
    sf::Text startText("Start", font, 40);
    sf::Text chooseText("Choisir", font, 40);
    sf::Text quitText("Quitter", font, 40);
    startText.setPosition(300, 150);
    chooseText.setPosition(300, 250);
    quitText.setPosition(300, 350);
    startText.setFillColor(sf::Color::Green);
    chooseText.setFillColor(sf::Color::Blue);
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
                if (chooseText.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    // ----------- Menu de sélection de vélo -----------
                    sf::RenderWindow selectionWindow(sf::VideoMode(800, 300), "Choisir un Vélo");
                    std::vector<sf::Texture> textures(velosDisponibles.size());
                    std::vector<sf::Sprite> sprites(velosDisponibles.size());

                    for (size_t i = 0; i < velosDisponibles.size(); ++i) {
                        if (!textures[i].loadFromFile(velosDisponibles[i])) {
                            std::cerr << "Erreur : Impossible de charger " << velosDisponibles[i] << std::endl;
                            continue;
                        }
                        sprites[i].setTexture(textures[i]);
                        sprites[i].setScale(0.3f, 0.3f);
                        sprites[i].setPosition(100 + i * 200, 100);
                    }

                    while (selectionWindow.isOpen()) {
                        sf::Event event2;
                        while (selectionWindow.pollEvent(event2)) {
                            if (event2.type == sf::Event::Closed)
                                selectionWindow.close();
                            if (event2.type == sf::Event::MouseButtonPressed) {
                                auto mouse = sf::Mouse::getPosition(selectionWindow);
                                for (size_t i = 0; i < sprites.size(); ++i) {
                                    if (sprites[i].getGlobalBounds().contains(mouse.x, mouse.y)) {
                                        veloChoisi = velosDisponibles[i];
                                        selectionWindow.close();
                                        break;
                                    }
                                }
                            }
                        }
                        selectionWindow.clear(sf::Color::White);
                        for (const auto& s : sprites)
                            selectionWindow.draw(s);
                        selectionWindow.display();
                    }
                }
                if (quitText.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    window.close();
                    return 0;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(startText);
        window.draw(chooseText);
        window.draw(quitText);
        window.display();
    }

    // ----------- Création du vélo avec l'image choisie -----------
    Velo monVelo(veloChoisi);
    monVelo.setPosition(100.f, solY - 80.f);

    // ----------- Sol, obstacles, ligne d'arrivée -----------
    sf::RectangleShape sol(sf::Vector2f(5000.f, 100.f));
    sol.setFillColor(sf::Color(100, 250, 50));
    sol.setPosition(0.f, solY);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<Obstacle> obstaclesEtFosses;
    float departX = 800.f;
    int totalElements = 20;

    for (int i = 0; i < totalElements; ++i) {
        bool estFosse = (std::rand() % 3 == 0);
        float x = departX + std::rand() % 300 + 200;

        Obstacle obs;
        obs.estFosse = estFosse;
        if (estFosse) {
            obs.forme.setSize(sf::Vector2f(100.f, 10.f));
            obs.forme.setFillColor(sf::Color(50, 50, 255));
            obs.forme.setPosition(x, solY - 10.f);
        } else {
            obs.forme.setSize(sf::Vector2f(40.f, 60.f));
            obs.forme.setFillColor(sf::Color::Red);
            obs.forme.setPosition(x, solY - 60.f);
        }

        obstaclesEtFosses.push_back(obs);
        departX += std::rand() % 400 + 300;
    }

    sf::RectangleShape ligneArrivee(sf::Vector2f(10.f, 100.f));
    ligneArrivee.setFillColor(sf::Color::Yellow);
    ligneArrivee.setPosition(2500.f, solY - 100.f);

    int score = 0;
    int highScore = 0;
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> highScore;
        highScoreFile.close();
    }

    sf::Text scoreText("Score: 0", font, 20);
    scoreText.setPosition(20.f, 20.f);
    scoreText.setFillColor(sf::Color::Black);

    sf::Text highScoreText("High Score: 0", font, 20);
    highScoreText.setPosition(600.f, 20.f);
    highScoreText.setFillColor(sf::Color::Black);

    sf::Clock clock;
    sf::Text timerText("Temps: 0s", font, 20);
    timerText.setPosition(20.f, 50.f);
    timerText.setFillColor(sf::Color::Black);

    // ----------- Sons (collision uniquement) -----------
    sf::SoundBuffer bufferCollision;
    bufferCollision.loadFromFile("collision.wav");
    sf::Sound sonCollision;
    sonCollision.setBuffer(bufferCollision);

    // sf::SoundBuffer bufferSaut;
    // bufferSaut.loadFromFile("saut.wav");
    // sf::Sound sonSaut;
    // sonSaut.setBuffer(bufferSaut);

    bool gameOver = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                monVelo.deplacerDroite();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                monVelo.freiner();
            else
                monVelo.arreterDeplacement();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                monVelo.sauter();
                // sonSaut.play();  // Le son de saut est désactivé pour l'instant
            }

            monVelo.appliquerGravite(0.4f, solY);

            for (auto& obs : obstaclesEtFosses) {
                if (monVelo.getSprite().getGlobalBounds().intersects(obs.forme.getGlobalBounds())) {
                    if (obs.estFosse) {
                        score = 0;
                        monVelo.resetVitesse();
                        monVelo.setPosition(100.f, solY - 80.f);
                        sonCollision.play();
                    } else {
                        score -= 5;
                        sonCollision.play();
                    }
                    break;
                }

                if (monVelo.getSprite().getPosition().x > obs.forme.getPosition().x + obs.forme.getSize().x) {
                    score += obs.estFosse ? 1 : 3;
                }
            }

            score += 1;

            if (clock.getElapsedTime().asSeconds() >= 70.f)
                gameOver = true;

            if (monVelo.getSprite().getPosition().x > ligneArrivee.getPosition().x) {
                gameOver = true;
                if (score > highScore) {
                    highScore = score;
                    std::ofstream out("highscore.txt");
                    out << highScore;
                }
            }

            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());

            std::stringstream timerStream;
            timerStream << "Temps: " << static_cast<int>(clock.getElapsedTime().asSeconds()) << "s";
            timerText.setString(timerStream.str());

            std::stringstream hs;
            hs << "High Score: " << highScore;
            highScoreText.setString(hs.str());

            sf::View camera(sf::FloatRect(monVelo.getSprite().getPosition().x - 400.f, 0.f, 800.f, 600.f));
            window.setView(camera);

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
            sf::Text gameOverText("Game Over", font, 40);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(300.f, 200.f);

            sf::Text replayText("Appuyez sur Y pour rejouer ou Q pour quitter", font, 20);
            replayText.setPosition(200.f, 300.f);

            window.clear(sf::Color::White);
            window.draw(gameOverText);
            window.draw(replayText);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                gameOver = false;
                score = 0;
                clock.restart();
                monVelo.setPosition(100.f, solY - 80.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                window.close();
            }
        }
    }

    return 0;
}




