#include <iostream>
#include "Snake.h"
#include "SnakeUnit.h"

Snake::Snake(){
    SnakeUnit *head;
    Body.push_back(head);
}

int Snake::GetLength(){
    return this->length;
}

void Snake::DrawSnake(){
    for(int i = 0;i < length; ++i){
        Body[i]->DrawUnit(p);
    }
}

void Snake::move(direction dir){
    switch (dir) {
    case Up:
    {
        SnakeUnit *nUnit =  new SnakeUnit(Body[0]->GetX(),Body[0]->GetY() - 1);
        Body.push_front(nUnit);
        Body.pop_back();
        break;
    }
    case Left:
    {
        SnakeUnit *nUnit =  new SnakeUnit(Body[0]->GetX() - 1,Body[0]->GetY());
        Body.push_front(nUnit);
        Body.pop_back();
        break;
    }
    case Down:
    {
        SnakeUnit *nUnit =  new SnakeUnit(Body[0]->GetX(),Body[0]->GetY() + 1);
        Body.push_front(nUnit);
        Body.pop_back();
        break;
    }
    case Right:
    {
        SnakeUnit *nUnit =  new SnakeUnit(Body[0]->GetX() + 1,Body[0]->GetY());
        Body.push_front(nUnit);
        Body.pop_back();
        break;
    }
    }
}

void Snake::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    switch(key){
    case Qt::Key_W:
        dir = Up;
        break;
    case Qt::Key_A:
        dir = Left;
        break;
    case Qt::Key_D:
        dir = Right;
        break;
    case Qt::Key_S:
        dir = Down;
        break;
    }
}

