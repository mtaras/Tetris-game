#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <TetrisBoard.h>
#include <QTimer>
#include <QTime>

namespace Ui {
    class MainWindow;
}

class TetrisBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //method to return ui
    Ui::MainWindow *getUI(){
        return ui;
    }

    void addtoBoard(QPushButton *w, int x, int y); // add Tetris squares to tetris layout
    void addtoNextBoard(QPushButton *w, int x, int y); //add Tetris squares to next figure layout
    void addScore(int); //add score
    void gameOver(); //game over event
    int getScore(); //get score

public slots:
    void timeoutHandler();          // handles time timeout
    void changeSpeed();             // increases speed
    void resetGame();               // resets the game
    void showTopTen();              // displays the list of top ten scores and their names
    void clearTopTen();             // clears the list of top ten scores
    void displayAbout();            // display into about the programmer
    void startGame();

private:
 //private datamemers
 Ui::MainWindow *ui;
 TetrisBoard *b;
 QTimer* timer;
 bool paused;
 int timePeriod;

protected:
    void keyPressEvent(QKeyEvent *event); //takes cares of pressed keys
};


#endif // MAINWINDOW_H
