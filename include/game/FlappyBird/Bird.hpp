#ifndef Bird_HPP
#define Bird_HPP
#include <Arduino.h>
#include <vector>
#include <TFT_eSPI.h>
class Bird {
private:
    int yPos;
    int xPos;
    int xSize;
    int ySize;
    float speed;
    float gravity;
    float maxFallSpeed;
    float jumpHeight;
    int animation;
    int currentSpeed;
    
public:

    Bird(float gravity, float maxFallSpeed, float jumpHeight);
    void update(float deltaTime);
    void renderFlappyBird();
    std::vector<unsigned short> extractPartialBackground(int xPartialBitmap, int yPartialBitmap, int widthPartialBitmap, int heightPartialBitmap);
    void gameOverAnimation();
    void jump();
    int getYPos();
    int getXPos();
    int getYSize();
    int getXSize();
};
#endif