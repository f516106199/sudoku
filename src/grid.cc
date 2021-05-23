#include "../include/grid.hpp"

    namespace sudoku{
        namespace grid{

void grid::setVal(int val,Status status){
    this->val=val;
    this->status=status;
}

grid::grid& grid::operator=(const grid& g){
    val=g.val;
    status=g.status;
}
        }//namespace grid
    }//namepsace soduku