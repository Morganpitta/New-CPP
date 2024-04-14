#if !defined( TILE_GRID_HPP )
#define TILE_GRID_HPP

    #include "tile.h++"
    #include "bitMap.h++"
    #include <array>

    typedef std::vector<std::vector<Tile>> TileGrid;

    TileGrid readScreen( DeviceContextHandleId context, POINT topLeft, int width, int height, int gridWidth, int gridHeight )
    {
        POINT currentTileCenter;
        RGBQUAD currentTileColour;
        TileGrid grid; grid.resize( gridWidth, std::vector<Tile>(gridHeight) );

        float tileWidth = float(width) / gridWidth;
        float tileHeight = float(height) / gridHeight;

        std::vector<RGBQUAD> pixels;

        getPixels( context, pixels, topLeft, width, height );

        for ( int xIndex = 0; xIndex < gridWidth; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < gridHeight; yIndex++ )
            {
                std::set<RGBQUAD> colours = getColoursInArea( pixels, width, height, (xIndex+0.5f)*tileWidth, (yIndex+0.5f)*tileHeight, (2*tileWidth)/3, (2*tileHeight)/3 );
                grid[xIndex][yIndex] = getMostLikelyTile( colours );
            }
        }

        return grid;
    }

    std::vector<POINT> getAdjacentMatchingTiles( TileGrid &grid, int gridWidth, int gridHeight, POINT position, Tile tileType )
    {
        const std::array<POINT, 8> offsets = {{ {1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1} }};
        
        std::vector<POINT> mines = {};
        for ( POINT offset: offsets )
        {
            POINT tilePosition = {position.x+offset.x,position.y+offset.y};
            if ( tilePosition.x < 0 || tilePosition.x >= gridWidth ||
                 tilePosition.y < 0 || tilePosition.y >= gridWidth )
                continue;
            
            if ( grid[tilePosition.x][tilePosition.y] == tileType )
                mines.push_back( tilePosition );
        }

        return mines;
    }

    struct Move
    {
        POINT position;
        std::vector<DWORD> flags;
    };

    bool operator<( const Move& move1, const Move& move2 )
    {
        return std::tie(move1.position.x, move1.position.y) < std::tie(move2.position.x, move2.position.y);
    }

    void playMove( Move move )
    {
        std::vector<INPUT> inputs = {};
        POINT originalMousePosition; GetCursorPos( &originalMousePosition );

        SetCursorPos( move.position.x, move.position.y );

        for ( DWORD flag: move.flags )
        {
            INPUT input = {0};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = flag;
            inputs.push_back(input);
        }

        SendInput( inputs.size(), &inputs[0], sizeof(INPUT) );

        SetCursorPos( originalMousePosition.x, originalMousePosition.y );
    }

    std::set<Move> getBestMoves( TileGrid &grid, int gridWidth, int gridHeight )
    {
        const int unknownProbability = -1;
        std::vector<std::vector<int>> probabilities; probabilities.resize( gridWidth, std::vector<int>(gridHeight, unknownProbability ) );

        std::set<Move> moves;
        for ( int xIndex = 0; xIndex < gridWidth; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < gridHeight; yIndex++ )
            {
                Tile tileType = grid[xIndex][yIndex];
                if ( isNumberTile(tileType) || tileType == ClearTile )
                {
                    std::vector<POINT> knownMines = getAdjacentMatchingTiles( grid, gridWidth, gridHeight, {xIndex, yIndex}, FlagTile );
                    std::vector<POINT> coveredTiles = getAdjacentMatchingTiles( grid, gridWidth, gridHeight, {xIndex, yIndex}, CoveredTile );
                    
                    if ( knownMines.size() >= int(tileType) )
                    {
                        for ( POINT position: coveredTiles )
                        {
                            moves.insert( {position, {MOUSEEVENTF_LEFTDOWN,MOUSEEVENTF_LEFTUP} } );
                        }
                    }

                    if ( coveredTiles.size() == (int(tileType) - knownMines.size() ) )
                    {
                        for ( POINT position: coveredTiles )
                        {
                            moves.insert( {position, {MOUSEEVENTF_RIGHTDOWN,MOUSEEVENTF_RIGHTUP} } );
                            grid[position.x][position.y] = FlagTile;
                        }
                    }
                }
            }
        }

        return moves;
    }

#endif /* TILE_GRID_HPP */