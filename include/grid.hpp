#ifndef _GRID_HPP_
#define _GRID_HPP_

    namespace sudoku{
        namespace game{
            class game;
        }
        namespace grid{

class grid{
    friend class game::game;
public:
    enum class Status{
        INITED,
        UNCERTAIN,
        SET,
        ERR,
        FakeErr
    };
    grid(Status status):status(status){}
    grid(){}
    void setVal(int val,Status status);
    grid & operator = (const grid&);
    int val;
    Status status;
};




        }//namespace grid
    }//namespace sudoku
#endif