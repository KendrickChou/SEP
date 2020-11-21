#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
{
    resize(1000,1000);
    m_timerId = startTimer(1000);
}

MainWindow::~MainWindow()
{
}

void MainWindow::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_timerId)
       {
        QPainter *p;
        render(p);
    }
}

void MainWindow::render(QPainter *p){
    p->setRenderHint(QPainter::Antialiasing);
    snake.DrawSnake();
}

