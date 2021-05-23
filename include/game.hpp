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
    void generate();// genertate game 
    void run();
    bool init();
    game():eraseNum(0),status(Status::CONTINUE),saveDir(){}
    game(Level level):status(Status::CONTINUE),level(level),saveDir(){
        switch (level)
        {
        case Level::bronze: eraseNum=30;break;
        case Level::gold: eraseNum=40;break;
        case Level::diamond: eraseNum=50;break;
        case Level::master:eraseNum=60;break;        
        default:
            break;
        }
    }
    game(const std::string str):saveDir(str){}
private:
    std::pair<int,int>prepos;
    std::pair<int,int>curpos;
    std::array<grid::grid,81>table;
    int eraseNum;
    Status status;
    Level level;
    std::string saveDir;
    bool saveFile();
    bool check();
    void fillCenter();
    void fillVertex();
    void fillBorder();
    bool loadFile();
    void eraseGrid();
};


        }//namespace game
    }//namespace sudoku

#endif
