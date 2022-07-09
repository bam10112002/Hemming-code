#include "../include/hamming.h"

Hamming::Hamming(int _massiveSize) : hammingArray(GetAdditionalBits(_massiveSize))
{
    // hammingArray = std::vector<u8>(static_cast<int>(std::ceil(GetAdditionalBits(_massiveSize)/8.0)));
    massiveSize = _massiveSize;
    // hammingArray.HammingSize() = GetAdditionalBits(massiveSize);
}
Hamming::Hamming(const Hamming& forCopy) : hammingArray(forCopy.hammingArray)
{
    massiveSize = forCopy.massiveSize;
    // hammingArray.HammingSize() = GetAdditionalBits(massiveSize);
    // hammingArray = forCopy.hammingArray;
    // hammingArray = new u8[static_cast<int>(std::ceil(GetAdditionalBits(massiveSize)/8.0))];
    // for (int i = 0; i < static_cast<int>(std::ceil(GetAdditionalBits(massiveSize)/8.0)); i++)
    // {
    //     hammingArray[i] = forCopy.hammingArray[i];
    // }
}
bool Hamming::operator==(const Hamming& right)
{
    for (int i = 1; i < hammingArray.HammingSize(); i *= 2)
    {
        if (this->hammingArray.get(i-1) != right.hammingArray.get(i-1))
        {
            return false;
        }
    }
    return true;
}
std::ostream& operator << (std::ostream &os, const Hamming &hm)
{
    // for (auto& obj : hm.hammingArray)
    // {
    //     // os.write((char*)&obj, sizeof(obj));
    //     int iVal;
    //     os.write((char*)iVal, sizeof(iVal));

    // }

    os << endl;
    for (int i = 0; i < hm.hammingArray.HammingSize(); i++)
    {
        os << " " << hm.hammingArray.get(i);
    }
    return os;
}
std::istream& operator >> (std::istream& in, Hamming& hm)
{
    // for (int i = 0; i < static_cast<int>(std::ceil(hm.hammingArray.HammingSize()/8.0)); i++)
    // {
    //     in.read((char*)&(hm.hammingArray[i]), sizeof(hm.hammingArray[i]));
    // }
    
    for (int i = 0; i < hm.hammingArray.HammingSize(); i++)
    {
        int val;
        in >> val;
        hm.hammingArray.set(i, val);
    }
    // hm.binaryPrint();

    return in;
}

int Hamming::GetAdditionalBits(int massiveSize)
{
    int n = std::log2(massiveSize);
    return massiveSize + n + 1;
}
void Hamming::binaryPrint()const 
{
    // std::cout << "hammingArray.HammingSize() = "<< hammingArray.HammingSize() << std::endl; 
    for (int i = 0; i < hammingArray.HammingSize(); i++)
    {
        if (i%8 == 0 && i != 0)
            std::cout << ": ";
        std::cout << hammingArray.get(i) << " ";
    }
    std::cout << std::endl;
}
void Hamming::setArr(const std::vector<u8>& array)
{
    int degree_2 = 1, old_pos = 0;
    for (int i = 0; i < hammingArray.HammingSize(); i++)
    {
        if (i + 1 == degree_2)
        {
            hammingArray.set(i,0);
            degree_2 *= 2;
        }
        else
        {
            int charInd = old_pos/(sizeof(u8)*8);
            hammingArray.set(i, (array[charInd] & (128 >> old_pos % (sizeof(u8)*8))));
            old_pos++;
        }
    }
    CalckHemmingBits();
}
std::vector<u8> Hamming::getArr()
{
    int degree_2 = 1, old_pos = 0;
    u8 ch = 0;
    std::vector<u8> vec;
    for (int i = 0; i < hammingArray.HammingSize(); i++)
    {
        if (i + 1 == degree_2)
        {
            degree_2 *= 2;
        }
        else
        {
            if (hammingArray.get(i))
                ch |=  (128 >> old_pos);
               
            old_pos++;
            if (old_pos == 8)
            {
                vec.push_back(ch);
                ch = 0;
                old_pos=0;
            }
            
        }
    }
    // std::cout << std::endl;
    return vec;
}
void Hamming::CalckHemmingBits()
{
    for (int i = 1; i < hammingArray.HammingSize(); i *= 2)
    {
        hammingArray.set(i-1,0);
    }

    // this->binaryPrint();
    int degree_2 = 1, old_pos = 0;
    for (int i = 0; i < hammingArray.HammingSize(); i++)
    {
        if (i + 1 == degree_2)
        {
            // std::cout << "degree: " << degree_2 << "| ";
            int ind = degree_2-1;
            int sum = 0;
            while (ind < hammingArray.HammingSize())
            {
                for (int j = 0; j < degree_2; j++)
                {
                    if (ind >= hammingArray.HammingSize())
                        break;
                    
                    // std::cout << get(ind) << " ";
                    sum += hammingArray.get(ind);
                    sum = sum % 2;
                    ind++;
                }
                ind = ind + degree_2;
            }
            if (ind < hammingArray.HammingSize())
                hammingArray.set(i, sum);
            // std::cout << std::endl;
            degree_2 *= 2;
        }
    }
}
int Hamming::ChangeError()
{  
    Hamming oldHm(*this);
    this->CalckHemmingBits();
    int sum = 0;
    for (int i = 1; i < hammingArray.HammingSize(); i *= 2)
    {
        if (this->hammingArray.get(i-1) != oldHm.hammingArray.get(i-1))
        {
            sum += i;
        }
    }
    if (sum-1 != -1)
        this->hammingArray.inverse(sum-1);
    this->CalckHemmingBits();
    return sum-1;
}
