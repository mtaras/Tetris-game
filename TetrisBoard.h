#ifndef TETRISBOARD_H
#define TETRISBOARD_H
#include "Figure.h"
#include "TetrisSquare.h"
#include <mainwindow.h>
#include <QTimer>
#include <map>


class MainWindow;
class Figure;

class TetrisBoard{
private:
    //board dimensions
    const static int HEIGHT = 18;
    const static int WIDTH = 10;
    const static int NEXTWIDTH = 4;

    bool inMotion;  //boolean to see if figure is still moving
    bool gameOver;  //boolean to see if game is over
    bool score_recorded;    //boolean to see if score was recorded

    int totalRowsRemoved;   //keep track of total removed rows

    //Figures
    Figure *currentFigure;
    Figure *nextFigure;

    // the 2D array of squares that comprise the game board
    TetrisSquare *field[HEIGHT][WIDTH];
    TetrisSquare *nextField[NEXTWIDTH][NEXTWIDTH];

    MainWindow *mw;             // a pointer to the main window

    // stores top ten scores
    std::map<int, QString> topTen;
    std::map<int, QString>::iterator it;
    std::map<int, QString>::reverse_iterator rit;

public:
    TetrisBoard(MainWindow* MW); // constructor
    ~TetrisBoard();              // destructor
    MainWindow* getMW();         // return the pointer to the main window
    void setMW(MainWindow *m);   // sets up the ui
    void placeFigure(Figure*);   // shows figure
    void hideFigure(Figure*);    // hides figure
    void placeNext(Figure*);     // show next figure
    void hideNext(Figure*);      // hide next video
    void tetrisTimeout();        // handles timeout
    void moveLeft();             // move figure left
    void moveRight();            // move figure right
    void accelerate();           // accelerate figure down
    bool checkSquare(int, int);  // check if given square is uccupied
    void stop();                 // stops the current figure
    void rotate();               // rotates the current figure
    void checkRows();            // check for filled rows
    void clearRow(int);          // clears specified rows
    void recordScore();          // records score
    int getHeight();             // returns board height
    int getWidth();              // returns board width

    void exitGame();             // exits game
    void resetGame();            // resets the game
    void showTopTen();           // displays the list of top ten scores and their names
    void clearTopTen();          // clears the list of top ten scores
    void displayAbout();         // display into about the programmer

    void startGame();            //starts game

};

//set the window
inline void TetrisBoard::setMW(MainWindow* m)
{   mw = m; }

//return window
inline MainWindow* TetrisBoard::getMW()
{   return mw; }

//return board height
inline int TetrisBoard::getHeight(){
    return HEIGHT;
}

//return board width
inline int TetrisBoard::getWidth(){
    return WIDTH;
}


#endif // TETRISBOARD_H
