#include "json.h++"
#include "file.h++"

int main()
{
    Json words = parseFile( "Wordle/words.json" );
    
    std::cout << words["words"][0];

    return 0;
}