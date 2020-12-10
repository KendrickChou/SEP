#include <QGraphicsScene>
#include <QIcon>
#include <QLabel>
#include "mainwindow.h"
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Snake");
    setMaximumSize(800,800);
    setMinimumSize(300,300);
    setStyleSheet("backgroung::white");

    Begin_botton = new QPushButton(this);
    Begin_botton->setText("New Game");
    Begin_botton->move(350,200);
    connect(Begin_botton,SIGNAL(clicked()),this,SLOT(new_Game()));

    Archive_botton = new QPushButton(this);
    Archive_botton->setText("Continue");
    Archive_botton->move(350,300);
    connect(Archive_botton,SIGNAL(clicked()),this,SLOT(read_Archive()));

    Exit_botton = new QPushButton(this);
    Exit_botton->setText("Exit");
    Exit_botton->move(350,400);
    connect(Exit_botton,SIGNAL(clicked()),this,SLOT(Exit()));

    gwindow = new GameWindow(this);
    connect(this,SIGNAL(show_new_Game()),gwindow,SLOT(receive_New_Game()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::new_Game(){
    this->hide();
    emit show_new_Game();
}

void MainWindow::Exit(){
    this->close();
}

void MainWindow::read_Archive(){

}


