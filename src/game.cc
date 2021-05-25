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
        switch (m.status){
            case  grid::grid::Status::INITED:
                osf<<"INITED "<<m.val<<' ';
                break;
            case grid::grid::Status::ERR:
                osf<<"ERR "<<m.val<<' ';
                break;
            case grid::grid::Status::FakeErr:
                osf<<"FakeErr "<<m.val<<' ';
                break;
            case grid::grid::Status::SET:
                osf<<"SET "<<m.val<<' ';
                break;
            case grid::grid::Status::UNCERTAIN:
                osf<<"UNCERTAIN "<<0<<' ';
                break;
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
    isf>>eraseNum;
    if(strtmp=="bronze"){
        level=Level::bronze;
    }
    else if(strtmp=="diamond"){
        level=Level::diamond;
    }   
    else if(strtmp=="master"){
        level=Level::master;
    }
    else if(strtmp=="gold"){
        level=Level::gold;
    }
    std::string strt;
    for(int i=0;i!=81;++i){
        isf>>strt;
        isf>>table[i].val;
        if(strt=="ERR"){
            table[i].status=grid::grid::Status::ERR;
        }
        else if(strt=="FakeErr"){
            table[i].status=grid::grid::Status::FakeErr;
        }
        else if(strt=="INITED"){
            table[i].status=grid::grid::Status::INITED;
        }
        else if(strt=="SET"){
            table[i].status=grid::grid::Status::SET;
        }
        else if(strt=="UNCERTAIN"){
            table[i].status=grid::grid::Status::UNCERTAIN;
        }
    }
    isf.close();
    return 1;
}
void game::setCheckChange(){
   if(table[curpos.first*9+curpos.second].val==0){
       table[curpos.first*9+curpos.second].status=grid::grid::Status::UNCERTAIN;
       if(setVec.find(std::make_pair(curpos.first,curpos.second))!=setVec.end()){
           setVec.erase(std::make_pair(curpos.first,curpos.second));
       }
   }
   else{
       table[curpos.first*9+curpos.second].status=grid::grid::Status::SET;
       if(setVec.find(std::make_pair(curpos.first,curpos.second))==setVec.end()){
           setVec.insert(std::make_pair(curpos.first,curpos.second));
       }
   }
   for(auto &m:table){
       if(m.status==grid::grid::Status::ERR){
           m.status=grid::grid::Status::SET;
       }
       if(m.status==grid::grid::Status::FakeErr){
           m.status=grid::grid::Status::INITED;
       }
   }
   for(auto pairPos:setVec){
       setCheckChange(pairPos);
   }
}

void game::setCheckChange(std::pair<int,int>pos){
    int i=pos.first;
    int j=pos.second;
    int val=table[i*9+j].val;
    for(int k=0;k!=9;++k){
        if(table[i*9+k].val==val&&k!=j){
            status=Status::ERROR;
            table[i*9+j].status=grid::grid::Status::ERR;
            if(table[i*9+k].status!=grid::grid::Status::ERR&&table[i*9+k].status!=grid::grid::Status::FakeErr){
                if(table[i*9+k].status==grid::grid::Status::INITED){
                    table[i*9+k].status=grid::grid::Status::FakeErr;
                }
                else {
                    table[i*9+k].status=grid::grid::Status::ERR;
                }
            }
        }
        if(table[k*9+j].val==val&&i!=k){
            status=Status::ERROR;
            table[i*9+j].status=grid::grid::Status::ERR;
            if(table[k*9+j].status!=grid::grid::Status::ERR&&table[k*9+j].status!=grid::grid::Status::FakeErr){
                if(table[k*9+j].status==grid::grid::Status::INITED){
                    table[k*9+j].status=grid::grid::Status::FakeErr;
                }
                else {
                    table[k*9+j].status==grid::grid::Status::ERR;
                }
            }
        }
    }
    i/=3;
    j/=3;
    for(int m=i*3;m!=i*3+3;++m){
        for(int n=j*3;n!=j*3+3;++n){
            if(table[m*9+n].val==val&&(m!=pos.first||n!=pos.second)){
                status=Status::ERROR;
                table[pos.first*9+pos.second].status=grid::grid::Status::ERR;
                if(table[m*9+n].status!=grid::grid::Status::ERR&&table[m*9+n].status!=grid::grid::Status::FakeErr){
                if(table[m*9+n].status==grid::grid::Status::INITED){
                    table[m*9+n].status=grid::grid::Status::FakeErr;
                }
                else {
                    table[m*9+n].status==grid::grid::Status::ERR;
                }
            }
            }
        }
    }
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
                table[i*9+j]=table[1*9+j+3];
            else if(i==1)
                table[i*9+j]=table[2*9+j+3];
            else if(i==2)
                table[i*9+j]=table[j+3];
        }
    }
    for(int i=0;i!=3;++i){
        for(int j=6;j!=9;++j){
            if(i==0)
                table[i*9+j]=table[2*9+j-3];
            else if(i==1)
                table[i*9+j]=table[j-3];
            else if(i==2)
                table[i*9+j]=table[1*9+j-3];
        }
    }
    for(int i=6;i!=9;++i){
        for(int j=0;j!=3;++j){
            if(i==6)
                table[i*9+j]=table[7*9+j+3];
            else if(i==7)
                table[i*9+j]=table[8*9+j+3];
            else if(i==8)
                table[i*9+j]=table[6*9+j+3];
        }
    }
    for(int i=6;i!=9;++i){
        for(int j=6;j!=9;++j){
            if(i==6)
                table[i*9+j]=table[8*9+j-3];
            else if(i==7)
                table[i*9+j]=table[6*9+j-3];
            else if(i==8)
                table[i*9+j]=table[7*9+j-3];
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
        for(int j=3;j!=6;++j){
            if(j==3)
                table[i*9+j]=table[(i-3)*9+5];
            else if(j==4)
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
void game::eraseGrid(){
    srand((int)time(0));
    for( int i=0;i!=eraseNum;++i){
        int k=rand()%81;
        while(table[k].status==grid::grid::Status::UNCERTAIN){
            k=rand()%81;
        }
        table[k].status=grid::grid::Status::UNCERTAIN;
        table[k].val=0;
    }
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

void game::undo(){
    auto p=cmdVec.back();
    cmdVec.pop_back();
    int index=p->pos.first*9+p->pos.second;
    table[index].val=p->preVal;
    curpos.first=p->pos.first;
    curpos.second=p->pos.second;
    setCheckChange();
}

bool game::checkFinish(){
    for(auto m:table){
        if(m.status!=grid::grid::Status::INITED&&m.status!=grid::grid::Status::SET){
            return 0;
        }
    }
    return 1;
}
        }//namespace game;
    }//namespace sudoku 

