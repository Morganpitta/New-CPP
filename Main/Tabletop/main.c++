#include "cardFactory.h++"
#include "cardCollection.h++"
#include "time.h++"
#include "draw.h++"

void handleInputs( sf::RenderWindow &window )
{
    sf::Event event;
    while ( window.pollEvent(event) )
    {
        switch ( event.type )
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                handleResize( window, event.size.width, event.size.height, 1600, 1000 );
                break;
        }
    }
}

int main()
{
    CardFactory &cardFactory = CardFactory::GetInstance();

    cardFactory.registerCard( "one", nullptr );

    sf::RenderWindow window( sf::VideoMode( 1600, 1000 ), "Tabletop" );
    FpsLimiter fps( 60 );

    if ( !loadBaseAssets() )
        return 1;

    Card *card = cardFactory.createCard( 1, "one" );
    CardCollection collection( card );

    while ( window.isOpen() )
    {
        handleInputs( window );

        if ( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords( sf::Mouse::getPosition( window ) );
            if ( collection.getCollider()->contains( mousePosition ) )
                collection.setPosition( mousePosition );
        }

        window.clear( sf::Color::Black );
        sf::RectangleShape rect( {1600, 1000} );
        rect.setFillColor( sf::Color::Green );
        window.draw( rect );

        window.draw( collection );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}