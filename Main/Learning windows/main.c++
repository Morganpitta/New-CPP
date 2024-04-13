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

    int gridWidth = 10; int gridHeight = 8;
    int screenWidth = ( endPoint.x - startPoint.x ); int screenHeight = ( endPoint.y - startPoint.y ); 

    TileGrid tileGrid = readScreen( context, startPoint, screenWidth, screenHeight, gridWidth, gridHeight );

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

    std::vector<POINT> points = getBestMove( tileGrid, gridWidth, gridHeight );
    
    float tileWidth = screenWidth / gridWidth;
    float tileHeight = screenHeight / gridHeight;

    while ( true )
    {
        for ( POINT point: points )
        {
            POINT screenPosition = { startPoint.x + (point.x+0.5f)*tileWidth, startPoint.y + (point.y+0.5f)*tileHeight };

            Ellipse( context, screenPosition.x - 5, screenPosition.y - 5, screenPosition.x + 5, screenPosition.y + 5 );
        }
    }

    return 0;
}