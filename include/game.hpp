#ifndef _GAME_HPP_
#define _GAME_HPP_

#include<vector>
#include<array>
#include<string>
#include"../include/grid.hpp"
#include"../include/command.hpp"
    namespace sudoku{
        namespace scene{
            class scene;
        }
        namespace game{
class game{
    friend class scene::scene;
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
   // void run();
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
    std::pair<int,int>curpos;
    std::array<grid::grid,81>table;
    int eraseNum;
    Status status;
    Level level;
    std::string saveDir;
    std::vector<command::command*>cmdVec;
    bool saveFile();
    struct errinfo{
        bool err;
        std::pair<int,int>p1;
        std::pair<int,int>p2;
        errinfo(bool err,int a,int b,int c,int d):err(err),p1(std::make_pair(a,b)),p2(std::make_pair(c,d)){}
    };
    errinfo check();
    void fillCenter();
    void fillVertex();
    void fillBorder();
    bool loadFile();
    void eraseGrid();
    void setCheckChange(const errinfo& res);
    void undo();
};


        }//namespace game
    }//namespace sudoku

#endif
