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

    void handleResize( 
        sf::RenderWindow &window,
        float windowWidth, 
        float windowHeight,
        const float targetWidth,
        const float targetHeight
    )
    {
        float ratio = windowWidth/windowHeight;
        float targetRatio = targetWidth/targetHeight;
        sf::FloatRect visibleArea(0, 0, targetWidth, targetHeight);
        
        if ( ratio > targetRatio )
        {
            float offset = targetWidth*(ratio/targetRatio-1);
            visibleArea = sf::FloatRect(-offset/2, 0, targetWidth+offset, targetHeight);
        }
        else if ( ratio < targetRatio )
        {
            float offset = targetHeight*(targetRatio/ratio-1);
            visibleArea = sf::FloatRect(0, -offset/2, targetWidth, targetHeight+offset);
        }
        window.setView(sf::View(visibleArea));
    }

#endif /* DRAW_HPP */