#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPoint>
#include <QTimer>
#include "Food.h"

const int Snake_Unit_Size = 20;
enum Move_dir{left,right,up,down};

class Snake: public QObject{
    Q_OBJECT
public:
    Move_dir dir = left;
    QGraphicsPathItem *Item_Snake;
    QList<QPoint> Snake_Body;
    QTimer* Clock;
    int life = 1;
    bool eatflag = true;
    int speed = 100;
    int score = 0;
    Snake();
    ~Snake();
    void setSnake();
    void moveSnake();
    void check_eat(Food* food);
    bool check_overlap(QGraphicsRectItem* food);
    void setIntetval(int speed);
    void resetSnake();

private slots:
    void startMove();
    void pauseMove();
signals:
    void game_over();
private:

};

#endif // SNAKE_H
