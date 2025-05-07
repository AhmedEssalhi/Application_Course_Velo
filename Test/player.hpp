#ifndef PLAYER_H
#define PLAYER_H

#include <c++/13/iostream>
#include <SFML/Graphics.hpp>
#include "coin.hpp"

class Player {
    public:
        Player(sf::Vector2f size) {
            player.setSize(size);
            player.setFillColor(sf::Color::Green);
        }
    
        void drawTo(sf::RenderWindow &window) {
            window.draw(player);
        }
    
        void move(sf::Vector2f distance) {
            player.move(distance);
        }
    
        void setPos(sf::Vector2f newPos) {
            player.setPosition(newPos);
        }
    
        int getY() {
            return player.getPosition().y;
        }
    
        bool isCollidingWithCoin(Coin *coin) {
            if (player.getGlobalBounds().intersects(coin->getGlobalBounds())) {
                return true;
            }
            return false;
        }
    private:
        sf::RectangleShape player;
};

#endif