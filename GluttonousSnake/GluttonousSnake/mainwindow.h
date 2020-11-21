#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "Snake.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Snake snake;
    MainWindow(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int m_timerId;

public slots:

};
#endif // MAINWINDOW_H
