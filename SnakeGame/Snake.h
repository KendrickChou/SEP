#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPoint>
#include <QTimer>
#include "Food.h"
#include <stack>
#include <queue>

const int Snake_Unit_Size = 20;
enum Move_dir{left,right,up,down};

class Snake: public QObject{
    Q_OBJECT
public:
    Move_dir dir = up;//move direction
    QGraphicsPathItem *Item_Snake;
    QList<QPoint> Snake_Body;//the coordinate of body
    QTimer* Clock;
    int life = 1;
    bool eatflag = true;
    int speed = 100;
    int score = 0;
    std::stack<Move_dir> path;//the path of eat the nearest food in AI mode
    Food *food;//the food in map
    bool AI_switch = false;//the switch of AI mode
    Snake();
    ~Snake();
    void setSnake();//draw snake
    void moveSnake();//move snake
    void check_eat(Food* food);//check whether snake eat a food
    bool check_overlap(QGraphicsRectItem* food);//check the food is in the body of snake
    void setIntetval(int speed);//set speed
    void resetSnake();//when snake eat itself, then reset the snake
    void Change_Pos(int x1,int y1,
                    int x2,int y2,
                    int x3,int y3);
    void FindPath(QPoint des);//find a path to a food
    void BFS(Move_dir **father,QPoint des);
    int cal_min_distance(QPoint head);//find the nearest food
    void stop_AI();

private slots:
    void startMove();
    void pauseMove();
    void AI();

signals:
    void game_over();
private:

};

#endif // SNAKE_H
