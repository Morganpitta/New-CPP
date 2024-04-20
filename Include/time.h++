#if !defined( FPS_HPP )
#define FPS_HPP

    #include <SFML/Window.hpp>
    #include <math.h>
    #include <unistd.h>
    #include "draw.h++"
    #include <chrono>
    #include <thread>

    typedef std::chrono::nanoseconds chronoNanoseconds; 

    chronoNanoseconds timeNow()
    {
        return std::chrono::duration_cast<chronoNanoseconds>( std::chrono::steady_clock::now().time_since_epoch() );
    }

    float nanosecondsToSeconds( chronoNanoseconds nanoseconds )
    {
        return nanoseconds.count()/1000000000.f;
    }

    class FpsLimiter
    {
        float averageFps;
        chronoNanoseconds startTime;
        chronoNanoseconds maxTimePerFrame;

        public:
            FpsLimiter( float fps )
            {
                maxTimePerFrame = std::chrono::round<chronoNanoseconds>(std::chrono::duration<float>(1/fps));
                averageFps = fps;
                startTime = timeNow();
            }

            chronoNanoseconds restart()
            {
                chronoNanoseconds elapsed = (timeNow() - startTime);

                //std::cout << std::to_string(std::max( elapsed, maxTimePerFrame ).count()/1000000000.f) << std::endl;

                averageFps = ( averageFps + 1/( nanosecondsToSeconds( std::max( elapsed, maxTimePerFrame ) ) ) )/2.f;
                
                startTime = timeNow();

                return elapsed;
            }

            chronoNanoseconds restartAndSleep()
            {
                chronoNanoseconds elapsed = (timeNow() - startTime);

                if ( elapsed < maxTimePerFrame )
                {
                    long long int microseconds = (maxTimePerFrame - elapsed).count() / 1000.f;
                    sleepFor( microseconds );
                }

                return restart();
            }

            void draw( sf::RenderWindow &window, sf::Vector2f topLeft, std::size_t size, sf::Color colour = sf::Color::Black )
            {
                sf::Text text( std::to_string( (int) std::ceil(averageFps) ), defaultFont );

                text.setFillColor( colour );
                text.setPosition( topLeft );
                text.setCharacterSize( size );

                window.draw(text);
            }
    };

#endif /* FPS_HPP */