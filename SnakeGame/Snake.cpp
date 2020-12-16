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
            if(--life < 1){
                emit game_over();
                return;
            }
            else resetSnake();
        }
        break;
    case right:
        head.setX(head.x() + 1);
        if(head.x() >= 20) {
            if(--life < 1){
                emit game_over();
                return;
            }
            else resetSnake();
        }
        break;
    case up:
        head.setY(head.y() - 1);
        if(head.y() < -20) {
            if(--life < 1){
                emit game_over();
                return;
            }
            else resetSnake();
        }
        break;
    case down:
        head.setY(head.y() + 1);
        if(head.y() >= 20 ){
            if(--life < 1){
                emit game_over();
                return;
            }
            else resetSnake();
        }
        break;
    default:
        break;
    }

    if(Snake_Body.contains(head)){
        if(--life < 1){
            emit game_over();
            return;
        }
        else resetSnake();
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

bool Snake::check_overlap(QGraphicsRectItem *food){
        for(auto i : Snake_Body){
            if(i.x() * Snake_Unit_Size == food->pos().x() && (i.y() * Snake_Unit_Size) == food->pos().y()){
                return false;
            }
        }
        return true;
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
            if(p == el){
                ++life;
            }
            food->setFood(i);
            while(!check_overlap(food->Item_Food[i])){
                food->setFood(i);
            }
            food->setFoodColor(i);
            ++score;
            eatflag = false;
            return;
        }
    }
    eatflag = true;
}

void Snake::setIntetval(int speed){
    Clock->setInterval(speed);
    Clock->start();
}

void Snake::startMove(){
    setIntetval(speed);
}

void Snake::pauseMove(){
    Clock->stop();
}

void Snake::resetSnake(){
    Clock->stop();
    Snake_Body.clear();
//    for(int i = 0;i < 3;++i){
//        QPoint BodyUnit;
//        BodyUnit.setX(0);
//        BodyUnit.setY(i);
//        Snake_Body.append(BodyUnit);
//    }
    QPoint BodyUnit;
    BodyUnit.setX(0);
    BodyUnit.setY(1);
    Snake_Body.append(BodyUnit);
    setSnake();
}
