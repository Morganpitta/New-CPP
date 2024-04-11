#if !defined( PARTICLE_HPP )
#define PARTICLE_HPP

    #include <SFML/Graphics.hpp>

    class Particle: public sf::Drawable
    {
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float charge;

        public:
            Particle( sf::Vector2f position = {0,0}, float charge = -1 ): position( position ), charge(charge)
            {
                
            }

            sf::Vector2f getPosition() const { return this->position; }
            sf::Vector2f getVelocity() const { return this->velocity; }
            sf::Vector2f getAcceleration() const { return this->acceleration; }
            float getCharge() const { return this->charge; }

            void setPosition( sf::Vector2f position ) { this->position = position; }
            void setVelocity( sf::Vector2f velocity ) { this->velocity = velocity; }
            void setAcceleration( sf::Vector2f acceleration) { this->acceleration = acceleration; }

            void accelerate( sf::Vector2f amount ){ this->acceleration += amount; }

            void updatePosition( float dt )
            {
                position += getVelocity() * dt + 0.5f * getAcceleration() * dt * dt;
                velocity += getAcceleration() * dt;
                acceleration = {0,0};
            }

            void update( float dt )
            {
                updatePosition( dt );
            }

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
            {
                sf::CircleShape circle( 10 );
                circle.setOrigin( {5,5} );
                circle.setPosition( getPosition() );

                target.draw( circle );
            }
    };

#endif /* PARTICLE_HPP */