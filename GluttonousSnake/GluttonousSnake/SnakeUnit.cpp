#include "SnakeUnit.h"
#include <QtWidgets>

SnakeUnit::SnakeUnit(){

}

SnakeUnit::SnakeUnit(const int x, const int y){
    X = x;
    Y = y;
}

int SnakeUnit::GetX(){
    return X;
}

int SnakeUnit::GetY(){
    return Y;
}

void SnakeUnit::moveUnit(const int x, const int y){
    X = x;
    Y = y;
}

void SnakeUnit::DrawUnit(QPainter *p){
    p->setPen(Qt::NoPen);
    p->setBrush(QColor(	187,255,255));
    p->drawRect(X,Y,5,5);
}
