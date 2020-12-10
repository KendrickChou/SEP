#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include <ui_mainwindow.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsPathItem>
#include <QList>
#include <QPoint>

enum Move_dir{left,right,up,down};

class GameWindow:public QDialog
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent);
    ~GameWindow();
    void creat_Map();
    void creat_Wall();
    void set_Snake();
    bool check_eat_Food();
    void keyPressEvent(QKeyEvent *event);
    void refresh_Snake();

private slots:
    void receive_New_Game();
    void refresh_Scene();
    void set_Food();
    void GameOver();

private:
    Move_dir dir = left;
    QGraphicsScene* Game_Scene;
    QGraphicsView* Game_View;
    QTimer* Clock_Timer;
    QGraphicsRectItem* Item_Food;
    QGraphicsPathItem* Item_Snake;
    QList<QPoint> Snake_Body;
signals:
    void game_over();
};

#endif // GAMEWINDOW_H
