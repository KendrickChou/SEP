#include "Food.h"
#include <QtGlobal>
#include <QPainter>
#include <QTime>


const int FOOD_SIZE = 20;

void Food::setFood(int i){
        int randomX = qrand() % 40 - 20;
        int randomY = qrand() % 40 - 20;
        int randomProperty = qrand() % 10;
        switch (randomProperty) {
        case 0:
            Food_Property[i] = el;
            break;
        case 1:
            Food_Property[i] = su;
            break;
        case 2:
            Food_Property[i] = sd;
            break;
        default:
            Food_Property[i] = n;
            break;
        }
        Item_Food[i]->setPos(randomX * FOOD_SIZE,randomY * FOOD_SIZE);
}

void Food::setFoodColor(int i){
    switch (Food_Property[i]) {
    case n:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::yellow)));
        break;
    case su:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::red)));
        break;
    case sd:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::blue)));
        break;
    case el:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::green)));
    }
}

Food::Food(){
    for(int i = 0; i < 3; ++i){
        QGraphicsRectItem* food = new QGraphicsRectItem (0,0,FOOD_SIZE,FOOD_SIZE);
        Item_Food.push_back(food);
        PROPERTY p;
        Food_Property.push_back(p);
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 3; ++i){
        this->setFood(i);
        this->setFoodColor(i);
    }
}
