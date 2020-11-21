#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <QtWidgets>
#include <deque>
#include "SnakeUnit.h"

class SnakeUnit;

class Snake:public QWidget{
private:
    int length = 1;
    bool alive = true;
    int speed;
    int score = 0;
    enum direction{Up,Down,Left,Right};
    direction dir = direction::Right;
public:
    std::deque<SnakeUnit *> Body;
    QPainter *p;
    Snake();
    void DrawSnake();
    void Eat();
    void keyPressEvent(QKeyEvent *event) override;
    int GetLength();
    void move(direction dir);
};

#endif // SNAKE_H
