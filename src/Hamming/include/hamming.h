#include <cmath>
#include <iostream>
#include "../src/HammingArray.h"


class Hamming
{
private:
    HammingArray hammingArray;
    unsigned int massiveSize;

    int GetAdditionalBits(int massiveSize);

public:
    Hamming(int massiveSize);
    Hamming(const Hamming& forCopy);
    bool operator==(const Hamming& right);
    friend std::istream& operator >> (std::istream& in, Hamming& hm);
    friend std::ostream& operator << (std::ostream &os, const Hamming &hm);
    
    void setArr(const std::vector<u8>& array);
    std::vector<u8> getArr();
    // std::vector<u8> getHemmingArr();
    void binaryPrint() const;
    int ChangeError();

    void CalckHemmingBits();
};