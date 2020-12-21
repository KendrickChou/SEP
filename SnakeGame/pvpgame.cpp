#include "pvpgame.h"
#include "ui_pvpgame.h"


const int MAP_GRID_NUM = 40;
const int MAP_GRID_SIZE = 20;

PVPGame::PVPGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PVPGame)
{
    ui->setupUi(this);
    setWindowTitle("PVP");

    Game_Scene = new QGraphicsScene(this);
    ui->Game_View->setScene(Game_Scene);

    P1 = new Snake;
    P1->Change_Pos(-18,17,-18,18,-18,19);
    P1->Item_Snake->setBrush(QBrush(QColor::fromRgb(99,184,255)));
    P1->dir = up;

    P2 = new Snake;
    P2->Change_Pos(18,-18,18,-19,18,-20);
    P2->Item_Snake->setBrush(QBrush(QColor::fromRgb(102,205,170)));
    P2->dir = down;
    GGtext = new QGraphicsSimpleTextItem;

    myFood = new Food;
    creat_Map();
    creat_Wall();
    set_Snake();

    Game_Scene->addItem(P1->Item_Snake);
    Game_Scene->addItem(P2->Item_Snake);
    Game_Scene->addItem(myFood->Item_Food[0]);
    Game_Scene->addItem(myFood->Item_Food[1]);
    Game_Scene->addItem(myFood->Item_Food[2]);
    Game_Scene->update();

    connect(ui->startButton,SIGNAL(clicked(bool)),P1,SLOT(startMove()));
    connect(ui->startButton,SIGNAL(clicked(bool)),P2,SLOT(startMove()));
    connect(ui->pausebutton,SIGNAL(clicked(bool)),P1,SLOT(pauseMove()));
    connect(ui->pausebutton,SIGNAL(clicked(bool)),P2,SLOT(pauseMove()));
    connect(P1->Clock,SIGNAL(timeout()),this,SLOT(refresh_P1()));
    connect(P2->Clock,SIGNAL(timeout()),this,SLOT(refresh_P2()));
    connect(P1,&Snake::game_over,this,&PVPGame::GameOver);
    connect(P2,&Snake::game_over,this,&PVPGame::GameOver);


}

PVPGame::~PVPGame()
{
    delete ui;
}

void PVPGame::creat_Map(){
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

void PVPGame::creat_Wall(){
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

void PVPGame::set_Snake(){
   P1->setSnake();
   P2->setSnake();
}

void PVPGame::keyPressEvent(QKeyEvent *event){
    //P1: W:up A:left S:down D:right
    //P2:I:up J:left K:down L:right
    switch (event->key()) {
    case Qt::Key_W:
        if(P1->dir != down){
            P1->dir = up;
        }
        break;
    case Qt::Key_A:
        if(P1->dir != right){
            P1->dir = left;
        }
        break;
    case Qt::Key_S:
        if(P1->dir != up){
         P1->dir = down;
        }
        break;
    case Qt::Key_D:
        if(P1->dir != left){
            P1->dir = right;
        }
        break;
    case Qt::Key_I:
        if(P2->dir != down){
            P2->dir = up;
        }
        break;
    case Qt::Key_J:
        if(P2->dir != right){
            P2->dir = left;
        }
        break;
    case Qt::Key_K:
        if(P2->dir != up){
         P2->dir = down;
        }
        break;
    case Qt::Key_L:
        if(P2->dir != left){
            P2->dir = right;
        }
        break;
    case Qt::Key_Escape:
        P1->Clock->stop();
        P2->Clock->stop();
        emit back_Menu();
    default:
        break;
    }
}

void PVPGame::refresh_P1(){
    QString Scorestring  = "Score: ";
    QString ScoreNum = QString::number(P1->score);
    Scorestring.append(ScoreNum);
    ui->ScoreLabel->setText(Scorestring);

    QString Lifestring = "Life: ";
    QString LifeNum = QString::number(P1->life);
    Lifestring.append(LifeNum);
    ui->LifeLabel->setText(Lifestring);

    QString Speedstring = "Speed: ";
    QString Speedlevel;
    switch (P1->speed) {
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
    ui->SpeedLabel->setText(Speedstring);

    P1->moveSnake();
    P1->check_eat(myFood);
    Game_Scene->update();
}

void PVPGame::refresh_P2(){
    QString Scorestring  = "Score: ";
    QString ScoreNum = QString::number(P2->score);
    Scorestring.append(ScoreNum);
    ui->ScoreLabel_2->setText(Scorestring);

    QString Lifestring = "Life: ";
    QString LifeNum = QString::number(P2->life);
    Lifestring.append(LifeNum);
    ui->LifeLabel_2->setText(Lifestring);

    QString Speedstring = "Speed: ";
    QString Speedlevel;
    switch (P2->speed) {
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
    ui->SpeedLabel_2->setText(Speedstring);

    P2->moveSnake();
    P2->check_eat(myFood);
    Game_Scene->update();
}

void PVPGame::receive_New_Game(){
    this->show();
}

void PVPGame::GameOver(){
    P1->Clock->stop();
    P2->Clock->stop();
    GGtext->setBrush(Qt::black);
    if(P1->score > P2->score){
        GGtext->setText("P1 win!");
    }
    else if(P1->score == P2->score){
        GGtext->setText("Tied!");
    }
    else{
        GGtext->setText("P2 win!");
    }
    GGtext->setFont(QFont("华文琥珀，12"));
    Game_Scene->addItem(GGtext);
}
