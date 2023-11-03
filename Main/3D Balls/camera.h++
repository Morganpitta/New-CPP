#if !defined( CAMERA_HPP )
#define CAMERA_HPP

    #include "SFML/System.hpp"
    #include <math.h>

    sf::Vector3f rotatePosition( sf::Vector3f relativePosition, float yaw, float pitch, float roll )
    {
        return {
            ( cos( yaw ) *  cos ( pitch ) ) * relativePosition.x + ( cos( yaw ) *  sin( pitch ) * sin( roll ) - sin( yaw ) * cos( roll ) ) * relativePosition.y + ( cos( yaw ) * sin ( pitch ) * cos( roll ) + sin( yaw ) * sin ( roll ) ) * relativePosition.z,
            ( sin( yaw ) * cos( pitch ) ) * relativePosition.x + ( sin( yaw ) * sin( pitch ) * sin( roll ) + cos( yaw ) * cos( roll ) ) * relativePosition.y + ( sin( yaw ) * sin ( pitch ) * cos (roll) - cos( yaw ) *  sin( roll ) ) * relativePosition.z,
            ( -sin( pitch ) ) * relativePosition.x + ( cos( pitch ) * sin( roll ) ) * relativePosition.y + ( cos( pitch ) *  cos( roll )) * relativePosition.z
        };
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

            void moveForward()
            {
                this->position += { sin( yaw ) * cos( pitch ), sin( pitch ), cos( yaw ) * cos( pitch ) };
            }

            void moveBackwards()
            {
                this->position += { sin( yaw + M_PI ) / cos( pitch ), sin( pitch ), cos( yaw + M_PI ) / cos( pitch ) };
            }

            void rotateYaw( float angle )
            {
                this->yaw = fmod( 2 * M_PI + this->yaw + angle, 2 * M_PI );
            }

            void rotatePitch( float angle )
            {
                this->pitch = std::min<float>( std::max<float>( -M_PI, this->pitch + angle ), M_PI );
            }

            sf::Vector3f relativePositionTo( sf::Vector3f globalPosition )
            {
                sf::Vector3f relativePosition = globalPosition - getPosition();
                return rotatePosition( relativePosition, 0, getYaw(), getPitch() );
            }
    };

#endif /* CAMERA_HPP */