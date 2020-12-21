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
    //initial snake
    Clock = new QTimer;
    Item_Snake = new QGraphicsPathItem;
    Item_Snake->setPen(Qt::NoPen);
    Item_Snake->setBrush(QBrush(QColor::fromRgb(102,205,170)));
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
    if(AI_switch){
        //in AI mode
        if(path.empty()){
            this->AI();
        }
        dir = path.top();
        path.pop();
    }
    QPoint head = Snake_Body.first();
    switch (dir) {
    case left:
        head.setX(head.x() - 1);
        //if touch the wall, GG
        if(head.x() < -20) {
            emit game_over();
            return;
        }
        break;
    case right:
        head.setX(head.x() + 1);
        if(head.x() >= 20) {
            emit game_over();
            return;
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
            emit game_over();
            return;
        }
        break;
    default:
        break;
    }

    //if eat itself
    if(Snake_Body.contains(head)){
        if(--life < 1){
            emit game_over();
            return;
        }
        else resetSnake();
    }

    //if eat a food
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
    //check eat a food and make the effect of food works
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
            if(p == ds){
                score *= 2;
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
    Snake_Body.clear();
    QPoint BodyUnit;
    BodyUnit.setX(0);
    BodyUnit.setY(1);
    Snake_Body.append(BodyUnit);
    this->moveSnake();
}

void Snake::Change_Pos(int x1, int y1, int x2, int y2, int x3, int y3){
        Snake_Body[0].setX(x1);
        Snake_Body[0].setY(y1);
        Snake_Body[1].setX(x2);
        Snake_Body[1].setY(y2);
        Snake_Body[2].setX(x3);
        Snake_Body[2].setY(y3);
        setSnake();
}

void Snake::AI(){
    //get the nearest food
    int i = cal_min_distance(Snake_Body.first());
    QPoint des(food->Item_Food[i]->x() / 20,food->Item_Food[i]->y() / 20);

    //find path to the food
    FindPath(des);
    AI_switch = true;
}

void Snake::BFS(Move_dir **father,QPoint des){
    std::queue<QPoint> q;
    int visit[40][40] = {0};
    int offsetX[4] = {0,0,-1,1};//up down left right
    int offsetY[4] = {-1,1,0,0};
    des.setX(des.x() + 20);//-20 <= des.x <= 20 in primary
    des.setY(des.y() + 20);
    for(int i = 0;i < Snake_Body.size();++i){
        visit[Snake_Body[i].x() + 20][Snake_Body[i].y() + 20] = 1;
    }
    QPoint head(Snake_Body.first().x() + 20,Snake_Body.first().y() + 20);
    q.push(head);
    while(!q.empty()){
        QPoint point = q.front();
        q.pop();
        if(point == des){
            return;
        }
        for(int i = 0;i < 4;++i){
            int nX = point.x() + offsetX[i];
            int nY = point.y() + offsetY[i];
            if(nX >= 40 || nX < 0 || nY >= 40 || nY < 0 || visit[nX][nY] == 1)
                continue;
            QPoint newPoint(nX,nY);
            visit[nX][nY] = 1;
            q.push(newPoint);

            //record the move direction
            switch (i) {
            case 0:
                father[nX][nY] = up;
                break;
            case 1:
                father[nX][nY] = down;
                break;
            case 2:
                father[nX][nY] = left;
                break;
            case 3:
                father[nX][nY] = right;
                break;
            }
        }
    }
}

void Snake::FindPath(QPoint des){
    Move_dir **father;
    father = new Move_dir *[40];
    for(int i = 0;i < 40;++i){
        father[i] = new Move_dir [40];
    }
    BFS(father,des);

    //get the path form father[40][40]
    /*method:start from the destination,continuelly find the pre-coordinate
     * until reach head,then we get a path from head to food*/
    QPoint pre(des.x() + 20,des.y() + 20);
    QPoint head(Snake_Body.first().x() + 20, Snake_Body.first().y() + 20);
    while(1){
        path.push(father[pre.x()][pre.y()]);
        switch (father[pre.x()][pre.y()]) {
        case up:
            pre.setY(pre.y() + 1);
            break;
        case down:
            pre.setY(pre.y() - 1);
            break;
        case left:
            pre.setX(pre.x() + 1);
            break;
        case right:
            pre.setX(pre.x() - 1);
            break;
        }
        if(pre == head){
            break;
        }
    }
    for(int i = 0;i < 40; ++i){
        delete [] father[i];
    }
    delete [] father;
}

int Snake::cal_min_distance(QPoint head){
    int min = 10000000;
    int res;
    for(int i = 0;i < 3;++i){
        int x = (food->Item_Food[i]->x() / 20) - head.x();
        int y = (food->Item_Food[i]->y() / 20) - head.y();
        if((x * x + y * y) < min){
            min = x * x + y * y;
            res = i;
        }
    }
    return res;
}

void Snake::stop_AI(){
    AI_switch = false;
    while(!path.empty()){
        path.pop();
    }
}
