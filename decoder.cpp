#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>
#include "src/Hamming/include/hamming.h"
namespace fs = std::filesystem;


void coder  (std::string inputFileName, std::string outFileName, int blockSize);
void decoder(std::string inputFileName, std::string outFileName, int blockSize);
void testCheckError();
void demon(std::string dirName);
// void checkFile(std::string fileName);

int main(int argc, char* argv[])
{
    int bits;
    std::string inName, outName;
    if (argc != 7)
    {
        cout << "argc is not valid, obtained value = " << argc << endl;
        return -1;
    }
    for (int i = 1; i < 7; i += 2)
    {
        if (std::string(argv[i]) == "-n")
            bits = std::stoi(argv[i+1]);

        else if (std::string(argv[i]) == "-i")
            inName = std::string(argv[i+1]);

        else if (std::string(argv[i]) == "-o")
            outName = std::string(argv[i+1]);
            
        else 
            std::cerr << "undefined key: " << argv[i] <<  endl;  
    }

    decoder(inName, outName, bits);

    return 0;
}

void decoder(std::string inputFileName, std::string outFileName, int blockSize)
{
    std::fstream input(inputFileName);
    std::fstream out(outFileName);
    if (!input || !out)
    {
        cout << "ERROR open file in decoder\n";
        return;
    }
    Hamming hm(blockSize);
    char ch;
    while (!input.eof())
    {
        input >> hm;
        int err = hm.ChangeError();
        
        if (err != -1)
            cout << "ERROR in " << err << "\tchars:";
        std::vector<u8> vec;
        vec = hm.getArr();
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i])
                out << char(vec[i]);
            if (vec[i] && err != -1)
                cout << char(vec[i]); // Выводит сообщение об ошибке
        }
        if (err != -1)
            cout << endl;
        // cout << input.gcount() << endl;
    }
    input.close();
    out.close();
}
