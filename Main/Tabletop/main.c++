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
                handleResize( window, event.size.width, event.size.width, 1600, 800 );
                break;
        }
    }
}

int main()
{
    CardFactory &cardFactory = CardFactory::GetInstance();

    cardFactory.registerCard( "one", nullptr );

    sf::RenderWindow window( sf::VideoMode( 1600, 800 ), "Tabletop" );
    FpsLimiter fps( 60 );

    Card *card = cardFactory.createCard( "one" );
    CardCollection collection( card );

    while ( true )
    {
        handleInputs( window );

        if ( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords( sf::Mouse::getPosition( window ) );
            if ( collection.getCollider()->contains( mousePosition ) )
                collection.setPosition( mousePosition );
        }

        window.clear( sf::Color::White );

        window.draw( collection );

        window.display();
    }

    return 0;
}