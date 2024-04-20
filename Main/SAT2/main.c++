#include "collisionRect.h++"
#include "time.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode( {800,800} ), "SAT!" );

    CollisionRect rect1( {200,10}, {200,200} );
    CollisionRect rect2( {10,10}, {400,400} );

    if ( !loadBaseAssets() )
        return 0;

    FpsLimiter fps( 60 );

    while ( window.isOpen() )
    {
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseWheelScrolled:
                    rect1.rotate( 0.01f * event.mouseWheelScroll.delta * event.mouseWheelScroll.delta * event.mouseWheelScroll.delta );
                    break;
            }
        }

        rect1.setPosition( sf::Vector2f( sf::Mouse::getPosition( window ) ) );
        sf::Vector2f mtv = CollisionPolygon::getCollision( &rect1, &rect2 );
        rect1.move( mtv/2.f );
        rect2.move( -mtv/2.f );

        //window.clear( CollisionPolygon::areColliding( &rect1, &rect2 ) ? sf::Color::Green : sf::Color::Blue );
        window.clear( sf::Color::Blue );

        window.draw( rect1 );
        window.draw( rect2 );

        fps.draw( window, {0,0}, 30 );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}