#include "HashTable_new.h"
#include <iostream>

int main()
{
    HashTable<int> hashtb = HashTable<int>();
    std::cout << hashtb.Insert(4) << std::endl;
    std::cout << hashtb << std::endl;
    try
    {
        std::cout << hashtb.Insert(1) << std::endl;
        std::cout << hashtb.Insert(8) << std::endl;
        std::cout << hashtb.Insert(6) << std::endl;
        std::cout << hashtb.Insert(2) << std::endl;
        std::cout << hashtb.Insert(12) << std::endl;
        std::cout << hashtb.Insert(1255) << std::endl;
        std::cout << hashtb.Insert(55) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}