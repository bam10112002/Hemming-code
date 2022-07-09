#include <stdexcept>
#include <vector>
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
using u8 = unsigned char;

/**
 * @brief Хранит массив битов в массиве типа unsigned char
 * @throws std::out_of_range Исключение выхода за границы при индексировании
 */
class HammingArray
{
private:
    std::vector<u8> hammingArray;
    unsigned int hammingSize;

public:
    HammingArray(size_t size);
    void set(int ind, int val);
    int get(int ind) const;
    void inverse(int ind);
    unsigned int HammingSize() const;
};