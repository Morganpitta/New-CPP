#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "time.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Timetabler" );
    window.setMouseCursorVisible( false );

    if ( !loadBaseAssets() )
        return 1;
    
    if ( !loadBallTexture() )
        return 1;

    FpsLimiter fps( 60 );

    ParticleHandler particles;

    float size = 7 - 1;

    for ( int xIndex = 0; xIndex <= size; xIndex++ )
    {   
        for ( int yIndex = 0; yIndex <= size; yIndex++ )
        {
            for ( int zIndex = 0; zIndex <= size; zIndex++ )
            {
                particles.addParticle( Particle( {xIndex / size - 1/2.f, yIndex / size - 1/2.f, zIndex / size - 1/2.f }, getRandomUnitVector() ) );
            }
        }
    }

    Camera camera( { 0, 0, -4 } );
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
                        for ( int index = 0; index < particles.getNumberOfParticles(); index++ )
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
        
        sf::Text text = sf::Text( "Force: " + std::to_string(forceStrength) + " Average speed: " + std::to_string(particles.getAverageSpeed()) + "\nAverage velocity: " + std::to_string(particles.getAverageVelocity().x) + ", " + std::to_string(particles.getAverageVelocity().y) + ", " + std::to_string(particles.getAverageVelocity().z), defaultFont );
        text.setPosition( {0,30} );
        window.draw( text );
        
        fps.draw( window, {0,0}, 30, sf::Color::White );

        window.display();
        //fps.restartAndSleep();
    }

    return 0;
}