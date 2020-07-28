#ifndef PIDFILE_H
#define PIDFILE_H

#include <string>
#include <iostream>
#include <ios>
#include <cstdio>
#include <cstring>
#include <unistd.h>

#include <sys/signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>

class Pid_file{
public:
    Pid_file()=default;
    ~Pid_file();
    Pid_file(const std::string& path);
    int set_path(const std::string& path);
    const std::string& get_path();
    int getPidfilehendler() const;

private:
    std::string path;//abs path to pid file
    int pidfilehendler;
};
#endif // PIDFILE_H
