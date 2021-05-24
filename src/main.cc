#include"../include/scene.hpp"
#include"../include/game.hpp"
#include<iostream>
void printhelp(){
    std::cout << std::endl;
    std::cout << "sudoku - a little game in command line" << std::endl
              << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\t sudoku [-l <progressFile>]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t -l <path> \t specify path of progress file to load, optional." << std::endl
              << std::endl;
}

int chooseLevel(){
    std::cout<<std::endl;
    std::cout<<"choose level\t 1.bronze  2.gold  3.diamond  4.master"<<std::endl;
    int opt;
    std::cin>>opt;
    while(!(opt>0&&opt<5)){
        system("cls");
        std::cout<<"choose level\t 1.bronze  2.gold  3.diamond  4.master"<<std::endl;
        std::cin>>opt;
    }
    return opt;
}
int main(int argc,char**argv){
    sudoku::game::game * Game;
    if(argc==1){
        int opt=chooseLevel();
        sudoku::game::game::Level L;
        switch (opt)
        {
        case  1:
            L=sudoku::game::game::Level::bronze;
            break;
        case 2:
            L=sudoku::game::game::Level ::gold;
            break;
        case 3:
            L=sudoku::game::game::Level::diamond;
        case 4:
            L=sudoku::game::game::Level::master;
        }
        Game=new sudoku::game::game(L);
    }
    else if(argc==3){
        Game=new sudoku::game::game(argv[2]);
    }
    Game->init();
    auto play=new sudoku::scene::scene(*Game);
    play->start();
}