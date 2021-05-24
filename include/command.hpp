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
    enum class Kind{
        BAD,
        OK
    };
    Kind kind;
    command(Kind kind):kind(kind){}
    command(Kind kind,int preval,grid::grid::Status pres, int curval,grid::grid::Status curs, int r,int c )
    :kind(kind),preVal(preval),preS(pres),curVal(curval),curS(curs),pos(std::make_pair(r,c)){}
private:
    int preVal;
    grid::grid::Status preS;
    int curVal;
    grid::grid::Status curS;
    std::pair<int,int>pos;   
};

class Ocommand :public command{
    friend class game::game;
    friend class scene::scene;
public:
    Ocommand(int preval,grid::grid::Status pres,int curval,grid::grid::Status curs,int r ,int c )
    :command(Kind::OK,preval,pres,curval,curs,r,c){}
};

class Bcommand:public command{
    friend class scene::scene;
    friend class game::game;
public:
    Bcommand(int preval,grid::grid::Status pres,int curval,grid::grid::Status curs,int r ,int c )
    :command(Kind::BAD,preval,pres,curval,curs,r,c){}
    void SetOther(grid::grid::Status pres,grid::grid::Status curs,int r ,int c );
private:
    grid::grid::Status OpreS;
    grid::grid::Status OcurS;
    std::pair<int,int>Opos;
};

        }//namespace command
    }//namespace sudoku
#endif