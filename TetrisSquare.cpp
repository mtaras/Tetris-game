/*
This is the TetrisSquare that represents the basic building block of the game.
This class inherits from the QPushButton class


Mikhail Tarasov
*/



#include "TetrisSquare.h"
//constructor
TetrisSquare::TetrisSquare(QPushButton *parent) : QPushButton(parent), occupied(false)
{}

//destructor
TetrisSquare::~TetrisSquare(){
}
//method to check if square is vacant
bool TetrisSquare::checkVacancy(){
    return occupied;
}
//method to change color of the square
void TetrisSquare::setColor(QString c){
    color = c;
}
//method to set occupied true
void TetrisSquare::occupy(){
    occupied = true;
}
//method to set occupied false
void TetrisSquare::vacate(){
    occupied = false;
}
//method to change the occupied to a specified value
void TetrisSquare::setOccupied(bool o){
    occupied = o;
}
