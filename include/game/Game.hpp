#ifndef GAME_HPP
#define GAME_HPP

class Game 
{
    public:
        virtual void update() = 0;
        virtual void keyPressed(int key) = 0;
        virtual void keyReleased(int key) = 0;
        virtual void onGameClosed() = 0;
        virtual int getSideMenuIndex() const = 0;

    protected:
        virtual void renderPartialBitmap(int x, int y, int xBitmap, int yBitmap, int width, int height, int bitmapWidth, int bitmapHeight, const unsigned short* bitmap);
};

#endif // GAME_HPP