#ifndef PVPGAME_H
#define PVPGAME_H

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
class PVPGame;
}

class PVPGame : public QDialog
{
    Q_OBJECT

public:
    explicit PVPGame(QWidget *parent = nullptr);
    void creat_Map();
    void creat_Wall();
    void set_Snake();
    void keyPressEvent(QKeyEvent *event);
    ~PVPGame();
private slots:
    void receive_New_Game();
    void refresh_P1();
    void refresh_P2();
    void GameOver();

private:
    Ui::PVPGame *ui;
    QGraphicsScene* Game_Scene;
    Snake *P1,*P2;
    Food *myFood;
    QGraphicsSimpleTextItem *GGtext;

};

#endif // PVPGAME_H
