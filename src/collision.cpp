#include "game.hpp"

void detectCollision(RectangleShape &rect, RectangleShape &rect2, int &collisionCounter)
{
    FloatRect r1 = rect.getGlobalBounds();
    FloatRect r2 = rect2.getGlobalBounds();
    if (r1.intersects(r2))
    {
        float overlapX = std::min(r1.left + r1.width - r2.left, 
            r2.left + r2.width - r1.left);
        
        rect.move(overlapX, 0.f);
        collisionCounter++;
    }
}