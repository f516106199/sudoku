#include"../include/game.hpp"
#include<fstream>
#include<exception>
#include<iostream>
    namespace sudoku{
        namespace game{

bool game::saveFile(){
    std::ofstream osf;
    osf.open(saveDir, std::ios::out|std::ios::ate);
    try {
        if(!osf.is_open()){
            throw std::runtime_error("can't open the file to save ");
        }
    }
    catch(std::runtime_error& e){
        //showerr
        return 0;
    }
    switch (level)
    {
    case  Level::bronze:
        osf<<"bronze\t"<<eraseNum<<'\n';
        break;
    case  Level::diamond:
        osf<<"diamond\t"<<eraseNum<<'\n';
        break;
    case  Level::gold:
        osf<<"gold\t"<<eraseNum<<'\n';
        break;
    case  Level::master:
        osf<<"master\t"<<eraseNum<<'\n';
        break;    
    default:
        break;
    }
    for(auto m:table){
        if(m.status==grid::grid::Status::UNCERTAIN){
            osf<<0<<' ';
        }
        else 
            osf<<m.val<<' ';
    }
    osf<<'\n';
    for(int i=0;i!=81;++i){
        if(table[i].status!=grid::grid::Status::INITED){
            osf<<i;
        }
    }
    
    osf.close();
    return 1;
}
bool game::loadFile(){
    std::ifstream isf(saveDir,std::ios::in);
    if(!isf.is_open()){
        std::cerr<<"fail to open the file"<<std::endl;
        exit(-1);
    }
    std:: string strtmp;
    isf>>strtmp;
    if(strtmp=="bronze"){
        level=Level::bronze;
    }
    else if(strtmp=="diamond"){
        level=Level::diamond;
    }   
    else if(strtmp=="master"){
        level==Level::master;
    }
    else if(strtmp=="gold"){
        level==Level::gold;
    }
    isf>>eraseNum;
    for(int i=0;i!=81;++i){
        isf>>table[i].val;
        if(table[i].val==0){
            table[i].status=grid::grid::Status::UNCERTAIN;   
        }
        else {
            table[i].status=grid::grid::Status::SET;
        }
    }
    int v;
    while(isf>>v){
        table[v].status=grid::grid::Status::INITED;
    }
    isf.close();
    return 1;
}
bool game::check(){
    int i=curpos.first;
    int j=curpos.second;
    int val=table[i*9+j].val;
    for(int k=0;k!=9;++k){
        if(table[i*9+k].val==val&&k!=j){
            return 0;
        }
        if(table[k*9+j].val==val&&k!=i){
            return 0;
        }   
    }
    i/=3;
    j/=3;
    for(int m=i;m!=i+3;++m){
        for(int n=j;n!=j+3;++j){
            if(table[m*9+n].val==val&&m!=curpos.first&&n!=curpos.second){
                return 0;
            }
        }
    }
    return 1;
}

void game::fillCenter(){
    bool used[9]={0};
    srand((int)time(0));
    for(int i=3;i!=6;++i){
        for(int j=3;j!=6;++j){
            int t=rand()%9;
            while(used[t]){
                t=rand()%9;
            }
            table[i*9+j].setVal(t+1,grid::grid::Status::INITED);
            used[t]=1;
        }
    }
}
void game::fillVertex(){
    for(int i=0;i!=3;++i){
        for(int j=0;j!=3;++j){
            if(i==0)
                table[i*9+j]=table[4*9+j+3];
            else if(i==1)
                table[i*9+j]=table[5*9+j+3];
            else if(i==2)
                table[i*9+j]=table[3*9+j+3];
        }
    }
    for(int i=0;i!=3;++i){
        for(int j=6;j!=9;++j){
            if(i==0)
                table[i*9+j]=table[5*9+j-3];
            else if(i==1)
                table[i*9+j]=table[3*9+j-3];
            else if(i==2)
                table[i*9+j]=table[4*9+j-3];
        }
    }
    for(int i=6;i!=9;++i){
        for(int j=0;j!=3;++j){
            if(i==6)
                table[i*9+j]=table[4*9+j+3];
            else if(i==7)
                table[i*9+j]=table[5*9+j+3];
            else if(i==8)
                table[i*9+j]=table[3*9+j+3];
        }
    }
    for(int i=6;i!=9;++i){
        for(int j=6;j!=9;++j){
            if(i==6)
                table[i*9+j]=table[5*9+j-3];
            else if(i==7)
                table[i*9+j]=table[3*9+j-3];
            else if(i==8)
                table[i*9+j]=table[4*9+j-3];
        }
    }
}
void game::fillBorder(){
    for(int i=0;i!=3;++i){
        for(int j=3;j!=6;++j){
            if(j==3)
                table[i*9+j]=table[(i+3)*9+4];
            else if(j==4)
                table[i*9+j]=table[(i+3)*9+5];
            else if(j==5)
                table[i*9+j]=table[(i+3)*9+3];
        }
    }
    for(int i=6;i!=9;++i){
        for(int j=3;j+6;++j){
            if(j==3)
                table[i*9+j]=table[(i-3*9+5)];
            else if(j=4)
                table[i*9+j]=table[(i-3)*9+3];
            else if(j==5)
                table[i*9+j]=table[(i-3)*9+4];
        }
    }
    for(int i=3;i!=6;++i){
        for(int j=0;j!=3;++j){
            if(i==3)
                table[i*9+j]=table[(4*9+j+3)];
            else if(i==4)
                table[i*9+j]=table[(5*9)+j+3];
            else if(i==5)
                table[i*9+j]=table[3*9+j+3];
        }
    }
    for(int i=3;i!=6;++i){
        for(int j=6;j!=9;++j){
            if(i==3)
                table[i*9+j]=table[5*9+j-3];
            else if(i==4)
                table[i*9+j]=table[3*9+j-3];
            else if(i==5)
               table[i*9+j]=table[4*9+j-3];
        }
    }
}
void game::generate(){
    fillCenter();
    fillBorder();
    fillVertex();
    eraseGrid();
}

void game::run(){

}
bool game::init(){
    if(saveDir.empty()){
        generate();
        return 1;
    }
    else {
        return loadFile();
    }
}


        }//namespace game;
    }//namespace sudoku 