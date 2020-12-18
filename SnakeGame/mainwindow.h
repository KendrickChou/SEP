#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <ui_mainwindow.h>
#include "GameWindow.h"
#include "pvpgame.h"


class QGraphicsScene;
class QGraphicsView;
class GameWindow;

class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void dealJump();
private slots:
    void new_Game();
    void read_Archive();
    void Exit();
    void Enter_settings();
    void new_gwindow();
    void PVP_Game();
signals:
    void show_new_Game();
    void show_PVP_Game();
    void rebegin_Game();
    void show_settings();
private:
    Ui::MainWindow *ui;
    void set_Button();
    GameWindow *gwindow,*ngwindow;
    PVPGame *pgame;
};
#endif // MAINWINDOW_H
