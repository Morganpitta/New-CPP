#include "particleHandler.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Balls" );

    ParticleHandler particles;

    while ( window.isOpen() )
    {
        sf::Event event;
        while ( window.pollEvent(event) )
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
            particles.getParticles().push_back( Particle( sf::Vector2f( sf::Mouse::getPosition(window) ) ) );

        particles.update( 1 );

        window.clear( sf::Color::Black );

        particles.draw( window );
        
        window.display();
    }

    return 0;
}