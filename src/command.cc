#include"../include/command.hpp"
    namespace sudoku{
        namespace command{
void Bcommand::SetOther(grid::grid::Status pres,grid::grid::Status curs,int r ,int c ){
    OpreS=pres;
    OcurS=curs;
    Opos=std::make_pair(r,c);
}
        }//namespace sudoku
    }//namespace command