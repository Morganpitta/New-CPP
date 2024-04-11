#if !defined( PARTICLE_HANDLER_CPP )
#define PARTICLE_HANDLER_CPP

    #include "particle.h++"
    #include <cmath>

    class ParticleHandler
    {
        std::vector<Particle> particles;

        public:
            std::vector<Particle> &getParticles() { return particles; }
            Particle &getParticle( std::size_t index ) { return getParticles()[index]; }

            void update( float dt )
            {
                for ( std::vector<Particle>::iterator iter1 = getParticles().begin(); iter1 < getParticles().end(); iter1++ )
                {
                    Particle &particle1 = *(iter1);
                    std::vector<Particle>::iterator iter2 = iter1;
                    for ( iter2++; iter2 < getParticles().end(); iter2++ )
                    {
                        Particle &particle2 = *(iter2);

                        sf::Vector2f vectorToParticle2 = particle2.getPosition() - particle1.getPosition();

                        float distanceSquared = vectorToParticle2.x * vectorToParticle2.x + vectorToParticle2.y * vectorToParticle2.y;

                        if ( distanceSquared > 0 )
                        {
                            float force = (particle1.getCharge() * particle2.getCharge()) / distanceSquared;
                            sf::Vector2f direction = -(vectorToParticle2) / float(sqrt( distanceSquared ));
                            particle1.accelerate( force * direction );
                            particle2.accelerate( -force * direction );
                        }
                    }
                }

                for ( std::vector<Particle>::iterator iter1 = getParticles().begin(); iter1 < getParticles().end(); iter1++ )
                {
                    Particle &particle = *(iter1);
                    particle.update( dt );
                }
            }

            void draw( sf::RenderWindow &window )
            {
                for ( std::vector<Particle>::iterator iter1 = getParticles().begin(); iter1 < getParticles().end(); iter1++ )
                {
                    Particle &particle = *(iter1);
                    window.draw(particle);
                }
            }
    };

#endif /* PARTICLE_HANDLER_CPP */