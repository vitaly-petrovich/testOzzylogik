#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include "MessageSerializer.h"

unsigned short randomValue();
unsigned short randomSize();
void generateRandomArray(std::vector<uint16_t>& array);
void prepareArray(std::vector<uint16_t>& array);
void printOut(std::vector<uint8_t>& array);
void printIn(std::vector<uint16_t>& array);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    std::vector<uint16_t> array;
    std::vector<uint8_t> msg;

    prepareArray(array);

    if(!MessageSerializer::serialize(array, msg))
        return 1;

    msg.resize(msg.size()-1);   // remove terminal byte

    printIn(array);
    printOut(msg);

    return 0;
}

void prepareArray(std::vector<uint16_t>& array)
{
    generateRandomArray(array);
    std::sort(array.begin(), array.end());
    array.erase(unique(array.begin(), array.end()), array.end());   //erase duplicates
}

void generateRandomArray(std::vector<uint16_t>& array)
{
    uint16_t len = randomSize();

    array.resize(len);
    for(std::vector<uint16_t>::iterator it = array.begin();
        it != array.end();
        it++)
        *it = randomValue();
}

unsigned short randomValue()
{
    return rand()%5001;
}

unsigned short randomSize()
{
    return rand()%4995+5;
}

void printOut(std::vector<uint8_t>& array)
{
    std::cout << "message: ";

    for(std::vector<uint8_t>::iterator it = array.begin();
        it != array.end();
        it++)
        std::cout << static_cast<uint16_t>(*it) << " ";

    std::cout << "\n";
}

void printIn(std::vector<uint16_t>& array)
{
    std::cout << "array: ";

    for(std::vector<uint16_t>::iterator it = array.begin();
        it != array.end();
        it++)
        std::cout << *it << " ";

    std::cout << "\n";
}
