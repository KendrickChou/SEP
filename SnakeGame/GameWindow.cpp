#include <QGraphicsScene>
#include <QIcon>
#include <QTime>
#include <QEvent>
#include <QPainter>
#include "GameWindow.h"
#include <ui_GameWindow.h>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QBitmap>
#include <string>

/*-----------------------public function------------------*/

const int MAP_GRID_NUM = 40;
const int MAP_GRID_SIZE = 20;

GameWindow::GameWindow(QWidget *parent)
    :QDialog(parent),
      ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Snake");

    Game_Scene = new QGraphicsScene(this);
    Game_Scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
    ui->Game_View->setScene(Game_Scene);

    mySnake = new Snake;
    myFood = new Food;
    creat_Map();
    creat_Wall();
    set_Snake();

    Game_Scene->addItem(mySnake->Item_Snake);
    Game_Scene->addItem(myFood->Item_Food[0]);
    Game_Scene->addItem(myFood->Item_Food[1]);
    Game_Scene->addItem(myFood->Item_Food[2]);
    Game_Scene->update();


    connect(ui->startButton,SIGNAL(clicked(bool)),mySnake,SLOT(startMove()));
    connect(ui->pauseButton,SIGNAL(clicked(bool)),mySnake,SLOT(pauseMove()));
    connect(mySnake->Clock,SIGNAL(timeout()),this,SLOT(refresh_Scene()));
    connect(mySnake,&Snake::game_over,this,&GameWindow::GameOver);
}

GameWindow::~GameWindow(){
    delete ui;
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
    QGraphicsRectItem* upWall_GraphicsRectItem = new QGraphicsRectItem(-403, -403, MAP_GRID_NUM*MAP_GRID_SIZE + 6, 3);
        QGraphicsRectItem* downWall_GraphicsRectItem = new QGraphicsRectItem(-403, 400, MAP_GRID_NUM*MAP_GRID_SIZE + 6, 3);
        QGraphicsRectItem* leftWall_GraphicsRectItem = new QGraphicsRectItem(-403, -400, 3, MAP_GRID_NUM*MAP_GRID_SIZE);
        QGraphicsRectItem* rightWall_GraphicsRectItem = new QGraphicsRectItem(400, -400, 3, MAP_GRID_NUM*MAP_GRID_SIZE);
        Game_Scene->addItem(upWall_GraphicsRectItem);
        Game_Scene->addItem(downWall_GraphicsRectItem);
        Game_Scene->addItem(leftWall_GraphicsRectItem);
        Game_Scene->addItem(rightWall_GraphicsRectItem);

        upWall_GraphicsRectItem->setBrush(QColor(Qt::black));
        downWall_GraphicsRectItem->setBrush(QColor(Qt::black));
        leftWall_GraphicsRectItem->setBrush(QColor(Qt::black));
        rightWall_GraphicsRectItem->setBrush(QColor(Qt::black));
}

void GameWindow::set_Snake(){
    mySnake->setSnake();
}

void GameWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
        if(mySnake->dir != down){
            mySnake->dir = up;
        }
        break;
    case Qt::Key_A:
        if(mySnake->dir != right){
            mySnake->dir = left;
        }
        break;
    case Qt::Key_S:
        if(mySnake->dir != up){
         mySnake->dir = down;
        }
        break;
    case Qt::Key_D:
        if(mySnake->dir != left){
            mySnake->dir = right;
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
    QString Scorestring  = "Score: ";
    QString ScoreNum = QString::number(mySnake->score);
    Scorestring.append(ScoreNum);
    ui->Scoreboard->setText(Scorestring);

    QString Lifestring = "Life: ";
    QString LifeNum = QString::number(mySnake->life);
    Lifestring.append(LifeNum);
    ui->Lifeboard->setText(Lifestring);

    QString Speedstring = "Speed: ";
    QString Speedlevel;
    switch (mySnake->speed) {
    case 100:
        Speedlevel = "Normal";
        break;
    case 130:
        Speedlevel = "SLOW";
        break;
    case 70:
        Speedlevel = "High";
        break;
    case 40:
        Speedlevel = "SHigh";
        break;
    }
    Speedstring.append(Speedlevel);
    ui->Speedboard->setText(Speedstring);


    mySnake->moveSnake();
    mySnake->check_eat(myFood);
    Game_Scene->update();
}

void GameWindow::GameOver(){
    mySnake->Clock->stop();
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
    connect(cButton,SIGNAL(clicked()),this,SLOT(NewGame()));
    connect(eButton,SIGNAL(clicked()),this,SLOT(close()));
}

void GameWindow::NewGame(){
    this->hide();
    emit newgame();
}

