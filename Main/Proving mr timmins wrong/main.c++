#include <vector>
#include <iostream>
#include "time.h++"

template<std::size_t size>
std::array<int,size> reverseTimmins( std::array<int,size> array )
{
    chronoNanoseconds startTime = timeNow();
    std::array<int,size> reversedArray;

    for ( int index = 0; index < size; index++ )
        reversedArray[size - index - 1] = array[index];

    chronoNanoseconds endTime = timeNow();

    std::cout << "Timmins: " << (endTime - startTime).count() << std::endl;
    return reversedArray;
}

template<std::size_t size>
std::array<int,size> reverse( std::array<int,size> array )
{
    chronoNanoseconds startTime = timeNow();
    int tmp = 0;

    for ( int index = 0; index < int( array.size() / 2 ); index++ )
    {
        tmp = array[index];
        array[index] = array[array.size() - index - 1];
        array[array.size() - index - 1] = tmp;
    }

    chronoNanoseconds endTime = timeNow();

    std::cout << "Me: " << (endTime - startTime).count() << std::endl;
    return array;
}

template<typename T,std::size_t size>
std::ostream& operator<< (std::ostream& stream, const std::array<T,size>& array)
{
    for ( const T &value: array )
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return stream;
}

int main()
{
    std::array<int,100000> array = {};

    for ( int index = 0; index < 100000; index++ )
    {
        array[index] = index;
    }

    reverseTimmins(array);
    reverse(array);
}