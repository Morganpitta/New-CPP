#include <windows.h>
#include <iostream>
#include <vector>

typedef HWND WindowHandleId;
typedef HDC DeviceContextHandleId;

enum Tile
{
    UnknownTile,
    OneTile,
    TwoTile,
    ThreeTile,
    FourTile,
    FiveTile,
    SixTile,
    SevenTile,
    EightTile,
    FlagTile,
    EmptyTile
};

const COLORREF FlagColor   = 0x0736f2;
const COLORREF Tile1Color  = 0xd27619;
const COLORREF Tile2Color  = 0x8cb6aa;
const COLORREF Tile3Color  = 0x2f2fd3;
const COLORREF Tile4Color  = 0xa21f7b;
const COLORREF Empty1Color = 0x77ddb9;
const COLORREF Empty2Color = 0x7de1bf;

Tile colourToTile( COLORREF colour )
{
    switch ( colour )
    {
        case FlagColor: return FlagTile;
        case Empty1Color: return EmptyTile;
        case Empty2Color: return EmptyTile;
        case Tile1Color: return OneTile;
        case Tile2Color: return TwoTile;
        case Tile3Color: return ThreeTile;
        case Tile4Color: return FourTile;
        default: return UnknownTile;
    }
}

typedef std::vector<std::vector<Tile>> TileGrid;

TileGrid readScreen( DeviceContextHandleId context, POINT topLeft, POINT bottomRight, int width, int height )
{
    POINT currentTileCenter; 
    COLORREF currentTileColour; 
    TileGrid grid; grid.resize( width, std::vector<Tile>(height) );
    int tileWidth = ( bottomRight.x - topLeft.x ) / width;
    int tileHeight = ( bottomRight.y - topLeft.y ) / height;
    for ( int xIndex = 0; xIndex < width; xIndex++ )
    {
        for ( int yIndex = 0; yIndex < height; yIndex++ )
        {
            currentTileCenter = { topLeft.x + LONG((xIndex+0.5f)*tileWidth), topLeft.y + LONG((yIndex+0.5f)*tileHeight) };
            currentTileColour = GetPixel(context,currentTileCenter.x,currentTileCenter.y);
            grid[xIndex][yIndex] = colourToTile( currentTileColour );
        }
    }

    return grid;
}

int main()
{
    DeviceContextHandleId context = GetDC(NULL);

    POINT point;
    COLORREF color;
    while ( true )
    {
        if ( GetKeyState('Z') & 0x8000 )
        {
            GetCursorPos(&point);
            color = GetPixel(context,point.x,point.y);
            std::cout << point.x << ", " << point.y << ": " << std::hex << int(color) << std::dec << " " << "(" << int(GetRValue(color)) << ", " << int(GetGValue(color)) << ", " << int(GetBValue(color)) << ")" << std::endl;
            Sleep(100);
        }
    }

    return 0;
}