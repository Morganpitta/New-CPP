#include "collisionRect.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode( {800,800} ), "SAT!" );

    CollisionRect rect1( {200,200}, {200,10} );
    CollisionRect rect2( {400,400}, {10,10} );

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
                    rect1.rotation += 0.1f * event.mouseWheelScroll.delta * event.mouseWheelScroll.delta * event.mouseWheelScroll.delta;
                    break;
            }
        }

        rect1.center = sf::Vector2f( sf::Mouse::getPosition( window ) );
        sf::Vector2f mtv = CollisionPolygon::getCollision( &rect1, &rect2 );
        rect1.center += mtv/2.f;
        rect2.center -= mtv/2.f;

        //window.clear( CollisionPolygon::areColliding( &rect1, &rect2 ) ? sf::Color::Green : sf::Color::Blue );
        window.clear( sf::Color::Blue );

        window.draw( rect1 );
        window.draw( rect2 );

        window.display();
    }

    return 0;
}