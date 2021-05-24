#include "../include/grid.hpp"

    namespace sudoku{
        namespace grid{

void grid::setVal(int val,Status status){
    this->val=val;
    this->status=status;
}

grid& grid::operator=(const grid& g){
    val=g.val;
    status=g.status;
    return *this;
}
        }//namespace grid
    }//namepsace soduku