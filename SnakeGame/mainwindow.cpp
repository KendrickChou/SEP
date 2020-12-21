#include <QGraphicsScene>
#include <QIcon>
#include <QLabel>
#include "mainwindow.h"
#include <ui_mainwindow.h>
#include <QMovie>
#include <QBitmap>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Snake");
    setMaximumSize(810,810);
    setMinimumSize(300,300);//set window size

    ui->label->setStyleSheet("background-color:rgb(232,232,232)");
    QMovie *movie = new QMovie(":/images/icons/mainwindow.gif");
    movie->setScaledSize(ui->gif->size());
    ui->gif->setMovie(movie);
    movie->start();//add a gif to menu

    set_Button();

    //initial single game mode
    gwindow = new GameWindow(this);
    connect(this,SIGNAL(show_new_Game()),gwindow,SLOT(receive_New_Game()));
    connect(gwindow,SIGNAL(back_Menu()),this,SLOT(show_Menu()));

    //initial PVP mode
    pgame = new PVPGame(this);
    connect(this,SIGNAL(show_PVP_Game()),pgame,SLOT(receive_New_Game()));
    connect(pgame,SIGNAL(back_Menu()),this,SLOT(show_Menu()));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::new_Game(){
    this->hide();
    emit show_new_Game();
}

void MainWindow::PVP_Game(){
    this->hide();
    emit show_PVP_Game();
}

void MainWindow::Enter_settings(){
    this->hide();
    emit show_settings();
}

void MainWindow::Exit(){
    this->close();
}

void MainWindow::read_Archive(){

}

void MainWindow::show_Menu(){
    pgame->hide();
    gwindow->hide();
    this->show();
}

void MainWindow::set_Button(){
    connect(ui->Begin_button,SIGNAL(clicked()),this,SLOT(new_Game()));

    connect(ui->Archieve_Button,SIGNAL(clicked()),this,SLOT(read_Archive()));

    connect(ui->Exit_Button,SIGNAL(clicked()),this,SLOT(Exit()));

    connect(ui->PVP_button,SIGNAL(clicked()),this,SLOT(PVP_Game()));

    connect(ui->settings,SIGNAL(clicked()),this,SLOT(Enter_settings()));

    //set clicked effect
    QPixmap settings_map,rank_map,press_image,release_map;
    settings_map.load(":/images/icons/settings.png");
    release_map = settings_map.scaled(50,50,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    press_image = settings_map.scaled(45,45,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->settings->resize(release_map.size());
    ui->settings->setIcon(release_map);
    ui->settings->setIconSize(release_map.size());
    ui->settings->setMask(release_map.mask());
    connect(ui->settings, &QPushButton::pressed, [=](){
        ui->settings->resize(press_image.size());
        ui->settings->setIcon(press_image);
        ui->settings->setIconSize(press_image.size());
        ui->settings->setMask(press_image.mask());
    });

    connect(ui->settings, &QPushButton::released, [=](){
        ui->settings->resize(release_map.size());
        ui->settings->setIcon(release_map);
        ui->settings->setIconSize(release_map.size());
        ui->settings->setMask(release_map.mask());
    });


    rank_map.load(":/images/icons/ranking.png");
    release_map = rank_map.scaled(50,50,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    press_image = rank_map.scaled(45,45,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->rank->resize(release_map.size());
    ui->rank->setIcon(release_map);
    ui->rank->setIconSize(release_map.size());
    ui->rank->setMask(release_map.mask());
    connect(ui->rank, &QPushButton::pressed, [=](){
        ui->rank->resize(press_image.size());
        ui->rank->setIcon(press_image);
        ui->rank->setIconSize(press_image.size());
        ui->rank->setMask(press_image.mask());
    });

    connect(ui->rank, &QPushButton::released, [=](){
        ui->rank->resize(release_map.size());
        ui->rank->setIcon(release_map);
        ui->rank->setIconSize(release_map.size());
        ui->rank->setMask(release_map.mask());
    });
}




