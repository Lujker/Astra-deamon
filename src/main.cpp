
/*
 *
 * */


#ifndef MAIN_DEM
#define MAIN_DEM

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>


#include "../incl/demon.h" //Demon class incl

//Arguments of check with run this prog
#define START "start"
#define STOP "stop"
#define RESTART "restart"
//CONST's
#define BUF_SIZE 4096
#define SET_FILE "/etc/DemSettings.ini"
int main(int argc, char *argv[])
{
    if(argc<2){
        std::cout<<"Usage ./Demon -d for demon or ./Demon -i for interactive console\n";
        exit(1);
    }
    if(strcmp(argv[1],"-d")==0){
        pid_t parpid;
///////////DEMON////////////////////////////////--setsid в <unistd.h>//////////
   if((parpid=fork())<0){                  //--здесь мы пытаемся создать дочерний процесс главного процесса (масло масляное в прямом смысле)
       std::cout<<"\ncan't fork";          //--точную копию исполняемой программы
        exit(1);                           //--если нам по какой-либо причине это сделать не удается выходим с ошибкой.
   }                                       //
   else if (parpid!=0) exit(0);     //--если дочерний процесс уже существует --генерируем немедленный выход из программы(зачем нам еще одна копия программы)
    chdir("/"); umask(0); setsid();        //--перевод нашего дочернего процесса в новую сесию
    //////////////////////////////////////////////////////////////////////////////
    /// block with capture soc

    Demon dem(SET_FILE);

    // close all diskriptors on IO and err
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
     //функция по открытию всех exec в новых fork и перехвата сигнала в потоке предке
    MonitorProc(dem);
    WriteLog("EXIT FROM MONITOR",dem.getLog_file());
}

////////////////////////intreactiv_console/////////////////////////////////////
    else if(strcmp(argv[1],"-i")==0){
        char buf[BUF_SIZE];
        chdir("/");
        Demon dem(SET_FILE);
        if(!dem.readpath()){
            std::cout<<"Cant open cfg file with proc path/n";
            exit(1);
        }

    while(fgets(buf,BUF_SIZE,stdin)){ //read comands from standart console input (terminal)

        if(buf[strlen(buf)-1]=='\n') buf[strlen(buf)-1]=0;
//runing the demon and read from prog-path file, exec new process
       if(strcmp(buf,START)==0) {           
           if(dem.start()) std::cout<<"START!"<<std::endl;
           else std::cout<<"Starting error"<<std::endl;
       }
       //stop, close another proc, read confg file and start again
        if(strcmp(buf,RESTART)==0) {
            if(dem.start()) std::cout<<"RESTART!"<<std::endl;
            else std::cout<<"restarting error"<<std::endl;
        }
//kill all proc on vector<Process*> in demon
        if(strcmp(buf,STOP)==0) {
            if(dem.stop()) std::cout<<"STOP!"<<std::endl;
            else std::cout<<"stoping error"<<std::endl;
        }
   }
}
///////////////////////////////////////////////////////////////////////////////
    else{
        std::cout<<"Usage ./Demon -d for demon or ./Demon -i for interactive console\n";
        exit(1);
    }

    return 0;
}

#endif //MAIN_DEMON
