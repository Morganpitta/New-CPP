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
        float averageSpeed;
        sf::Vector3f averageVelocity;
        public:
            ParticleHandler(): particles(), idGenerator(), averageSpeed(0)
            {

            }

            Particle &getParticle( Id id )
            {
                return this->particles[id];
            }

            std::size_t getNumberOfParticles()
            {
                return this->particles.size();
            }

            float getAverageSpeed()
            {
                return this->averageSpeed;
            }

            sf::Vector3f getAverageVelocity()
            {
                return this->averageVelocity;
            }

            Particle &addParticle( Particle particle )
            {
                this->particles[idGenerator.getNextId()] = particle;
                return this->particles[idGenerator.nextId-1];
            }

            void draw( sf::RenderWindow &window, Camera &camera )
            {
                for( ParticlesMap::iterator iterator = this->particles.begin(), itr_end = this->particles.end(); iterator != this->particles.end(); iterator++ ) 
                {
                    Particle &particle = iterator->second;
                    particle.draw( window, camera );
                }
            }

            void update()
            {
                for( ParticlesMap::iterator iterator1 = this->particles.begin(), itr_end = this->particles.end(); iterator1 != this->particles.end(); iterator1++ ) 
                {
                    Particle &particle1 = iterator1->second;
                    ParticlesMap::iterator iterator2 = iterator1;
                    for( iterator2++ , itr_end = this->particles.end(); iterator2 != this->particles.end(); iterator2++ ) 
                    {
                        Particle &particle2 = iterator2->second;
                        
                        sf::Vector3f vectorToParticle2 = particle2.getPosition() - particle1.getPosition();

                        float distance = sqrt( lengthSquared(vectorToParticle2) );

                        if ( distance > 0 )
                        {
                            // Cap force
                            //distance = std::max( 0.1f, distance );

                            float force = forceStrength / ( distance * distance ) / 1000;
                            sf::Vector3f direction = -vectorToParticle2 / distance;
                            particle1.accelerate( force * direction );
                            particle2.accelerate( -force * direction );
                        }
                    }
                }

                averageSpeed = 0;
                averageVelocity = {0,0,0};

                for( ParticlesMap::iterator iterator = this->particles.begin(), itr_end = this->particles.end(); iterator != this->particles.end(); iterator++ ) 
                {
                    Particle &particle = iterator->second;
                    particle.update();
                    averageSpeed += sqrt( lengthSquared( particle.getVelocity() ) );
                    averageVelocity += particle.getVelocity();
                }

                averageSpeed /= getNumberOfParticles();
                averageVelocity /= (float) getNumberOfParticles();
            }
    };

#endif /* PARTICLE_HANDLER_HPP */