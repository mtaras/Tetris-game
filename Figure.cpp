/*
This is the Figure class that defines the way Tetris figures are build
and tells TetrisBoard class about the position and shapes of the figures.


Mikhail Tarasov
*/




#include "Figure.h"
#include "TetrisBoard.h"
#include <iostream>

//constructor
Figure::Figure(int h, int w, QString c, TetrisBoard* b)
    : x_coord(4), y_coord(0),  height(h), width(w), color(c), board(b) // start from position 4,0
{}

//destructor
Figure::~Figure()
{}

//method to rotate figure matrix counterclockwise
void Figure::rotate()
{
    bool okToRotate = true;

    // create a copy array so that we can use it in the case
    // when the rotation is not possible
    int c_array[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            c_array[i][j] = figure[i][j];

    //rotate the matrix
    int tmp;
    for (int i=0; i<2; i++){
            for (int j=i; j<4-i-1; j++){
                    tmp=figure[i][j];
                    figure[i][j]=figure[j][4-i-1];
                    figure[j][4-i-1]=figure[4-i-1][4-j-1];
                    figure[4-i-1][4-j-1]=figure[4-j-1][i];
                    figure[4-j-1][i]=tmp;
            }
    }

    //check if the board borders are in the way of rotation
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
             if(isFull(i,j)){
                  if((y_coord + i) > board->getHeight() - 1 || (y_coord + i) < 0 || (j + x_coord) < 0 || (j + x_coord) > board->getWidth() - 1 ){
                      okToRotate = false;
                      break;
                  }
             }
        }
    }
    //check if no other pieces are in the way of rotation
    if(okToRotate){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
             if(isFull(i,j)){
                  if(board->checkSquare(y_coord + i, j + x_coord )){
                      okToRotate = false;
                      break;
                  }
             }
        }
    }
}

    //if we cannot rotate use the backed up matrix
    if(okToRotate == false){
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                figure[i][j] = c_array[i][j];
    }
}

//method to check the matrix cell if it has 1 in it
bool Figure::isFull(int y, int x){
    return this->figure[y][x]==1;
}

//method to incrase y coordinates
bool Figure::moveDown()
{
    bool freeToMove = true;
    //check if the figure has hit the bottom
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(isFull(i,j)){
                if((y_coord + i + 1) > board->getHeight() - 1){
                    freeToMove = false;
                    break;
                }
            }
        }
}
    //check for occupied cells below
    if(freeToMove){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
               if(isFull(i,j)){
                   if(board->checkSquare(y_coord + i + 1, j + x_coord )){
                        freeToMove = false;
                        break;
                    }
                }
            }
        }
    }

    //move down if no restictions
    if(freeToMove)
      this->y_coord = this->y_coord + 1;
    else{
        board->stop();
        return false;
    }
    return true;
}

//method to decrease x coordinate
void Figure::moveLeft()
{

    bool freeToMove = true;
    //check if figure has hit the left border
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(isFull(i,j)){
                if((x_coord + j - 1) < 0){
                    freeToMove = false;
                    break;
                }
            }
        }
}

    //check if there are occupied blocks to the left
    if(freeToMove){
        for(int i = 0; i < height; i++){
             for(int j = 0; j < width; j++){
                 if(isFull(i,j)){
                    if(board->checkSquare(y_coord + i, j + x_coord - 1)){
                        freeToMove = false;
                        break;
                    }
                 }
             }
        }
    }

    //move down
    if(freeToMove)
      x_coord--;
}

//a method to increase x coordinates
void Figure::moveRight()
{
    bool freeToMove = true;
    //check if the figure has hit the right border
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(isFull(i,j)){
                if((x_coord + j + 1) > board->getWidth()-1){
                    freeToMove = false;
                    break;
                }
            }
        }
    }
    //check if there are occupied blocks to the right
    if(freeToMove){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(isFull(i,j)){    
                if(board->checkSquare(y_coord + i, j + x_coord + 1)){
                    freeToMove = false;
                    break;
                }
            }
        }
    }
    }
    //move right
    if(freeToMove)
      x_coord++;
}



//Factory method that returns a figure specified by an integer
Figure* Figure::getFigure(int type, TetrisBoard* b){

    if(type == 0) return new Square(b);
    else if(type == 1) return new Ipiece(b);
    else if(type == 2) return new Tpiece(b);
    else if(type == 3) return new Jpiece(b);
    else if(type == 4) return new Lpiece(b);
    else if(type == 5) return new Spiece(b);
    else if(type == 6) return new Zpiece(b);
}

//Square Constuctor
Square::Square(TetrisBoard *b)
    : Figure(4,4,"red",b)
{
    y_coord = -1;
    figure[0][0] = 0;
    figure[0][1] = 0;
    figure[0][2] = 0;
    figure[0][3] = 0;
    figure[1][0] = 0;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[1][3] = 0;
    figure[2][0] = 0;
    figure[2][1] = 1;
    figure[2][2] = 1;
    figure[2][3] = 0;
    figure[3][0] = 0;
    figure[3][1] = 0;
    figure[3][2] = 0;
    figure[3][3] = 0;
}
//Square destructor
Square::~Square()
{}

//Ipiece constructor
Ipiece::Ipiece(TetrisBoard *b)
    : Figure(4,4,"orange",b)
{
    y_coord = -1;
    figure[0][0] = 0;
    figure[0][1] = 0;
    figure[0][2] = 0;
    figure[0][3] = 0;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[1][3] = 1;
    figure[2][0] = 0;
    figure[2][1] = 0;
    figure[2][2] = 0;
    figure[2][3] = 0;
    figure[3][0] = 0;
    figure[3][1] = 0;
    figure[3][2] = 0;
    figure[3][3] = 0;

}

//Ipiece destructor
Ipiece::~Ipiece()
{}

//Tpiece constructor
Tpiece::Tpiece(TetrisBoard *b)
    : Figure(4,4,"yellow",b)
{
    y_coord = -1;
    figure[0][0] = 0;
    figure[0][1] = 0;
    figure[0][2] = 0;
    figure[0][3] = 0;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[1][3] = 0;
    figure[2][0] = 0;
    figure[2][1] = 1;
    figure[2][2] = 0;
    figure[2][3] = 0;
    figure[3][0] = 0;
    figure[3][1] = 0;
    figure[3][2] = 0;
    figure[3][3] = 0;
}
//Tpiece destructor
Tpiece::~Tpiece()
{}

//Jpiece constructor
Jpiece::Jpiece(TetrisBoard *b)
    : Figure(4,4,"purple",b)
{
    y_coord= -1;
    figure[0][0] = 0;
    figure[0][1] = 0;
    figure[0][2] = 0;
    figure[0][3] = 0;
    figure[1][0] = 0;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[1][3] = 1;
    figure[2][0] = 0;
    figure[2][1] = 0;
    figure[2][2] = 0;
    figure[2][3] = 1;
    figure[3][0] = 0;
    figure[3][1] = 0;
    figure[3][2] = 0;
    figure[3][3] = 0;
}
//Jpiece destructor
Jpiece::~Jpiece()
{}

//Lpiece constructor
Lpiece::Lpiece(TetrisBoard *b)
    : Figure(4,4,"blue",b)
{
    y_coord = -1;
    figure[0][0] = 0;
    figure[0][1] = 0;
    figure[0][2] = 0;
    figure[0][3] = 0;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[1][3] = 0;
    figure[2][0] = 1;
    figure[2][1] = 0;
    figure[2][2] = 0;
    figure[2][3] = 0;
    figure[3][0] = 0;
    figure[3][1] = 0;
    figure[3][2] = 0;
    figure[3][3] = 0;
}

//Lpiece destructor
Lpiece::~Lpiece()
{}

//Spiece constructor
Spiece::Spiece(TetrisBoard *b)
    : Figure(4,4,"sky",b)
{
    y_coord = -1;
    figure[0][0] = 0;
    figure[0][1] = 0;
    figure[0][2] = 0;
    figure[0][3] = 0;
    figure[1][0] = 0;
    figure[1][1] = 1;
    figure[1][2] = 1;
    figure[1][3] = 0;
    figure[2][0] = 1;
    figure[2][1] = 1;
    figure[2][2] = 0;
    figure[2][3] = 0;
    figure[3][0] = 0;
    figure[3][1] = 0;
    figure[3][2] = 0;
    figure[3][3] = 0;
}

//Spiece destructor
Spiece::~Spiece()
{}

//Zpiece constructor
Zpiece::Zpiece(TetrisBoard *b)
    : Figure(4,4,"green",b)
{
    y_coord = -1;
    figure[0][0] = 0;
    figure[0][1] = 0;
    figure[0][2] = 0;
    figure[0][3] = 0;
    figure[1][0] = 1;
    figure[1][1] = 1;
    figure[1][2] = 0;
    figure[1][3] = 0;
    figure[2][0] = 0;
    figure[2][1] = 1;
    figure[2][2] = 1;
    figure[2][3] = 0;
    figure[3][0] = 0;
    figure[3][1] = 0;
    figure[3][2] = 0;
    figure[3][3] = 0;
}

//Zpiece destructor
Zpiece::~Zpiece()
{}


