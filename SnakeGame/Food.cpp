#include "Food.h"
#include <QtGlobal>
#include <QPainter>
#include <QTime>


const int FOOD_SIZE = 20;

void Food::setFood(int i){
        int randomX = qrand() % 40 - 20;
        int randomY = qrand() % 40 - 20;
        int randomProperty = qrand() % 20;
        switch (randomProperty) {
        case 0:
        case 1:
            Food_Property[i] = sd;
            break;
        case 2:
        case 3:
            Food_Property[i] = su;
            break;
        case 4:
            Food_Property[i] = el;
            break;
        case 5:
            Food_Property[i] = ds;
            break;
        default:
            Food_Property[i] = n;
            break;
        }//set the probability of different food by merge case
        Item_Food[i]->setPos(randomX * FOOD_SIZE,randomY * FOOD_SIZE);
}

void Food::setFoodColor(int i){
    Item_Food[i]->setPen(Qt::NoPen);
    switch (Food_Property[i]) {
    case n:
        Item_Food[i]->setBrush(QBrush(QColor::fromRgb(130,130,130)));
        break;
    case su:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::red)));
        break;
    case sd:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::blue)));
        break;
    case el:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::green)));
        break;
    case ds:
        Item_Food[i]->setBrush(QBrush(QColor(Qt::white)));
    }
}// normal:grey speedup:red speeddown:blue extralife:green doublescore:white

Food::Food(){
    for(int i = 0; i < 3; ++i){
        QGraphicsRectItem* food = new QGraphicsRectItem (0,0,FOOD_SIZE,FOOD_SIZE);
        Item_Food.push_back(food);
        PROPERTY p;
        Food_Property.push_back(p);
    }//initial food, 3 food in the map
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 3; ++i){
        this->setFood(i);
        this->setFoodColor(i);
    }
}
