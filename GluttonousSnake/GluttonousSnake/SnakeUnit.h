#ifndef SNAKEUNIT_H
#define SNAKEUNIT_H

#include <iostream>
#include <string>
#include "Snake.h"

class SnakeUnit{
private:
    int X = -1,Y = -1;
public:
    SnakeUnit();
    SnakeUnit(const int x, const int y);
    int GetX();
    int GetY();
    void moveUnit(const int x,const int y);
    void DrawUnit(QPainter *p);
};

#endif // SNAKEUNIT_H
