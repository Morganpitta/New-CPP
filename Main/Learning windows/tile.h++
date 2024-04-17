#if !defined( TILE_HPP )
#define TILE_HPP 

    #include <windows.h>
    #include <set>
    #include <tuple>
    #include <array>

    enum Tile
    {
        ClearTile,
        OneTile,
        TwoTile,
        ThreeTile,
        FourTile,
        FiveTile,
        SixTile,
        SevenTile,
        EightTile,
        FlagTile,
        CoveredTile,
        ErrorTile,
        NumberOfTiles
    };

    // In the form BGRA
    const RGBQUAD Covered1Color = { 0x51, 0xd7, 0xaa, 0xff };
    const RGBQUAD Covered2Color = { 0x49, 0xd1, 0xa2, 0xff };
    const RGBQUAD Clear1Color   = { 0x99, 0xb8, 0xd7, 0xff };
    const RGBQUAD Clear2Color   = { 0x9f, 0xc2, 0xe5, 0xff };
    const RGBQUAD Tile1Color    = { 0xd2, 0x76, 0x19, 0xff };
    const RGBQUAD Tile2Color    = { 0x3c, 0x8e, 0x38, 0xff };
    const RGBQUAD Tile3Color    = { 0x30, 0x30, 0xd3, 0xff };
    const RGBQUAD Tile4Color    = { 0xa2, 0x1f, 0x7b, 0xff };
    const RGBQUAD Tile5Color    = { 0x01, 0x8f, 0xff, 0xff };
    const RGBQUAD FlagColor     = { 0x07, 0x36, 0xf2, 0xff };

    const std::array<RGBQUAD,10> tileColours = {{ Tile1Color, Tile2Color, Tile3Color, Tile4Color, Tile5Color, FlagColor, Covered1Color, Covered2Color, Clear1Color, Clear2Color }};

    bool operator==( const RGBQUAD &rgb1, const RGBQUAD &rgb2 )
    {
        return std::tie(rgb1.rgbRed,rgb1.rgbGreen,rgb1.rgbBlue) == std::tie(rgb2.rgbRed,rgb2.rgbGreen,rgb2.rgbBlue);
    }

    float colourDifference( RGBQUAD colour1, RGBQUAD colour2 )
    {
        return ( colour1.rgbRed - colour2.rgbRed ) * ( colour1.rgbRed - colour2.rgbRed ) + 
               ( colour1.rgbGreen - colour2.rgbGreen ) * ( colour1.rgbGreen - colour2.rgbGreen ) + 
               ( colour1.rgbBlue - colour2.rgbBlue ) * ( colour1.rgbBlue - colour2.rgbBlue );
    }

    Tile colourToTile( RGBQUAD colour )
    {
        if ( colour == Tile1Color ) return OneTile;
        if ( colour == Tile2Color ) return TwoTile;
        if ( colour == Tile3Color ) return ThreeTile;
        if ( colour == Tile4Color ) return FourTile;
        if ( colour == Tile5Color ) return FiveTile;
        if ( colour == FlagColor ) return FlagTile;
        if ( colour == Covered1Color || colour == Covered2Color ) return CoveredTile;
        if ( colour == Clear1Color || colour == Clear2Color ) return ClearTile;

        return ErrorTile;
    }

    float getDifference( std::set<RGBQUAD> colours, RGBQUAD colour )
    {
        if ( colours.empty() )
            return -1;

        auto iterator = colours.begin();
        float bestMatchDifference = colourDifference( *iterator, colour );
        for ( iterator++; iterator != colours.end(); iterator++ )
        {
            float difference = colourDifference( *iterator, colour );
            if ( bestMatchDifference > difference )
            {
                bestMatchDifference = difference;
            }
        }

        return bestMatchDifference;
    }

    Tile getMostLikelyTile( std::set<RGBQUAD> colours )
    {
        if ( colours.empty() )
            return ErrorTile;

        int bestMatchIndex = -1;
        float bestMatchDifference = 0;
        for ( int index = 0; index < tileColours.size(); index++ )
        {
            float difference = getDifference( colours, tileColours[index] );
            if ( bestMatchDifference > difference || bestMatchIndex == -1 )
            {
                if ( difference < 5 )
                    return colourToTile( tileColours[index] );
                bestMatchIndex = index;
                bestMatchDifference = difference;
            }
        }

        return ErrorTile;
    }

    bool isNumberTile( Tile tile )
    {
        return OneTile <= tile && tile <= EightTile;
    }

#endif /* TILE_HPP */