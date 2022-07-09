#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>
#include "src/Hamming/include/hamming.h"
namespace fs = std::filesystem;


void coder(std::string inputFileName, std::string outFileName, int blockSize);

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

    coder(inName, outName, bits);

    return 0;
}

void coder(std::string inputFileName, std::string outFileName, int blockSize)
{
    std::ifstream input(inputFileName);
    std::ofstream out(outFileName);
    if (!input || !out)
    {
        cout << "ERROR open file in coder" << endl;
        return;
    }

    bool endFile = false;
    while (!endFile)
    {
        std::vector<u8> arr((blockSize/8)+1);
        Hamming hm(blockSize);
        for (int i = 0 ; i < blockSize/8; i++)
        {
            char ch;
            if(input.get(ch))
            {
                arr[i] = ch;
            }
            else
            {   if (i == 0)
                {
                    input.close();
                    out.close(); 
                    return;
                }
                for (int j = i; j < blockSize/8; j++)
                    arr[j] = 0;
                endFile = !endFile;
                break;
            }
        }
        hm.setArr(arr);
        out << hm;
    }
    input.close();
    out.close();
}
