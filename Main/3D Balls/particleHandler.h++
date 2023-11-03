#if !defined( PARTICLE_HANDLER_HPP )
#define PARTICLE_HANDLER_HPP

    #include "particle.h++"
    #include "id.h++"

    typedef std::map<Id, Particle> ParticlesMap;

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

            Particle &addParticle( Particle particle )
            {
                particles[idGenerator.getNextId()] = particle;
                return particles[idGenerator.lastId];
            }

            void draw( sf::RenderWindow &window, Camera &camera )
            {
                for( ParticlesMap::iterator iterator = particles.begin(), itr_end = particles.end(); iterator != particles.end(); ++iterator ) 
                {
                    Particle &particle = iterator->second;
                    particle.draw( window, camera );
                }
            }
    };

#endif /* PARTICLE_HANDLER_HPP */