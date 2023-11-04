#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "time.h++"
#include "particleHandler.h++"

template <typename T> 
int sign( T val ) 
{
    return (T(0) < val) - (val < T(0));
}

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
                particles.addParticle( Particle( {xIndex / 10.f, yIndex/10.f, zIndex/10.f } ) );
            }
        }
    }

    Camera camera( { 0.5, 0.5, -2 } );
    sf::Clock startTime = sf::Clock();

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
                    if ( event.key.code == sf::Keyboard::R )
                        for ( int index = 0; index < particles.getNumberOfParticle(); index++ )
                        {
                            particles.getParticle( index ).setVelocity( {0,0,0} );
                        }
                    break;

                case sf::Event::MouseWheelScrolled:
                    forceStrength = forceStrength + sign( event.mouseWheelScroll.delta ) * std::pow( abs( event.mouseWheelScroll.delta ) / 2, 3 );
                    break;
            }
        }


        if ( isSelected )
        {
            float speed = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? 0.1 : 0.01 ;
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W )  )
                camera.moveForward( speed );
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S )  )
                camera.moveBackwards( speed );
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A )  )
                camera.moveLeft( speed );
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D )  )
                camera.moveRight( speed );
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space )  )
                camera.moveUp( speed );
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift )  )
                camera.moveDown( speed );
            camera.rotateYaw( ( sf::Mouse::getPosition( window ).x - window.getSize().x / 2.f ) / ( M_PI * 300 ) );
            camera.rotatePitch( -( sf::Mouse::getPosition( window ).y - window.getSize().y / 2.f ) / ( M_PI * 300 ) );
            sf::Mouse::setPosition( { (int) std::floor( window.getSize().x / 2.f ), (int) std::floor( window.getSize().y / 2.f ) }, window );
        }

        if ( startTime.getElapsedTime().asSeconds() > 6 )
            particles.update();
        
        window.clear( sf::Color::Black );

        particles.draw( window, camera );
        
        sf::Text text = sf::Text( "Force: " + std::to_string(forceStrength), defaultFont );
        text.setPosition( {0,30} );
        window.draw( text );
        
        fps.draw( window, {0,0}, 30, sf::Color::White );

        window.display();
        //fps.restartAndSleep();
    }

    return 0;
}