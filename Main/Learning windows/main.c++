#include "tileGrid.h++"
#include <iostream>

int main()
{
    DeviceContextHandleId context = GetDC(NULL);

    POINT startPoint;
    POINT endPoint;
    
    while ( true )
    {
        if ( GetKeyState('Z') & 0x8000 ) { GetCursorPos(&startPoint); break; }
    }

    while ( true )
    {
        if ( !(GetKeyState('Z') & 0x8000) ) { GetCursorPos(&endPoint); break; }
    }

    std::cout << "doing things" << std::endl;

    int gridWidth = 10; int gridHeight = 8;
    TileGrid tileGrid = readScreen( context, startPoint, endPoint, gridWidth, gridHeight );

    for ( int yIndex = 0; yIndex < gridHeight; yIndex++ )
    {
        for ( int xIndex = 0; xIndex < gridWidth; xIndex++ )
        {
            std::string string = " " + std::to_string( int(tileGrid[xIndex][yIndex]) ) + " ";
            if ( string.size() == 3 ) string += " ";
            std::cout << string;
        }
        std::cout << std::endl;
    }

    return 0;
}