#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include "ui_GameWindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include "Snake.h"
#include "Food.h"
#include <QPoint>

namespace Ui {
class GameWindow;
}

class GameWindow:public QDialog
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent);
    ~GameWindow();
    void creat_Map();
    void creat_Wall();
    void set_Snake();//draw Snake
    void keyPressEvent(QKeyEvent *event);

private slots:
    void receive_New_Game();//show a new game when click the single game button in menu
    void refresh_Scene();//refresh the scene when clock is timeout
    void GameOver();
    void restartGame();

private:
    QGraphicsScene* Game_Scene;
    QGraphicsSimpleTextItem *GGtext;//when GG, show this text
    Snake *mySnake;
    Food *myFood;
    Ui::GameWindow *ui;
signals:
    void back_Menu();//back to the menu
};

#endif // GAMEWINDOW_H
