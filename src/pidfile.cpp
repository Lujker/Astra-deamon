#include "../incl/pidfile.h"

Pid_file::Pid_file(const std::string &path)
{
   this->path=path;
   set_path(path);
}
//open and block pid file
int Pid_file::set_path(const std::string &path)
{
    char str[10];
    this->path=path;
    this->pidfilehendler = open(path.data(), O_WRONLY|O_CREAT, S_IXUSR);

if (pidfilehendler == -1 )
    {
        /* Couldn't open lock file */
//       WriteLog("Failed open pid file");
        exit(1);
    }
/* Try to lock file */
    if (lockf(pidfilehendler,F_TLOCK,0) == -1)
    {
        /* Couldn't get lock on lock file */
//        WriteLog("Failed lock pid file");
        return pidfilehendler;
    }

    /* Get and format PID */
    sprintf(str,"%d\n",getpid());

    /* write pid to lockfile */
    write(pidfilehendler, str, strlen(str));

//    WriteLog("Get and write pid on file");

    return pidfilehendler;
}

const std::string &Pid_file::get_path()
{
return this->path;
}

int Pid_file::getPidfilehendler() const
{
    return pidfilehendler;
}

Pid_file::~Pid_file()
{
    if(pidfilehendler!=-1&&pidfilehendler!=0){
        if (lockf(pidfilehendler,F_ULOCK,0) == -1)
        {
            /* Couldn't get lock on lock file */
//            WriteLog("Failed unlock pid file");
        }
        close(pidfilehendler);
    }
    unlink(path.data());
//     WriteLog("Unlock and del file");
}
