#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "time.h++"
#include <complex>

using namespace std::complex_literals;

void function( std::complex<double> &number, std::complex<double> &constant )
{
    number = std::abs( number ) * std::abs( number ) + constant;
}

unsigned int numberOfIterationsToDiverge( double x, double y, unsigned int maxDepth )
{
    std::complex<double> constant( x, y );
    std::complex<double> number( 0, 0 );
    for ( int index = 0; index < maxDepth; index++ )
    {
        if ( std::abs( number ) > 4 )
            return index;

        function( number, constant );
    }

    return maxDepth;
}

void generate( sf::VertexArray &vertices, unsigned int maxDepth = 1000 )
{
    for ( int xIndex = 0; xIndex < 800; xIndex++ )
    {
        for ( int yIndex = 0; yIndex < 800; yIndex++ )
        {
            unsigned int numberOfIterations = numberOfIterationsToDiverge( double(xIndex - 400)  / 10.f, double(yIndex - 400) / 10.f, maxDepth );

            if ( numberOfIterations == maxDepth )
            {
                vertices[xIndex+yIndex*800].color = { 255, 255, 255 };
            }
            else
            {
                double speed = 1 - std::pow( numberOfIterations / (float) maxDepth, 1/2 );
                vertices[xIndex+yIndex*800].color = { speed * 255, speed * 255, speed * 255 };
            }
        }
    }
}

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Mazewars" );

    //if ( !loadBaseAssets() )
    //    return 1;

    FpsLimiter fps( 60 );

    sf::VertexArray vertices(sf::PrimitiveType::Points,800*800);

    for ( int xIndex = 0; xIndex < 800; xIndex++ )
    {
        for ( int yIndex = 0; yIndex < 800; yIndex++ )
        {
            vertices[xIndex+yIndex*800].position = { xIndex, yIndex };
        }
    }

    generate(vertices);

    
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
                    break;
            }
        }
        
        window.clear( sf::Color::Black );

        window.draw( vertices );

        fps.draw( window, {0,0}, 30, sf::Color::White );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}