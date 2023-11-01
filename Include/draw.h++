#if !defined( DRAW_HPP )
#define DRAW_HPP

    #include <SFML/Graphics.hpp>
    #include "math.h"
    #include "file.h++"

    sf::Font defaultFont;

    bool loadBaseAssets()
    {
        setWorkingDirectoryToDefault();

        if ( !defaultFont.loadFromFile("georgia.ttf") )
        {
            return false;
        }

        return true;
    }

#endif /* DRAW_HPP */