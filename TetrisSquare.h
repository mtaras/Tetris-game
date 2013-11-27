#ifndef TETRISSQUARE_H
#define TETRISSQUARE_H

#include <QPushButton>
#include <QString>

class TetrisSquare : public QPushButton
{
    Q_OBJECT

private:
    bool occupied;  //boolean to check if square is occupied
    QString color;  //color of the square

public:
    TetrisSquare(QPushButton *parent = 0);  //constructor
    ~TetrisSquare();                        //destructor
    bool checkVacancy();                    //check if vacant
    QString getColor();                     //return color
    void setColor(QString);                 //change color
    void occupy();                          //make occupied
    void vacate();                          //make not occupied
    bool getOccupied();                     //check if occupied
    void setOccupied(bool);                 //set the specified boolean value to occupied

};

inline QString TetrisSquare::getColor(){
        return this->color;
}


inline bool TetrisSquare::getOccupied(){
        return this->occupied;
}
#endif // TETRISSQUARE_H
