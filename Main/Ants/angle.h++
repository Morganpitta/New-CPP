#if !defined( ANGLE_HPP )
#define ANGLE_HPP

    #include <math.h>

    float normaliseAngle( float angle )
    {
        angle = std::fmod( angle, 360.f );

        if ( angle < 0 )
            angle += 360;
        
        return angle;
    }

    float angleOf( sf::Vector2f vector )
    {
        return normaliseAngle( atan2( vector.x, vector.y ) * float( 180 / M_PI ) );
    }

    sf::Vector2f get2DUnitVector( float angle )
    {
        return { sin( angle * float(M_PI/180) ), cos( angle * float(M_PI/180) ) };
    }

    sf::Vector2f get2DUnitVectorYAxisInverted( float angle )
    {
        return { sin( angle * float(M_PI/180) ), -cos( angle * float(M_PI/180) ) };
    }

#endif /* ANGLE_HPP */