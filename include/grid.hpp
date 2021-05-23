#ifndef _GRID_HPP_
#define _GRID_HPP_

    namespace sudoku{
        namespace game{
            class game;
        }
        namespace grid{

class grid{
    friend class game;
public:
    enum class Status{
        INITED,
        UNCERTAIN,
        SET
    };
    grid(Status status):status(status){}
    void setVal(int val,Status status);
private:
    int val;
    Status status;
};




        }//namespace grid
    }//namespace sudoku
#endif