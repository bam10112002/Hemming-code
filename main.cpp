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

int main()
{
    // testCheckError();

    coder  ("./datasets/in.txt", "./datasets/coded/text1.txt", 16);
    coder  ("./datasets/in.txt", "./datasets/coded/text2.txt", 16);
    // decoder("./datasets/out.txt", "./datasets/rezult.txt", 30);
    // demon("./datasets/coded/");
    
}

void testCheckError()
{
    std::vector<u8> vec = {'b', 'a'};
    Hamming hm(16);
    hm.setArr(vec);
    cout << "Base Hamming massive : ";
    hm.binaryPrint();
    // hm.set(10,0);
    cout << "Broken massive       : ";
    hm.binaryPrint();
    int errInd = hm.ChangeError();
    cout << "Changed massive      : ";
    hm.binaryPrint();
    cout << "Error detected in ind = " << errInd << endl;
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
void decoder(std::string inputFileName, std::string outFileName, int blockSize)
{
    std::ifstream input(inputFileName);
    std::ofstream out(outFileName);
    if (!input || !out)
    {
        cout << "ERROR open file in decoder\n";
        return;
    }
    Hamming hm(blockSize);
    while (!input.eof())
    {
        input >> hm;
        int err = hm.ChangeError();
        
        if (err != -1)
            cout << "ERROR in " << err << "\t" << endl;
        std::vector<u8> vec;
        vec = hm.getArr();
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i])
                out << char(vec[i]);
            if (vec[i] && err != -1)
                cout << char(vec[i]);
        }
    }
    input.close();
    out.close();
}
void demon(std::string dirName)
{
    std::ifstream input;
    for (const auto& entry : fs::directory_iterator(dirName))
    {
        Hamming hm(16);
        input.open(entry.path());
        if (!input)
        {
            cout << "ERROR open file in demon\n";
            return;
        }
        while (!(input.eof()))
        {
            input >> hm;
            int err = hm.ChangeError();
            if (err != -1)
                cout << "Error in file" << entry.path() << "ERROR in " << err << "\t" << endl;
        }
        input.close();
    }
}
