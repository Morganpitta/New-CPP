#if !defined( TILE_HPP )
#define TILE_HPP 

    #include <windows.h>
    #include <set>
    #include <tuple>

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

    // float colourDifference( RGBQUAD colour1, RGBQUAD colour2 )
    // {
    //     return ( colour1.rgbRed - colour2.rgbRed ) * ( colour1.rgbRed - colour2.rgbRed ) + 
    //            ( colour1.rgbGreen - colour2.rgbGreen ) * ( colour1.rgbGreen - colour2.rgbGreen ) + 
    //            ( colour1.rgbBlue - colour2.rgbBlue ) * ( colour1.rgbBlue - colour2.rgbBlue );
    // }

    // Tile colourToTile( RGBQUAD colour )
    // {
    //     if ( colourDifference( colour, Covered1Color ) < 5 || colourDifference( colour, Covered2Color ) < 5 ) return CoveredTile;
    //     if ( colourDifference( colour, Clear1Color ) < 5 || colourDifference( colour, Clear2Color ) < 5 ) return ClearTile;
    //     if ( colourDifference( colour, FlagColor ) < 5 ) return FlagTile;
    //     if ( colourDifference( colour, Tile1Color ) < 5 ) return OneTile;
    //     if ( colourDifference( colour, Tile2Color ) < 5 ) return TwoTile;
    //     if ( colourDifference( colour, Tile3Color ) < 5 ) return ThreeTile;
    //     if ( colourDifference( colour, Tile4Color ) < 5 ) return FourTile;

    //     return ErrorTile;
    // }

    Tile getMostLikelyTile( std::set<RGBQUAD> colours )
    {
        if ( colours.count( Tile1Color ) > 0 ) return OneTile;
        if ( colours.count( Tile2Color ) > 0 ) return TwoTile;
        if ( colours.count( Tile3Color ) > 0 ) return ThreeTile;
        if ( colours.count( Tile4Color ) > 0 ) return FourTile;
        if ( colours.count( Tile5Color ) > 0 ) return FiveTile;
        if ( colours.count( FlagColor ) > 0 ) return FlagTile;
        if ( colours.count( Covered1Color ) > 0 || colours.count( Covered2Color ) > 0 ) return CoveredTile;
        if ( colours.count( Clear1Color ) > 0 || colours.count( Clear2Color ) > 0 ) return ClearTile;

        return ErrorTile;
    }

    bool isNumberTile( Tile tile )
    {
        return OneTile <= tile && tile <= EightTile;
    }

#endif /* TILE_HPP */