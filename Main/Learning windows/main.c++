#include "tileGrid.h++"
#include <iostream>
#include <algorithm>

std::ostream &operator<<(std::ostream &stream,  POINT point)
{
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}

int main()
{
    DeviceContextHandleId context = GetDC(NULL);

    POINT startPoint;
    POINT endPoint;
    
    while ( true )
    {
        if ( GetKeyState('T') & 0x8000 ) { GetCursorPos(&startPoint); std::cout << startPoint << std::endl; }

        if ( GetKeyState('Z') & 0x8000 ) { GetCursorPos(&startPoint); break; }
    }

    while ( true )
    {
        if ( !(GetKeyState('Z') & 0x8000) ) { GetCursorPos(&endPoint); break; }
    }

    std::cout << startPoint << ", " << endPoint << std::endl;

    // EASY -> 10, 8
    // MEDIUM -> 18, 14
    // HARD -> 24, 20
    int gridWidth; int gridHeight;
    std::string input;
    std::cout << "Width: "; std::cin >> input; gridWidth = std::stoi(input);
    std::cout << "Height: "; std::cin >> input; gridHeight = std::stoi(input);
    int screenWidth = ( endPoint.x - startPoint.x ); int screenHeight = ( endPoint.y - startPoint.y );
    float tileWidth = float(screenWidth) / gridWidth; float tileHeight = float(screenHeight) / gridHeight;

    // while (true)
    // {
    //     if ( GetKeyState('S') & 0x8000 ) break;
    //     for ( int yIndex = 0; yIndex < gridHeight; yIndex++ )
    //     {
    //         for ( int xIndex = 0; xIndex < gridWidth; xIndex++ )
    //         {
    //             POINT screenPosition = { startPoint.x + LONG((xIndex+0.5f)*tileWidth), startPoint.y + LONG((yIndex+0.5f)*tileHeight) };
    //
    //             Ellipse( context, screenPosition.x - tileWidth/3, screenPosition.y - tileHeight/3, screenPosition.x + tileWidth/3, screenPosition.y + tileHeight/3 );
    //         }
    //     }
    // }
    while ( true ) 
    {
        while ( true )
        {
            if ( GetKeyState(VK_F2) & 0x8000 ) { std::cout << "starting" << std::endl; break; }
        }

        while( true )
        {
            if ( GetKeyState(VK_F4) & 0x8000 ) break;

            TileGrid tileGrid = readScreen( context, startPoint, screenWidth, screenHeight, gridWidth, gridHeight );

            // for ( int yIndex = 0; yIndex < gridHeight; yIndex++ )
            // {
            //     for ( int xIndex = 0; xIndex < gridWidth; xIndex++ )
            //     {
            //         std::string string = " " + std::to_string( int(tileGrid[xIndex][yIndex]) ) + " ";
            //         if ( string.size() == 3 ) string += " ";
            //         std::cout << string;
            //     }
            //     std::cout << std::endl;
            // }
            // std::cout << std::endl;

            std::set<Move> moves;

            while ( true )
            {
                std::set<Move> tempMoves = getBestMoves( tileGrid, gridWidth, gridHeight );
                std::set<Move> newMoves;

                std::set_difference( tempMoves.begin(), tempMoves.end(), moves.begin(), moves.end(), std::inserter(newMoves, newMoves.end()) );

                if ( newMoves.size() == 0 )
                    break;

                moves.insert(newMoves.begin(), newMoves.end());
            }
            
            if ( moves.size() == 0 )
            {
                std::cout << "no move to play, ending" << std::endl;
                break;
            }

            for ( Move move: moves )
            {
                POINT screenPosition = { startPoint.x + LONG((move.position.x+0.5f)*tileWidth), startPoint.y + LONG((move.position.y+0.5f)*tileHeight) };
                move.position = screenPosition;

                playMove(move);
            }

            Sleep(750);
        }
        if ( GetKeyState(VK_F4) & 0x8000 ) break;
    }

    return 0;
}