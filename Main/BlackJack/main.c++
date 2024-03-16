#include <deck.h++>
#include <iostream>

int main()
{
    Deck deck;

    std::cout << std::string( deck ) << std::endl;

    deck.shuffle();

    std::cout << std::string( deck ) << std::endl;

    return 0;
}