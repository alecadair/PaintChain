#ifndef DIGITALWALL_H
#define DIGITALWALL_H

#include <QObject>

//class Pixel {
//public:
//    uint x_loc;
//    uint y_loc;
//    uint color;
//    Pixel();
//    uint get_color();
//    uint set_color();


//};

class DigitalWall
{
private:
    uint x_loc;
    uint y_loc;
public:
    DigitalWall();
    void get_pixel(uint x_loc, uint y_loc, uint color);
};


#endif // DIGITALWALL_H
