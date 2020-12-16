#include "Snake.h"
#include <QPainter>

void Snake::setSnake(){
    QPainterPath path;
    for(auto i : Snake_Body){
        path.addRect(i.x() * Snake_Unit_Size,i.y() * Snake_Unit_Size,Snake_Unit_Size,Snake_Unit_Size);
    }

    Item_Snake->setPath(path);
    Item_Snake->update();
}

Snake::Snake(){
    Clock = new QTimer;
    this->setIntetval(100);
    Item_Snake = new QGraphicsPathItem;
    Item_Snake->setBrush(QBrush(QColor(Qt::black)));
        for(int i = 0;i < 3;++i){
            QPoint BodyUnit;
            BodyUnit.setX(0);
            BodyUnit.setY(i);
            Snake_Body.append(BodyUnit);
        }
    setSnake();
}

Snake::~Snake(){

}

void Snake::moveSnake(){
    QPoint head = Snake_Body.first();
    switch (dir) {
    case left:
        head.setX(head.x() - 1);
        if(head.x() < -20) {
            emit game_over();
            return;
        }
        break;
    case right:
        head.setX(head.x() + 1);
        if(head.x() > 20) {
            emit game_over();
            return;
        }
        break;
    case up:
        head.setY(head.y() - 1);
        if(head.y() < -20) {
            emit game_over();
            return;
        }
        break;
    case down:
        head.setY(head.y() + 1);
        if(head.y() > 20){
            emit game_over();
            return;
        }
        break;
    default:
        break;
    }

    if(Snake_Body.contains(head)){
        emit game_over();
        return;
    }

    if(eatflag){
        Snake_Body.pop_back();
    }
    else{
        eatflag = true;
    }

    Snake_Body.push_front(head);
    this->setSnake();
}

void Snake::check_eat(Food* food){
    QPoint head = this->Snake_Body.first();
    for(int i = 0; i < 3; ++i){
        if(((head.x() * Snake_Unit_Size) == food->Item_Food[i]->pos().x()) && ((head.y() * Snake_Unit_Size) == food->Item_Food[i]->pos().y())){
            PROPERTY p = food->Food_Property[i];
            if(p == sd) {
                if(speed < 130) speed += 30;
                this->setIntetval(speed);
            }
            if(p == su) {
                if(speed > 40)
                speed -= 30;
                this->setIntetval(speed);
            }
            food->setFood(i);// remember to make sure the food is not in the snake body
            food->setFoodColor(i);
            eatflag = false;
        }
    }
    eatflag = true;
}

void Snake::setIntetval(int speed){
    Clock->setInterval(speed);
    Clock->start();
}

