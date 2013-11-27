#include "TetrisSquare.h"
#include <QString.h>
#include "TetrisBoard.h"


#ifndef FIGURE_H
#define FIGURE_H
class TetrisBoard;

class Figure{

protected:
    int x_coord; //x coordinate
    int y_coord; //y coordinate
    int width;   //width of the figure matrix
    int height;  //height of the figure matrix
    int figure[4][4];   //template matrix
    QString color;  //color
    TetrisBoard* board; //figure has to be aware of the board that gets the figure
    Figure(int, int, QString, TetrisBoard*); //constructor


public:
    static Figure* getFigure(int, TetrisBoard*); //factory method
    virtual ~Figure() = 0;  //destructor
    virtual bool isFull(int, int);  //check figure matrix for 1
    void rotate();  //rotate method
    bool moveDown();    //move down method
    void moveLeft();    // move left method
    void moveRight();   //move right method
    QString getColor(); //return color
    int getWidth();     //returns width of the figure matrix
    int getHeight();    //returns height of the figure matrix
    int getY();         //returns y coordinate
    int getX();         //returns x coordinate
    virtual int getActualHeight();  //returns the height of the figure itself (i.e. 2 for square)
};

inline QString Figure::getColor(){
    return this->color;
}
inline int Figure::getHeight(){
    return this->height;
}
inline int Figure::getWidth(){
    return this->width;
}
inline int Figure::getX(){
    return this->x_coord;
}
inline int Figure::getY(){
    return this->y_coord;
}
inline int Figure::getActualHeight(){
    return 2;
}

//declarations of all the children of Figure class:

class Square: public Figure{

friend class Figure;
private:
  Square(TetrisBoard*);

public:
    virtual ~Square();

};

class Ipiece: public Figure{
friend class Figure;

private:
    Ipiece(TetrisBoard*);

public:
    virtual ~Ipiece();
    virtual int getActualHeight();
};
inline int Ipiece::getActualHeight(){
    return 1;
}

class Tpiece: public Figure{

friend class Figure;

private:
    Tpiece(TetrisBoard*);

public:
    virtual ~Tpiece();
};

class Jpiece: public Figure{
friend class Figure;

private:
    Jpiece(TetrisBoard*);

public:
    virtual ~Jpiece();
};

class Lpiece: public Figure{
friend class Figure;

private:
    Lpiece(TetrisBoard*);

public:
    virtual ~Lpiece();
};

class Spiece: public Figure{
friend class Figure;

private:
    Spiece(TetrisBoard*);

public:
    virtual ~Spiece();
};

class Zpiece: public Figure{
friend class Figure;

private:
    Zpiece(TetrisBoard*);

public:
    virtual ~Zpiece();
};

#endif // FIGURE_H
