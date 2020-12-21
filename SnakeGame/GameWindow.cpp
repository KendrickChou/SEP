#include <QGraphicsScene>
#include <QIcon>
#include <QTime>
#include <QEvent>
#include <QPainter>
#include "GameWindow.h"
#include <ui_GameWindow.h>
#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QBitmap>
#include <string>

/*-----------------------public function------------------*/

const int MAP_GRID_NUM = 40;//there are 40 * 40 grids in map
const int MAP_GRID_SIZE = 20;//every grid is 20 * 20


GameWindow::GameWindow(QWidget *parent)
    :QDialog(parent),
      ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Single Mode");

    Game_Scene = new QGraphicsScene(this);
    ui->Game_View->setScene(Game_Scene);

    GGtext = new QGraphicsSimpleTextItem;
    mySnake = new Snake;
    set_Snake();
    myFood = new Food;

    //creat map, wall
    creat_Map();
    creat_Wall();

    // add items to scene
    Game_Scene->addItem(mySnake->Item_Snake);
    Game_Scene->addItem(myFood->Item_Food[0]);
    Game_Scene->addItem(myFood->Item_Food[1]);
    Game_Scene->addItem(myFood->Item_Food[2]);
    Game_Scene->update();

    //connect some buttons to corresponding functions
    connect(ui->startButton,SIGNAL(clicked(bool)),mySnake,SLOT(startMove()));
    connect(ui->pauseButton,SIGNAL(clicked(bool)),mySnake,SLOT(pauseMove()));
    connect(ui->restartButton,SIGNAL(clicked(bool)),this,SLOT(restartGame()));
    connect(ui->AIButton,SIGNAL(clicked(bool)),mySnake,SLOT(AI()));
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
    // W:up A:left S:down D:right Q:quit AI mode Esc:back to menu
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
    case Qt::Key_Q:
        mySnake->stop_AI();
        break;
    case Qt::Key_Escape:
        mySnake->Clock->stop();
        emit back_Menu();
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
    //refresh scoreboard
    QString Scorestring  = "Score: ";
    QString ScoreNum = QString::number(mySnake->score);
    Scorestring.append(ScoreNum);
    ui->Scoreboard->setText(Scorestring);

    //refresh lifeboard
    QString Lifestring = "Life: ";
    QString LifeNum = QString::number(mySnake->life);
    Lifestring.append(LifeNum);
    ui->Lifeboard->setText(Lifestring);

    //refresh speedboard
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

    mySnake->food = myFood;//to make we can get Food information in class Snake
    mySnake->moveSnake();
    mySnake->check_eat(myFood);//check whether snake eat a food
    Game_Scene->update();
}

void GameWindow::GameOver(){
    mySnake->Clock->stop();
    GGtext->setBrush(Qt::black);
    GGtext->setText("You lose!");
    GGtext->setFont(QFont("华文琥珀，12"));
    Game_Scene->addItem(GGtext);
}

void GameWindow::restartGame(){
    //remove and new
    Game_Scene->removeItem(GGtext);
    Game_Scene->removeItem(mySnake->Item_Snake);
    Game_Scene->removeItem(myFood->Item_Food[0]);
    Game_Scene->removeItem(myFood->Item_Food[1]);
    Game_Scene->removeItem(myFood->Item_Food[2]);
    Game_Scene->update();
    delete mySnake;
    delete myFood;
    mySnake = new Snake;
    myFood = new Food;
    mySnake->setSnake();
    mySnake->score = 0;
    mySnake->speed = 100;
    mySnake->life = 1;
    Game_Scene->addItem(mySnake->Item_Snake);
    Game_Scene->addItem(myFood->Item_Food[0]);
    Game_Scene->addItem(myFood->Item_Food[1]);
    Game_Scene->addItem(myFood->Item_Food[2]);
    Game_Scene->update();
    connect(ui->startButton,SIGNAL(clicked(bool)),mySnake,SLOT(startMove()));
    connect(ui->pauseButton,SIGNAL(clicked(bool)),mySnake,SLOT(pauseMove()));
    connect(ui->restartButton,SIGNAL(clicked(bool)),this,SLOT(restartGame()));
    connect(ui->AIButton,SIGNAL(clicked(bool)),mySnake,SLOT(AI(Food *food)));
    connect(mySnake->Clock,SIGNAL(timeout()),this,SLOT(refresh_Scene()));
    connect(mySnake,&Snake::game_over,this,&GameWindow::GameOver);
}

