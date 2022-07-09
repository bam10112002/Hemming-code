#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>
#include "src/Hamming/include/hamming.h"
namespace fs = std::filesystem;


void demon(std::string, std::ofstream&);
void copyFile(std::string, std::string);

int main(int argc, char* argv[])
{
    int bits, deley;
    std::string dirName, logName;

    if (argc != 9)
    {
        cout << "argc is not valid, obtained value = " << argc << endl;
        return -1;
    }

    for (int i = 1; i < 9; i += 2)
    {
        if (std::string(argv[i]) == "-n")
            bits = std::stoi(argv[i+1]);

        else if (std::string(argv[i]) == "-d")
            dirName = std::string(argv[i+1]);

        else if (std::string(argv[i]) == "-l")
            logName = std::string(argv[i+1]);

        else if (std::string(argv[i]) == "-t")
            deley = std::stoi(argv[i+1]);
            
        else 
            std::cerr << "undefined key: " << argv[i] <<  endl;  
    }

    pid_t parpid, sid;
    
    parpid = fork(); //создаем дочерний процесс
    if(parpid < 0)
    {
        exit(1);
    } 
    else if(parpid != 0)
    {
        exit(0);
    } 
   
    sid = setsid();//генерируем уникальный индекс процесса
    if(sid < 0) {
        exit(1);
    }

    close(STDIN_FILENO);//закрываем доступ к стандартным потокам ввода-вывода
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    std::ofstream of(logName);
    of << "Demon Started" << endl;
    for (int i = 0; i < 10; i++)
    {
        // cout << "demon iter" << endl;
        demon(dirName, of);
        sleep(deley);
    }
    
    return 0;
}

void copyFile(std::string out, std::string in)
{
    std::string cp = "cp " + out + " " + in;
    system(cp.c_str());
}

void demon(std::string dirName, std::ofstream& logStream)
{
    std::ifstream input;
    for (const auto& entry : fs::directory_iterator(dirName))
    {
        Hamming hm(16);
        input.open(entry.path());
        std::ofstream tmp("./datasets/tmp");
       
        if (!logStream)
        {
            cout << "ERROR open log file\n";
            return;
        }
        if (!input)
        {
            cout << "ERROR open file in demon\n";
            return;
        }
        
        int err, count = 0;
        while (!(input.eof()))
        {
            input >> hm;
            err = hm.ChangeError();
            if (err != -1)
                count++;
            tmp << hm;
        }
        if (count)
            logStream << "Detected " << count << " errors";
        else
            logStream << "Error undefind";
        logStream << ", file name " << entry.path() << endl;
        input.close();
        tmp.close();

        if (count) 
            copyFile("./datasets/tmp", entry.path());
    }
}
