#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "time.h++"
#include "particleHandler.h++"
#include <complex>

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Balls" );
    window.setMouseCursorVisible( false );

    if ( !loadBaseAssets() )
        return 1;
    if ( !loadBallTexture() )
        return 1;

    FpsLimiter fps( 60 );

    ParticleHandler particles;

    for ( int xIndex = 0; xIndex < 10; xIndex++ )
    {   
        for ( int yIndex = 0; yIndex < 10; yIndex++ )
        {
            for ( int zIndex = 0; zIndex < 10; zIndex++ )
            {
                particles.addParticle( Particle( {xIndex, yIndex, zIndex } ) );
            }
        }
    }

    Camera camera;

    bool isSelected = false;

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

                case sf::Event::KeyPressed:
                    if ( event.key.code == sf::Keyboard::Escape )
                        isSelected = !isSelected;
                        window.setMouseCursorVisible( !isSelected );
                        sf::Mouse::setPosition( { (int) std::floor( window.getSize().x / 2.f ), (int) std::floor( window.getSize().y / 2.f ) }, window );
                    break;
            }
        }


        float speed = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? 0.1 : 0.01 ;
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W )  )
            camera.moveForward();
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S )  )
            camera.moveBackwards();
        if ( isSelected )
        {
            camera.rotateYaw( ( sf::Mouse::getPosition( window ).x - window.getSize().x / 2.f ) / ( M_PI * 300 ) );
            camera.rotatePitch( -( sf::Mouse::getPosition( window ).y - window.getSize().x / 2.f ) / ( M_PI * 300 ) );
            sf::Mouse::setPosition( { (int) std::floor( window.getSize().x / 2.f ), (int) std::floor( window.getSize().y / 2.f ) }, window );
        }
        
        window.clear( sf::Color::Black );

        particles.draw( window, camera );
        
        sf::Text text = sf::Text( "Yaw: " + std::to_string( camera.getYaw() ) + "\nPitch:" + std::to_string( camera.getPitch() ) + "\nX: "+std::to_string( camera.getPosition().x ) + ", Y: " +std::to_string( camera.getPosition().y ) + ", Z: " +std::to_string( camera.getPosition().z ), defaultFont );
        text.setPosition( {0,30} );
        window.draw( text );

        fps.draw( window, {0,0}, 30, sf::Color::White );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}