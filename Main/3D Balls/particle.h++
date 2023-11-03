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

            void draw( sf::RenderWindow &window, Camera &camera )
            {
                sf::Vector3f relativePosition = camera.relativePositionTo( getPosition() );

                if ( relativePosition.z > 0.1 )
                {
                    sf::VertexArray quad( sf::PrimitiveType::Quads, 4 );

                    float apparentSize = ParticleRadius / relativePosition.z;

                    quad[0] = sf::Vertex( { relativePosition.x * 100 - apparentSize + 400, relativePosition.y * 100 - apparentSize + 400 }, { 0, 0 } );
                    quad[1] = sf::Vertex( { relativePosition.x * 100 - apparentSize + 400, relativePosition.y * 100 + apparentSize + 400 }, { 0, BallTexture.getSize().y } );
                    quad[2] = sf::Vertex( { relativePosition.x * 100 + apparentSize + 400, relativePosition.y * 100 + apparentSize + 400 }, { BallTexture.getSize().x, BallTexture.getSize().y } );
                    quad[3] = sf::Vertex( { relativePosition.x * 100 + apparentSize + 400, relativePosition.y * 100 - apparentSize + 400 }, { BallTexture.getSize().x, 0 } );

                    sf::RenderStates states;
                    states.texture = &BallTexture;

                    window.draw( quad, states );
                }
            }
    };

#endif /* PARTICLE_HPP */