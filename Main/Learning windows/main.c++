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

    // EASY -> 10, 8
    // MEDIUM -> 18, 14
    // HARD -> 
    int gridWidth = 18; int gridHeight = 14;
    int screenWidth = ( endPoint.x - startPoint.x ); int screenHeight = ( endPoint.y - startPoint.y ); 
    float tileWidth = float(screenWidth) / gridWidth; float tileHeight = float(screenHeight) / gridHeight;

    while( true )
    {
        if ( GetKeyState('K') & 0x8000 ) break;

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
        std::cout << std::endl;

        std::set<Move> moves = getBestMoves( tileGrid, gridWidth, gridHeight );
        
        if ( moves.size() == 0 )
            break;

        for ( Move move: moves )
        {
            POINT screenPosition = { startPoint.x + LONG((move.position.x+0.5f)*tileWidth), startPoint.y + LONG((move.position.y+0.5f)*tileHeight) };
            move.position = screenPosition;

            playMove(move);
        }

        Sleep(4000);
    }

    return 0;
}