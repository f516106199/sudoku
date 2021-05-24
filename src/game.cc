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
            table[i].status==grid::grid::Status::UNCERTAIN;
        }
    }
    isf.close();
    return 1;
}
void game::setCheckChange(const errinfo& res){
    int i=res.p1.first;
    int j=res.p1.second;
    int m=res.p2.first;
    int n=res.p2.second;
    table[i*9+j].status=grid::grid::Status::ERR;
        if(table[m*9+n].status!=grid::grid::Status::INITED&&table[m*9+n].status!=grid::grid::Status::FakeErr)
            table[m*9+n].status=grid::grid::Status::ERR;
        else
            table[m*9+n].status=grid::grid::Status::FakeErr;
}

game::errinfo game::check(){
    int i=curpos.first;
    int j=curpos.second;
    int val=table[i*9+j].val;
    for(int k=0;k!=9;++k){
        if(table[i*9+k].val==val&&k!=j){
            status=Status::ERROR;
            return errinfo(1,i,j,i,k);
        }
        if(table[k*9+j].val==val&&k!=i){
            status=Status::ERROR;
            return errinfo(1,i,j,k,j);
        }   
    }
    i/=3;
    j/=3;
    for(int m=i;m!=i+3;++m){
        for(int n=j;n!=j+3;++j){
            if(table[m*9+n].val==val&&(m!=curpos.first||n!=curpos.second)){
                status=Status::ERROR;
                return errinfo(1,i,j,m,n);
            }
        }
    }
    return errinfo(0,0,0,0,0);
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
        for(int j=3;j!=6;++j){
            if(j==3)
                table[i*9+j]=table[(i-3*9+5)];
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
    if(p->kind==command::command::Kind::OK){
        command::Ocommand* p1=reinterpret_cast<command::Ocommand*>(p);
        int index=p1->pos.first*9+p1->pos.second;
        table[index].val=p1->preVal;
        table[index].status=p1->preS;
    }
    else{
        command::Bcommand*p2=reinterpret_cast<command::Bcommand*>(p);
        int index=p2->Opos.first*9+p2->Opos.second;
        table[index].setVal(p2->preVal,p2->preS);
        index=p2->Opos.first*9+p2->Opos.second;
        table[index].status=p2->OpreS;
    }
}
        }//namespace game;
    }//namespace sudoku 