#include "pvagame.h"
#include "ui_pvagame.h"

const int MAP_GRID_NUM = 40;
const int MAP_GRID_SIZE = 20;

PVAGame::PVAGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PVAGame)
{
    ui->setupUi(this);
    setWindowTitle("Player Vs AI");

//    Game_Scene = new QGraphicsScene(this);
}

PVAGame::~PVAGame()
{
    delete ui;
}
