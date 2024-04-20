#if !defined( MATH_CPP )
#define MATH_CPP
    
    #include <SFML/System.hpp>
    #include <cmath>

    float vectorDot( sf::Vector2f vector1, sf::Vector2f vector2 )
    {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

    float absMin( float value1, float value2 )
    {
        return abs(value1) < abs(value2) ? value1 : value2;
    }

    // In radians
    float normaliseAngle( float angle )
    {
        angle = std::fmod( angle, 2 * M_PI );

        if ( angle < 0 )
            angle += 2*M_PI;
        
        return angle;
    }
    
    sf::Vector2f rotatePosition( sf::Vector2f position, float angle )
    {
        // The 2D rotation matrix
        return {
            static_cast<float>( 
                position.x*cos( angle ) + position.y*sin( angle )
            ),
            static_cast<float>( 
                - position.x*sin( angle ) + position.y*cos( angle )
            )
        };
    }

#endif /* MATH_CPP */