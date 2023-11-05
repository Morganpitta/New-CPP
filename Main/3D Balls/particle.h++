#if !defined( PARTICLE_HPP )
#define PARTICLE_HPP

    #include "SFML/Graphics.hpp"
    #include "camera.h++"
    #include <math.h>

    sf::Texture BallTexture;

    bool loadBallTexture()
    {
        if ( !BallTexture.loadFromFile("roundBall.png") )
        {
            return false;
        }

        return true;
    }

    const float ParticleRadius = 10;

    float lengthSquared( sf::Vector3f vector )
    {
        return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
    }


    class Particle
    {
        sf::Vector3f position;
        sf::Vector3f velocity;
        public:
            Particle( sf::Vector3f position = { 0, 0, 0 }, sf::Vector3f velocity = { 0, 0, 0 } ): position( position ), velocity( velocity )
            {

            }

            sf::Vector3f getPosition()
            {
                return this->position;
            }

            sf::Vector3f getVelocity()
            {
                return this->velocity;
            }

            void setPosition( sf::Vector3f position )
            {
                this->position = position;
            }

            void setVelocity( sf::Vector3f velocity )
            {
                this->velocity = velocity;
            }

            void move( sf::Vector3f position )
            {
                this->position += position;
            }

            void accelerate( sf::Vector3f velocity )
            {
                this->velocity += velocity;
            }

            void draw( sf::RenderWindow &window, Camera &camera )
            {
                sf::Vector3f relativePosition = camera.relativePositionTo( getPosition() );

                if ( relativePosition.z > 0.1 )
                {
                    sf::VertexArray quad( sf::PrimitiveType::Quads, 4 );

                    float apparentRadius = ParticleRadius / relativePosition.z;

                    quad[0] = sf::Vertex( { ( relativePosition.x / relativePosition.z ) * 1000 - apparentRadius + 400, ( -relativePosition.y / relativePosition.z ) * 1000 - apparentRadius + 400 }, { 0, 0 } );
                    quad[1] = sf::Vertex( { ( relativePosition.x / relativePosition.z ) * 1000 - apparentRadius + 400, ( -relativePosition.y / relativePosition.z ) * 1000 + apparentRadius + 400 }, { 0, BallTexture.getSize().y } );
                    quad[2] = sf::Vertex( { ( relativePosition.x / relativePosition.z ) * 1000 + apparentRadius + 400, ( -relativePosition.y / relativePosition.z ) * 1000 + apparentRadius + 400 }, { BallTexture.getSize().x, BallTexture.getSize().y } );
                    quad[3] = sf::Vertex( { ( relativePosition.x / relativePosition.z ) * 1000 + apparentRadius + 400, ( -relativePosition.y / relativePosition.z ) * 1000 - apparentRadius + 400 }, { BallTexture.getSize().x, 0 } );

                    sf::RenderStates states;
                    states.texture = &BallTexture;

                    window.draw( quad, states );
                }
            }

            void update()
            {
                //applyForces();

                updatePosition();
            }

            void applyForces()
            {
                accelerate( { 0, -1, 0 } );
            }

            void updatePosition()
            {
                sf::Vector3f nextPosition = getPosition() + getVelocity() / 10000.f;
                sf::Vector3f nextVelocity = getVelocity();

                /**
                if ( nextPosition.x <= 0 )
                {
                    nextPosition.x = 0;
                    nextVelocity.x *= -1;
                }
                if ( nextPosition.x >= 1 )
                {
                    nextPosition.x = 1;
                    nextVelocity.x *= -1;
                }
                
                if ( nextPosition.y <= 0 )
                {
                    nextPosition.y = 0;
                    nextVelocity.y *= -1;
                }
                if ( nextPosition.y >= 1 )
                {
                    nextPosition.y = 1;
                    nextVelocity.y *= -1;
                }
                
                if ( nextPosition.z <= 0 )
                {
                    nextPosition.z = 0;
                    nextVelocity.z *= -1;
                }
                if ( nextPosition.z >= 1 )
                {
                    nextPosition.z = 1;
                    nextVelocity.z *= -1;
                }
                */

                float distanceToCenter = sqrt( lengthSquared( nextPosition ) );

                if ( distanceToCenter >= 1 )
                {
                    sf::Vector3f direction = nextPosition / distanceToCenter;

                    nextPosition = direction;
                    nextVelocity = nextVelocity - 2 * (nextVelocity.x * direction.x + nextVelocity.y * direction.y + nextVelocity.z * direction.z) * direction;
                }

                setPosition( nextPosition );
                setVelocity( nextVelocity );
            }
    };

#endif /* PARTICLE_HPP */