#include "Entities/ant.h++"
#include "Entities/pheromone.h++"
#include <SFML/Window.hpp>
#include "time.h++"

int main()
{    
    sf::RenderWindow window( sf::VideoMode(800,800), "Ants" );

    if ( !loadBaseAssets() )
        return 1;
    
    if ( !loadAntTexture() )
        return 1;

    std::vector<Ant> ants;
    std::vector<Pheromone> pheromones;

    for ( int index = 0; index < 100; index++ )
    {
        ants.push_back( Ant( {400,400} ) );
    }

    for ( int index = 0; index < 100; index++ )
    {
        pheromones.push_back( Pheromone( BorderPheromone, get2DUnitVector( 360*(index/100.f) ) * 400.f + sf::Vector2f ( 400, 400 ) ) );
    }

    FpsLimiter fps( 60 );

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
        
        window.clear( sf::Color::Black );

        std::for_each( ants.begin(), ants.end(), [&window,&pheromones]( Ant &ant ){
            ant.update( pheromones );
            window.draw( ant );
        }); 

        std::for_each( pheromones.begin(), pheromones.end(), [&window]( Pheromone &pheromone ){
            pheromone.update();
            window.draw( pheromone );
        });

        std::remove_if( pheromones.begin(), pheromones.end(), [](Pheromone& pheromone){
            return pheromone.getStrength() <= 0;
        });

        fps.draw( window, {0,0}, 30, sf::Color::White );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}