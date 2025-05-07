#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

// Constantes
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GROUND_HEIGHT = 100.0f;
const float GRAVITY = 0.5f;
const float JUMP_STRENGTH = -10.0f;

// Structure pour les obstacles
struct Obstacle {
    sf::RectangleShape shape;
    bool passed = false;
};

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Music musiqueFond;
    sf::SoundBuffer bufferCollision;
    sf::Sound sonCollision;
    sf::Texture joueurTexture;
    sf::Sprite joueur;
    sf::Text scoreText;
    sf::RectangleShape sol;
    sf::Text title;
    sf::Text chooseText;
    sf::Sprite bikePreviewSprite;
    std::vector<std::string> bikeTextures;
    int selectedBike;
    bool inMenu;
    bool isPaused;
    int score;
    float velocityY;
    bool isJumping;
    std::vector<Obstacle> obstacles;
    sf::Clock obstacleClock;
    void handleEvents();
    void update();
    void render();
    void togglePause();
};

#endif
