#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <ui_mainwindow.h>
#include "GameWindow.h"


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
signals:
    void show_new_Game();
private:
    Ui::MainWindow *ui;
    void set_Button();
    GameWindow *gwindow;
};
#endif // MAINWINDOW_H
