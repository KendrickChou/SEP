#include <QGraphicsScene>
#include <QIcon>
#include <QTime>
#include <QtGlobal>
#include <QEvent>
#include <QPainter>
#include "GameWindow.h"
#include <ui_mainwindow.h>
#include <QHBoxLayout>
#include <QStyleOptionGraphicsItem>

/*-----------------------public function------------------*/

const int MAP_GRID_NUM = 40;
const int MAP_GRID_SIZE = 20;

GameWindow::GameWindow(QWidget *parent)
    :QDialog(parent)
{
    Game_Scene = new QGraphicsScene(this);
    Game_Scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
    Game_View = new QGraphicsView(Game_Scene,this);
    Clock_Timer = new QTimer;
    Game_Scene->setSceneRect(-400,-400,800,800);
    Item_Snake = new QGraphicsPathItem;
    Item_Snake->setBrush(QBrush(QColor(Qt::black)));

    creat_Map();
    creat_Wall();
    set_Food();
    set_Snake();

    Game_Scene->addItem(Item_Food);
    Game_Scene->addItem(Item_Snake);

    QHBoxLayout* main_Layout = new QHBoxLayout;
    main_Layout->addWidget(Game_View);
    setLayout(main_Layout);
    main_Layout->setSizeConstraint(QLayout::SetFixedSize);

    Clock_Timer->setInterval(100);
    Clock_Timer->start();

    connect(Clock_Timer,SIGNAL(timeout()),this,SLOT(refresh_Scene()));
    connect(this,SIGNAL(game_over()),this,SLOT(GameOver()));
}

GameWindow::~GameWindow(){

}

void GameWindow::creat_Map(){
    for (int i = 1; i < MAP_GRID_NUM ; ++i)
    {
        QGraphicsLineItem* Raw = new QGraphicsLineItem(400, -400 + i*MAP_GRID_SIZE, -400, -400 + i*MAP_GRID_SIZE);
        QGraphicsLineItem* Column = new QGraphicsLineItem(-400 + i*MAP_GRID_SIZE, 400, -400 + i*MAP_GRID_SIZE, -400);
        Raw->setPen(QColor(255,255,240));
        Column->setPen(QColor(255,255,240));
        Game_Scene->addItem(Raw);
        Game_Scene->addItem(Column);
    }
    Game_Scene->setBackgroundBrush(QBrush(QColor(255,255,240)));
}

void GameWindow::creat_Wall(){

}

bool GameWindow::check_eat_Food(){
    QPoint head = Snake_Body.first();
    if((head.x() * MAP_GRID_SIZE) == Item_Food->pos().x() && (head.y() * MAP_GRID_SIZE) == Item_Food->pos().y()){
        this->set_Food();
        return false;
    }
    return true;
}

void GameWindow::set_Snake(){
    if(Snake_Body.isEmpty()){
        for(int i = 0;i < 3;++i){
            QPoint BodyUnit;
            BodyUnit.setX(0);
            BodyUnit.setY(i);
            Snake_Body.append(BodyUnit);
        }
    }
    else Snake_Body;

    QPainterPath path;
    for(auto i : Snake_Body){
        path.addRect(i.x() * MAP_GRID_SIZE,i.y() * MAP_GRID_SIZE,MAP_GRID_SIZE,MAP_GRID_SIZE);
    }

    Item_Snake->setPath(path);
    Item_Snake->update();
}

void GameWindow::refresh_Snake(){
    QPoint head = Snake_Body.first();
    switch (dir) {
    case left:
        head.setX(head.x() - 1);
        break;
    case right:
        head.setX(head.x() + 1);
        break;
    case up:
        head.setY(head.y() - 1);
        break;
    case down:
        head.setY(head.y() + 1);
        break;
    default:
        break;
    }

    if(Snake_Body.contains(head)){
        emit game_over();
        return;
    }

    if(check_eat_Food()){
        Snake_Body.pop_back();
    }

    Snake_Body.push_front(head);
    this->set_Snake();
}

void GameWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
        if(dir != down){
            dir = up;
        }
        break;
    case Qt::Key_A:
        if(dir != right){
            dir = left;
        }
        break;
    case Qt::Key_S:
        if(dir != up){
         dir = down;
        }
        break;
    case Qt::Key_D:
        if(dir != left){
            dir = right;
        }
        break;
    default:
        break;
    }
}
/*-----------------------SLOT function------------------*/

void GameWindow::receive_New_Game(){
    this->show();
}

void GameWindow::refresh_Scene(){
    this->refresh_Snake();
}

void GameWindow::set_Food(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int randomX = qrand() % 40 - 20;
    int randomY = qrand() % 40 - 20;
    if(Item_Food == nullptr){
        Item_Food = new QGraphicsRectItem(0,0,MAP_GRID_SIZE,MAP_GRID_SIZE);
        Item_Food->setBrush(QBrush(QColor(Qt::red)));
    }
    Item_Food->setPos(randomX * MAP_GRID_SIZE,randomY * MAP_GRID_SIZE);
}

void GameWindow::GameOver(){
    Clock_Timer->stop();
    QDialog *OverDialog = new QDialog(this);
    OverDialog->resize(200,200);
    QPushButton *cButton = new QPushButton(tr("Continue"));
    QPushButton *eButton = new QPushButton(tr("Exit"));
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->addWidget(cButton);
    btnLayout->addWidget(eButton);
    OverDialog->setLayout(btnLayout);
    OverDialog->show();
}
