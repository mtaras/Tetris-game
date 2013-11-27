/*
This is the mainwindow class that is responsible for User Interface elements
and takes care of the keyboard controls


Mikhail Tarasov
*/




#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QString>
#include <QIcon>
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include <QKeyEvent>
#include <TetrisBoard.h>

//cosntrictor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),timePeriod(1000), paused(),
    ui(new Ui::MainWindow)
{
    //initialize the board
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus); //for key press events

    b = new TetrisBoard(this);
    ui->pauseMessage->hide();
    ui->gameover->hide();
    ui->TetrisLayout->setSpacing(0);

    ui->nextFigureLayout->setSpacing(0);
    timer = new QTimer(this);

    // connect the necessary signals and slots
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutHandler()));
    connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(resetGame()));
    connect(ui->actionTT, SIGNAL(triggered()), this, SLOT(showTopTen()));
    connect(ui->actionClear_TT, SIGNAL(triggered()), this, SLOT(clearTopTen()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(displayAbout()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(startGame()));
}
//destructor
MainWindow::~MainWindow()
{
    delete b;
    delete timer;
    delete ui;
}

//method to handle key press events
void MainWindow::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Escape && !paused) {
       this->close();
   }
   else if(event->key() == Qt::Key_A && !paused){
       b->moveLeft();
   }
   else if(event->key() == Qt::Key_D && !paused){
       b->moveRight();
   }

   else if(event->key() == Qt::Key_S && !paused){
       b->accelerate();
   }

   else if(event->key() == Qt::Key_W && !paused){
       b->rotate();
   }
   else if(event->key() == Qt::Key_P){
       if(paused){
           paused = false;
           this->timer->start(timePeriod);
           ui->pauseMessage->hide();
       }
       else{
           paused = true;
           this->timer->stop();
           ui->pauseMessage->show();
       }

   }
}
//function that is called when the timer times out
void MainWindow::timeoutHandler()
{
   //pass control to the tetris board
   b->tetrisTimeout();
}
//method to show top ten
void MainWindow::showTopTen()              // displays the list of top ten scores and their names
{
    b->showTopTen();
}
//method to clear top ten
void MainWindow::clearTopTen()             // clears the list of top ten scores
{
    b->clearTopTen();
}
//method to display about info
void MainWindow::displayAbout()            // display into about the programmer
{
    b->displayAbout();
}
//method to insert Tetris squares to the Tetris layout
void MainWindow::addtoBoard(QPushButton *w, int x, int y){
    ui->TetrisLayout->addWidget( w, x, y);
}
//method to insert Tetris squares to the next figure layout
void MainWindow::addtoNextBoard(QPushButton *w, int x, int y){
    ui->nextFigureLayout->addWidget( w, x, y);
}

//method that adds score to the scoreboard
void MainWindow::addScore(int s){
    if(s == 1) //1 row removed
       ui->scoreLCD->display(ui->scoreLCD->value() + 10);
    else if(s == 2) //2 rows removed
       ui->scoreLCD->display(ui->scoreLCD->value() + 50);
    else if(s == 3) //3 rows removed
       ui->scoreLCD->display(ui->scoreLCD->value() + 100);
    else if(s == 4) //4 rows removed
       ui->scoreLCD->display(ui->scoreLCD->value() + 200);
}

    //method to decrease tetris timeout time to increase pace of the game
void MainWindow::changeSpeed(){

    if(timePeriod > 100){   //do not lower below 100 ms
    this->timePeriod = this->timePeriod - 100;
    this->timer->start(timePeriod);
    ui->speed->display(ui->speed->value() + 1);
    }
}

//method to hadle game over event
void MainWindow::gameOver(){
    timer->stop();
    ui->gameover->show();
    b->recordScore();
}

//method to return the current score
int MainWindow::getScore(){
    return ui->scoreLCD->value();
}
//method to start the game
void MainWindow::startGame(){
    this->timer->start(timePeriod);
    b->startGame();
}
//method to restart the game
void MainWindow::resetGame(){
    delete b;
    ui->scoreLCD->display(ui->scoreLCD->value()*0);
    ui->speed->display(ui->speed->value()*0);
    b = new TetrisBoard(this);
    ui->pauseMessage->hide();
    ui->gameover->hide();
    ui->TetrisLayout->setSpacing(0);
    ui->nextFigureLayout->setSpacing(0);
    timePeriod = 1000;
    startGame();
}
