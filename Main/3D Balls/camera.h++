#if !defined( CAMERA_HPP )
#define CAMERA_HPP

    #include "SFML/System.hpp"
    #include <math.h>
    #include "matrix.h++"
    #include "random.h++"


    Matrix<float> getXRotationMatrix( float angle )
    {
        return Matrix<float>( 3, 3, { 
            1,          0,          0,
            0,          cos(angle), -sin(angle),
            0,          sin(angle), cos(angle)
        });
    }

    Matrix<float> getYRotationMatrix( float angle )
    {
        return Matrix<float>( 3, 3, { 
            cos(angle), 0,          sin(angle),
            0,          1,          0,
            -sin(angle),0,          cos(angle)
        });
    }

    Matrix<float> getZRotationMatrix( float angle )
    {
        return Matrix<float>( 3, 3, { 
            cos(angle), -sin(angle),0,
            sin(angle), cos(angle), 0,
            0,          0,          1
        });
    }

    sf::Vector3f rotatePosition( sf::Vector3f relativePosition, float yaw, float pitch )
    {
        relativePosition *= getYRotationMatrix( -yaw );
        relativePosition *= getXRotationMatrix( pitch );
        return relativePosition;
    }

    sf::Vector3f getUnitVector( float yaw, float pitch )
    {
        return { sin( yaw ) * cos( pitch ), sin( pitch ), cos( yaw ) * cos( pitch ) };
    }

    sf::Vector3f getRandomUnitVector()
    {
        return getUnitVector( randomFloat( 0, M_PI * 2 ), randomFloat( 0, M_PI * 2 ) );
    }

    class Camera
    {
        sf::Vector3f position;
        float yaw;
        float pitch;
        public:
            Camera( sf::Vector3f position = { 0, 0, 0 }, float yaw = 0, float pitch = 0 ): position( position ), yaw( yaw ), pitch( pitch )
            {

            }

            sf::Vector3f getPosition()
            {
                return this->position;
            }

            float getYaw()
            {
                return this->yaw;
            }

            float getPitch()
            {
                return this->pitch;
            }

            void setPosition( sf::Vector3f position )
            {
                this->position = position;
            }

            void setYaw( float yaw )
            {
                this->yaw = yaw;
            }

            void setPitch( float pitch)
            {
                this->pitch = pitch;
            }

            void moveForward( float amount = 1 )
            {
                this->position += getUnitVector( getYaw(), getPitch() ) * amount;
            }

            void moveBackwards( float amount = 1 )
            {
                this->position -= getUnitVector( getYaw(), getPitch() ) * amount;
            }

            void moveLeft( float amount = 1 )
            {
                this->position += getUnitVector( getYaw() - M_PI / 2, getPitch() ) * amount;
            }

            void moveRight( float amount = 1 )
            {
                this->position += getUnitVector( getYaw() + M_PI / 2, getPitch() ) * amount;
            }

            void moveUp( float amount = 1 )
            {
                this->position += getUnitVector( getYaw(), getPitch() + M_PI / 2 ) * amount;
            }

            void moveDown( float amount = 1 )
            {
                this->position -= getUnitVector( getYaw(), getPitch() + M_PI / 2 ) * amount;
            }

            void rotateYaw( float angle )
            {
                this->yaw = fmod( 2 * M_PI + this->yaw + angle, 2 * M_PI );
            }

            void rotatePitch( float angle )
            {
                this->pitch = std::min<float>( std::max<float>( -M_PI/2, this->pitch + angle ), M_PI/2 );
            }

            sf::Vector3f relativePositionTo( sf::Vector3f globalPosition )
            {
                sf::Vector3f relativePosition = globalPosition - getPosition();
                return rotatePosition( relativePosition, getYaw(), getPitch() );
            }
    };

#endif /* CAMERA_HPP */