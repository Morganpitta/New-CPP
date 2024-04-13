#if !defined( TILE_GRID_HPP )
#define TILE_GRID_HPP

    #include "tile.h++"
    #include "bitMap.h++"
    #include <array>

    typedef std::vector<std::vector<Tile>> TileGrid;

    TileGrid readScreen( DeviceContextHandleId context, POINT topLeft, POINT bottomRight, int gridWidth, int gridHeight )
    {
        POINT currentTileCenter;
        RGBQUAD currentTileColour;
        TileGrid grid; grid.resize( gridWidth, std::vector<Tile>(gridHeight) );
        
        int screenWidth = ( bottomRight.x - topLeft.x ); 
        int screenHeight = ( bottomRight.y - topLeft.y ); 

        int tileWidth = screenWidth / gridWidth;
        int tileHeight = screenHeight / gridHeight;

        std::vector<RGBQUAD> pixels;

        getPixels( context, pixels, topLeft, screenWidth, screenHeight );

        for ( int xIndex = 0; xIndex < gridWidth; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < gridHeight; yIndex++ )
            {
                std::set<RGBQUAD> colours = getColoursInArea( pixels, screenWidth, screenHeight, (xIndex+0.5f)*tileWidth, (yIndex+0.5f)*tileHeight );
                grid[xIndex][yIndex] = getMostLikelyTile( colours );
            }
        }

        return grid;
    }

    int getNumberOfKnownAdjacentMines( TileGrid &grid, int gridWidth, int gridHeight, POINT position )
    {
        std::array<POINT, 8> offsets = { {1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1} };
        
        int mines = 0;
        for ( POINT offset: offsets )
        {
            POINT tilePosition = {position.x+offset.x,position.y+offset.y};
            if ( tilePosition.x < 0 || tilePosition.x > gridWidth ||
                 tilePosition.y < 0 || tilePosition.y > gridWidth )
                continue;
            
            if ( grid[tilePosition.x][tilePosition.y] == FlagTile )
                mines++;
        }

        return mines;
    }

    POINT getBestMove( TileGrid &grid, int gridWidth, int gridHeight )
    {
        const int unknownProbability = -1;
        std::vector<std::vector<int>> probabilities; probabilities.resize( gridWidth, std::vector<int>(gridHeight, unknownProbability ) );

        for ( int xIndex = 0; xIndex < gridWidth; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < gridHeight; yIndex++ )
            {
                Tile tileType = grid[xIndex][yIndex];
                if ( isNumberTile(tileType) || tileType == ClearTile )
                {
                    int knownMines = getNumberOfKnownAdjacentMines( grid, gridWidth, gridHeight, {xIndex, yIndex} );
                    if ( knownMines >= int(tileType) )
                    {

                    }
                }
            }
        }
    }

#endif /* TILE_GRID_HPP */