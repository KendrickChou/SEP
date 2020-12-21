#ifndef PVAGAME_H
#define PVAGAME_H

#include <QDialog>
#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include "ui_pvpgame.h"
#include "Snake.h"
#include "Food.h"
#include <QPoint>

namespace Ui {
class PVAGame;
}

class PVAGame : public QDialog
{
    Q_OBJECT

public:
    explicit PVAGame(QWidget *parent = nullptr);
//    void creat_Map();
//    void creat_Wall();
//    void set_Snake();
//    void keyPressEvent(QKeyEvent *event);
    ~PVAGame();

private slots:
//    void receive_New_Game();
//    void refresh_P1();
//    void refresh_P2();
//    void GameOver();

private:
    Ui::PVPGame *ui;
//    QGraphicsScene* Game_Scene;
//    Snake *Player;
//    Food *myFood;
//    QGraphicsSimpleTextItem *GGtext;

private:
};

#endif // PVAGAME_H
