#ifndef _FONT_PROPERTIES_HPP_
#define _FONT_PROPERTIES_HPP_

#include<utility>
#include<iostream>

    namespace sudoku{
        namespace grid{  
            class grid;
        }//namespace grid
        namespace fontProperties{

enum fontColor{
    BOLD = 1,
    RESET = 0,
    BG_BLUE = 44,
    BG_DEFAULT = 49,
    BG_GREEN = 42,
    BG_RED = 41,
    FG_BLACK = 30,
    FG_BLUE = 34,
    FG_CYAN = 36,
    FG_DARK_GRAY = 90,
    FG_DEFAULT = 39,
    FG_GREEN = 32,
    FG_LIGHT_BLUE = 94,
    FG_LIGHT_CYAN = 96,
    FG_LIGHT_GRAY = 37,
    FG_LIGHT_GREEN = 92,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_RED = 91,
    FG_LIGHT_YELLOW = 93,
    FG_MAGENTA = 35,
    FG_RED = 31,
    FG_WHITE = 97,
    FG_YELLOW = 33,
};

class colorFormat{
private:
    fontColor fC;
public:
    colorFormat(fontColor m):fC(m){}
    fontColor retColor();
    friend std::ostream& 
    operator <<(std::ostream& os,colorFormat fc){
        return os<<"\033["<<fc<<"m";
    };

};

        }//namespace fontProperties
    }//namespace sudoku
#endif