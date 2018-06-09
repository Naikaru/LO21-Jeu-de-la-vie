#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
#include <iostream>

template<class T>
class Cell
{
 T value;
public:
    Cell(T v):value(v){}
    Cell(Cell& c):value(c.value){}

    virtual bool isAlive() = 0;
    virtual void kill() = 0;
    const T& getValue() const{ return value;}
};

class CellCent : public Cell<int>{
public:
    CellCent():Cell(100){}
    CellInt(int v):Cell(v){}
    CellInt(CellInt v):Cell(v){}
    virtual bool isAlive(){
        if(value > 0) return true;
        else return false;
    }
    virtual void kill(){
        value -= 20;
    }
};

class CellBool : public Cell<bool>{
public:
    CellInt():Cell(true){}
    CellInt(bool v):Cell(v){}
    CellInt(CellBool v):Cell(v){}
    virtual bool isAlive(){
        return value;
    }
    virtual void kill(){
        value = false;
    }
};
#endif // CELL_H
