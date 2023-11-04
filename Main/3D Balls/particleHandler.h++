#if !defined( PARTICLE_HANDLER_HPP )
#define PARTICLE_HANDLER_HPP

    #include "particle.h++"
    #include "id.h++"

    typedef std::map<Id, Particle> ParticlesMap;
    float forceStrength = 0;

    class ParticleHandler
    {
        ParticlesMap particles;
        IdGenerator idGenerator;
        public:
            ParticleHandler(): particles(), idGenerator()
            {

            }

            Particle &getParticle( Id id )
            {
                return this->particles[id];
            }

            std::size_t getNumberOfParticle()
            {
                return this->particles.size();
            }


            Particle &addParticle( Particle particle )
            {
                particles[idGenerator.getNextId()] = particle;
                return particles[idGenerator.nextId-1];
            }

            void draw( sf::RenderWindow &window, Camera &camera )
            {
                for( ParticlesMap::iterator iterator = particles.begin(), itr_end = particles.end(); iterator != particles.end(); iterator++ ) 
                {
                    Particle &particle = iterator->second;
                    particle.draw( window, camera );
                }
            }

            void update()
            {
                for( ParticlesMap::iterator iterator1 = particles.begin(), itr_end = particles.end(); iterator1 != particles.end(); iterator1++ ) 
                {
                    Particle &particle1 = iterator1->second;
                    ParticlesMap::iterator iterator2 = iterator1;
                    for( iterator2++ , itr_end = particles.end(); iterator2 != particles.end(); iterator2++ ) 
                    {
                        Particle &particle2 = iterator2->second;
                        
                        sf::Vector3f vectorToParticle2 = particle2.getPosition() - particle1.getPosition();

                        float distance = sqrt( lengthSquared(vectorToParticle2) );

                        if ( distance > 0 )
                        {
                            distance = std::max( 0.1f, distance );

                            float force = forceStrength / ( distance * distance ) / 1000;
                            sf::Vector3f direction = -vectorToParticle2 / distance;
                            particle1.accelerate( force * direction );
                            particle2.accelerate( -force * direction );
                        }
                    }
                }

                for( ParticlesMap::iterator iterator = particles.begin(), itr_end = particles.end(); iterator != particles.end(); iterator++ ) 
                {
                    Particle &particle = iterator->second;
                    particle.update();
                }
            }
    };

#endif /* PARTICLE_HANDLER_HPP */