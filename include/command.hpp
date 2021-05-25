/* class sotre the envalue operation  */

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_
#include"../include/grid.hpp"
#include<utility>
    namespace sudoku{
        namespace scene{
            class scene;
        }
        namespace game{
            class game;
        }
        namespace command{

class command{
    friend class game::game;
public:
    command()=default;
    command(int preval, int curval, int r,int c )
    :preVal(preval),curVal(curval),pos(std::make_pair(r,c)){}
private:
    int preVal;
    int curVal;
    std::pair<int,int>pos;   
};

        }//namespace command
    }//namespace sudoku
#endif