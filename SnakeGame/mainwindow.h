#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <ui_mainwindow.h>
#include "GameWindow.h"
#include "pvpgame.h"
#include "pvagame.h"


class QGraphicsScene;
class QGraphicsView;
class GameWindow;

class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void new_Game();//new single game
    void read_Archive();//read archive
    void Exit();//exit the game
    void Enter_settings();
    void PVP_Game();//enter PVP
    void show_Menu();
signals:
    void show_new_Game();
    void show_PVP_Game();
    void rebegin_Game();
    void show_settings();
private:
    Ui::MainWindow *ui;
    GameWindow *gwindow;//single game
    PVPGame *pgame;//PVP game
    void set_Button();

};
#endif // MAINWINDOW_H
