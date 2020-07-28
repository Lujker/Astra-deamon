#ifndef DEMON_H
#define DEMON_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <ios>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>

#include <sys/signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include "pidfile.h"


/* "/var/run/my_demon.pid"*/
//#define PID_FILE "/tmp/my_demon.pid"
//#define CFG_FILE "/home/user/Qt_prog/etc/Proc_path.cfg"
//#define LOG_FILE "/home/user/Qt_prog/Log/DemonLog.txt"
//const for error label
#define FAIL_FORK 1
#define FAIL_EXEC 2
//const for status lable
#define CLS 2
#define STR 1
class Pid_file;
class Demon;


void MonitorProc(Demon& dem); //Demon control in background mode
bool WriteLog(const std::string& msg, const std::string& Log_file); //Write log info in LOG_FILE
bool ParsPath(std::string str, std::vector<std::string>& vec_path);


class Demon
{
public:
     Demon()=default;
     Demon(const std::string& set_file);
    ~Demon();
//func's demon
     bool start();
     bool stop();
     bool restart();
     bool ReadSetting(const char *FileName); //read all settings from SET_FILE
     bool readpath();
     bool del_pid(int pid);
     std::string getLog_file() const;

private:
     std::vector<int>                pid_vec; //arr with pid number of exec proc what startin in demon::start()
    std::vector<std::string> input_user_path; //vector with path of exec files from user cfg
    int status;
    //Path to main file of using on this prog
    Pid_file*        pid;
    std::string set_file; //setting file
    std::string cfg_file; //config file with prog's path
    std::string log_file;
};


#endif // DEMON_H
