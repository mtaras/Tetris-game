#include <QTimer>
#include <QTime>
#include <QString>
/*
This is the TetrisBoard class that consrtucts the gameboard
and handles most of the game functions and rules.


Mikhail Tarasov
*/



#include <QIcon>
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include <QKeyEvent>
#include "TetrisBoard.h"
#include "TetrisSquare.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QLineEdit>
#include <QTextStream>

/*
This is a TetrisBoard class that consrtucts the gameboard
and handles most of the game fucntions and rules
*/


//constructor
TetrisBoard::TetrisBoard(MainWindow* MW): mw(MW), gameOver(false),totalRowsRemoved(0), score_recorded(false)
{
    int i, j;
    // fill Tetris grid with push buttons and color them
    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            this->field[i][j] = new TetrisSquare;
            this->field[i][j]->setColor("white");
            this->field[i][j]->setIcon(QIcon("white.jpg"));
            this->field[i][j]->setIconSize(QSize(30,30));
            this->field[i][j]->setFlat(true);
            mw->addtoBoard(field[i][j], i, j);
        }
    }

    //create and fill the grid for displaying the next figure
    for (i = 0; i < NEXTWIDTH; ++i) {
        for (j = 0; j < NEXTWIDTH; ++j) {
            this->nextField[i][j] = new TetrisSquare;
            this->nextField[i][j]->setColor("white");
            this->nextField[i][j]->setIcon(QIcon("white.jpg"));
            this->nextField[i][j]->setIconSize(QSize(30,30));
            this->nextField[i][j]->setFlat(true);
            mw->addtoNextBoard(nextField[i][j], i, j);

        }
    }

    // populate topTen
    QFile file("top_ten.txt");
    if(file.open(QIODevice::ReadOnly)){
        while(!file.atEnd()){
            QString line = file.readLine();
            QStringList fields = line.split(" ");
            topTen[fields[1].toInt()] = fields[0];
        }
    }

    //generate the first two figures
    inMotion = true;
    srand((unsigned)time(0));
    currentFigure = Figure::getFigure(rand()%7, this);
    nextFigure = Figure::getFigure(rand()%7, this);
}


//destructor
TetrisBoard::~TetrisBoard(){
    delete currentFigure;
    delete nextFigure;
}


//method to check whether a specified square is occupied
bool TetrisBoard::checkSquare(int i, int j){
    return field[i][j]->checkVacancy();
}


//mehod to handle timer timeout
void TetrisBoard::tetrisTimeout(){

    // update current figure position on the board
    if(inMotion){
    hideFigure(currentFigure);

    currentFigure->moveDown();
    placeFigure(currentFigure);
    }
}
//method to draw current figure on the board
void TetrisBoard::placeFigure(Figure *f){
    for(int i=0;i<f->getHeight();i++){
        for(int j=0;j<f->getWidth();j++){
            if(f->isFull(i,j)){
                this->field[i+f->getY()][j+f->getX()]->setIcon(QIcon(f->getColor() + ".jpg"));
                this->field[i+f->getY()][j+f->getX()]->setIconSize(QSize(30,30));
                this->field[i+f->getY()][j+f->getX()]->setFlat(true);
            }
        }
    }
}

//method to hide the current figure from the board
void TetrisBoard::hideFigure(Figure *f){
    for(int i=0;i<f->getHeight();i++){
        for(int j=0;j<f->getWidth();j++){
            if(f->isFull(i,j)){
                this->field[i+f->getY()][j+f->getX()]->setIcon(QIcon("white.jpg"));
                this->field[i+f->getY()][j+f->getX()]->setIconSize(QSize(30,30));
                this->field[i+f->getY()][j+f->getX()]->setFlat(true);
            }
        }
    }
}



//method to draw the next figure on the next figure board
void TetrisBoard::placeNext(Figure *f){
    for(int i=0;i<f->getHeight();i++){
        for(int j=0;j<f->getWidth();j++){
            if(f->isFull(i,j)){
                this->nextField[i+f->getY()][j+f->getX()]->setIcon(QIcon(f->getColor() + ".jpg"));
                this->nextField[i+f->getY()][j+f->getX()]->setIconSize(QSize(30,30));
                this->nextField[i+f->getY()][j+f->getX()]->setFlat(true);
            }
        }
    }
}

//method to hide the figure on the next figure board
void TetrisBoard::hideNext(Figure *f){
    for(int i=0;i<f->getHeight();i++){
        for(int j=0;j<f->getWidth();j++){
            if(f->isFull(i,j)){
                this->nextField[i+f->getY()][j+f->getX()]->setIcon(QIcon("white.jpg"));
                this->nextField[i+f->getY()][j+f->getX()]->setIconSize(QSize(30,30));
                this->nextField[i+f->getY()][j+f->getX()]->setFlat(true);
            }
        }
    }
}

//methods that move current figure
//first hide it
//do the operation
//redraw the figure


//move the current figure to the left
void TetrisBoard::moveLeft(){
    hideFigure(currentFigure);
    currentFigure->moveLeft();
    placeFigure(currentFigure);
}

//move the current figure to the right
void TetrisBoard::moveRight(){
    hideFigure(currentFigure);
    currentFigure->moveRight();
    placeFigure(currentFigure);
}

//move the current figure down
void TetrisBoard::accelerate(){
    hideFigure(currentFigure);
    currentFigure->moveDown();
    placeFigure(currentFigure);
}
//method to rotate the current figure
void TetrisBoard::rotate(){
    hideFigure(currentFigure);
    currentFigure->rotate();
    placeFigure(currentFigure);
}

//method to clear a row when it is full
void TetrisBoard::clearRow(int r){

    for(int i = r; i > 0; i--){
        for(int j =0; j<10;j++){
            field[i][j]->setOccupied(field[i-1][j]->getOccupied());
            field[i][j]->setColor(field[i-1][j]->getColor());
            field[i-1][j]->setColor("white");
            field[i-1][j]->vacate();
            field[i][j]->setIcon(QIcon(field[i][j]->getColor() + ".jpg"));
            field[i-1][j]->setIcon(QIcon(field[i-1][j]->getColor() + ".jpg"));
        }
    }
}

//check if rows are full and can be removed
void TetrisBoard::checkRows(){

    int numOfRemoved = 0;
    bool rowIsFull = true;
    for(int i = HEIGHT - 1; i > -1; i--){
        rowIsFull = true;
        for(int j = 0; j<10;j++){
            if(field[i][j]->checkVacancy() == false){
                rowIsFull = false;
            }
        }
        //if row is full call the appropriate method
        if(rowIsFull){
            clearRow(i);
            i++;
            numOfRemoved++;
        }

    }
    //keep track of removed rows and add socre
    if(numOfRemoved > 0){
        totalRowsRemoved = totalRowsRemoved + numOfRemoved;
        mw->addScore(numOfRemoved);

    }
    //if 10 rows removed increase speed
    if(totalRowsRemoved > 9 ){
        mw->changeSpeed();
        totalRowsRemoved = totalRowsRemoved - 10;
    }

}
//method to handle the event when the figure lands on some surface
void TetrisBoard::stop(){
    inMotion = false;

    //check if we lose the game
    for(int j=0; j < nextFigure->getActualHeight(); j++){
        for(int i = 2; i < this->WIDTH-1; i++){
            if(field[j][i]->getOccupied()==true){
                gameOver = true;
                mw->gameOver();
            }
        }
    }
    //stop the figure and occupy the corresponding squares
    if(gameOver == false){
    for(int i=0;i<currentFigure->getHeight();i++){
        for(int j=0;j<currentFigure->getWidth();j++){
            if(currentFigure->isFull(i,j)){
                this->field[i+currentFigure->getY()][j+currentFigure->getX()]->setColor(currentFigure->getColor());
                this->field[i+currentFigure->getY()][j+currentFigure->getX()]->occupy();
                this->field[i+currentFigure->getY()][j+currentFigure->getX()]->setIcon(QIcon(field[i+currentFigure->getY()][j+currentFigure->getX()]->getColor() + ".jpg"));
                this->field[i+currentFigure->getY()][j+currentFigure->getX()]->setIconSize(QSize(30,30));
                this->field[i+currentFigure->getY()][j+currentFigure->getX()]->setFlat(true);

            }
        }
    }
    //check for filled rows
    checkRows();
    //assign a new figure from the next one
    currentFigure = nextFigure;
    hideNext(nextFigure);
    //generate next one
    nextFigure = Figure::getFigure(rand()%7, this);
    //place new figures
    placeNext(nextFigure);
    placeFigure(currentFigure);
    inMotion = true;
    }
}
//method to start new game
void TetrisBoard::startGame(){
    placeFigure(currentFigure);
    placeNext(nextFigure);
}

// displays the list of top ten scores and their names
void TetrisBoard::showTopTen()
{
    QFile file("top_ten.txt");
    QString scores = "";
    int i = 1;
    if(file.open(QIODevice::ReadOnly)){

        while(!file.atEnd()){
            QString line = file.readLine();
            scores.append( line + "\n");
            i++;
        }
    }
     if(scores=="")
         scores = "no scores recorded";

     QMessageBox::about(this->mw, QString("Top Ten"), scores);
}
// clears the list of top ten scores
void TetrisBoard::clearTopTen()
{
    topTen.clear();
    QFile file("top_ten.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
    file.close();

    // notify player scores were erased
    QMessageBox::about(this->mw, QString(""), QString("Scores cleared"));

}
// display into about the programmers
void TetrisBoard::displayAbout()
{
    QMessageBox::about(this->mw, QString("About"),
                       QString("Authors: Mikhail Tarasov, Tracy Okorie\n2011"));

}
//record the score
void TetrisBoard::recordScore()
{
    if(score_recorded) return;
    bool topTenMember = false;

    // get time
    int score = mw->getScore();
    if(!score){return;}  // score is zero

    if( topTen.size() < 10 ){

         topTenMember = true;

         // prompt for name
         bool ok;
         QString name = QInputDialog::getText(this->mw, QString("You got high score!"),
                                              QString("Your name:"), QLineEdit::Normal,
                                              QDir::home().dirName(), &ok);
        topTen[score] = name;
    }
    else
    {
        rit = topTen.rbegin();
        int worstScore = (*rit).first;
        if( score < worstScore )
        {
            topTenMember = true;
            // prompt for name
            bool ok;
            QString name = QInputDialog::getText(this->mw, QString("You got high score!"),
                                                 QString("Your name:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            // delete smallest
            topTen.erase( worstScore );
            // insert the screo
            topTen[score] = name;
        }
    }

        // rewrite the file
        QFile file("top_ten.txt");
        file.open(QFile::WriteOnly|QFile::Truncate);
        QTextStream out(&file);
        //it = topTen.begin();
        for( it = topTen.begin(); it != topTen.end(); it++ )
             out << (*it).second << " " << (*it).first << "\n";
        file.close();

        // display the updated list
        if (topTenMember)
            showTopTen();
        score_recorded=true;
    }
