#ifndef _GAME_HPP_
#define _GAME_HPP_

#include<vector>
#include<array>
#include<string>
#include"../include/grid.hpp"

    namespace sudoku{
        namespace game{
class game{
public:
    enum class Status{
        CONTINUE,
        ERROR,
        OK
    };
    enum class Level{
        bronze,
        gold,
        diamond,
        master
    };
    void setLevel(); //set level and make sure erasenum
    void generate();// genertate game 
    void loadFile();
    void run();

private:
    std::array<grid::grid,81>table;
    int eraseNum;
    Status status;
    Level level;
    std::string saveDir;
    void saveFile();
    void check();
};


        }//namespace game
    }//namespace sudoku

#endif
