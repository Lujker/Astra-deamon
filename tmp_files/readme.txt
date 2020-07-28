Данная программа является службой для автозапуска сторонних программ. Основные настройки программы находятся в файле settings.ini: 
(путь к файлу блокировки, путь к файлу логов, путь к файлу с абсолютными путями для запуска программ (к исполняемым файлам).      
Служба работает через систему systemd и имеет unit файл который должен быть расположен по пути: /etc/systemd/system/demon.service 
Файл с путями к исполняемым фалам должен нахоидся по пути: /etc/DemPath.conf (по одному пути на строку, путь заканчивать ';')     
Файл логов расположен по пути: /var/log/DemLog.log.                                                                               
При ошибках запуска или его невозможности необходимо создать такие файлы (и заполнить в случае DemPath и settings)                
Также можно настроить logrotate для данной службы путем создания или редактирования фалйа demlogctl по пути /etc/logrotate.d/     
Ниже приведен пример содержания каждого фала и содержание фала demon.service...                                                   
/////////////////////////////////////////////////////////
/etc/DemPath.conf:
/home/user/Qt_prog/build-ProcPlug-Desktop-Debug/ProcPlug;
/home/user/C_Prog/Test_ReadFile/main;
/////////////////////////////////////////////////////////
/etc/settings.ini:
pid_file_path=/tmp/my_demon.pid;
config_file_path=/etc/DemPath.conf;
log_file_path=/var/log/DemLog.log;
/////////////////////////////////////////////////////////
точное содержание demon.service: 
[Unit]
Description = Exec proc from cfg files

[Service]
Type=forking
ExecStart=sudo /home/user/Qt_prog/build-Demon-Desktop-Debug/Demon -d &
ExecStop=sudo /usr/bin/killall Demon
Restart=sudo /usr/bin/killall -s -12 Demon
PIDFile=/tmp/my_demon.pid

[Install]
WantedBy=multi-user.target
/////////////////////////////////////////////////////////
автозапуск службы можно включить и отключить после установки файла по вышеуказанному пути и выполнения команд:
systemctl enable demon.service - включение
systemctl disable demon.service - отключение
systemctl is-enabled unit_name - проверка на включение/отключение
/////////////////////////////////////////////////////////
/etc/logrotate.d/demlogctl:

/var/log/DemLog.log{
    daily
    rotate 3
    size 10M
    compress
    delaycompress
    copytruncate
}
/////////////////////////////////////////////////////////
