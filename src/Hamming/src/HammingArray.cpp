#include "HammingArray.h"

HammingArray::HammingArray(size_t size)
{
    hammingArray = std::vector<u8>(static_cast<int>(std::ceil(size/8.0)));
    hammingSize = size;
    // cout << hammingSize;
}

/**
 * @brief  Устанавливает бит в массив
 * 
 * @param ind индекс бита
 * @param val значение бита
 * @throw std::out_of_range исключение выхода за границы
 */
void HammingArray::set(int ind, int val)
{
    if (ind < 0 || ind > hammingSize)
    {
        throw std::out_of_range("set::index out of range");
    }
    int charInd = ind/(sizeof(u8)*8);

    if (val)
        hammingArray[charInd] |=  (128 >> ind % (sizeof(u8)*8));
    else 
        hammingArray[charInd] &= ~(128 >> ind % (sizeof(u8)*8));
}

/**
 * @brief Получает значение бита из массива
 * 
 * @param ind индекс бита
 * @return int значение бита
 * @throw std::out_of_range исключение выхода за границы
 */
int HammingArray::get(int ind) const
{    
    if (ind < 0 || ind > hammingSize)
       throw std::out_of_range("get::index out of range");
 
    int charInd = ind/(sizeof(u8)*8);

    if (hammingArray[charInd] & (128 >> ind % (sizeof(u8)*8)))
        return 1;
    return 0;
}

/**
 * @brief инверсирует бит в массиве
 * 
 * @param ind индекс бита
 * @throw std::out_of_range исключение выхода за границы
 */
void HammingArray::inverse(int ind)
{
    if (ind < 0 || ind > hammingSize)
        throw std::out_of_range("inverse::index out of range");

    int charInd = ind/(sizeof(u8)*8);
    hammingArray[charInd] ^= (128 >> ind % (sizeof(u8)*8));

}

unsigned int HammingArray::HammingSize()const
{
    return hammingSize;
}
