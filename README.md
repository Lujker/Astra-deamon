# Astra-demon
Astra-linux exec demon (systemd)
if you are interested in getting information about a project or an extended readme file write: vladzzp111@gmail.com

This program is a service for the autorun of third-party programs. The main program settings are located in the settings.ini file:
(path to the lock file, path to the log file, path to the file with absolute paths for launching programs (to executable files).
The service runs through the systemd system and has a unit file that should be located along the path: /etc/systemd/system/demon.service
The file with the paths to the executable files must be located along the path: /etc/DemPath.conf (one path per line, the path ends with ';')
The log file is located along the path: /var/log/DemLog.log.
In case of startup errors or its impossibility, you must create such files (and fill in in the case of DemPath and settings)
@@@ If you are interested in an example of the content of the files, write to me.
