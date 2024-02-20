#if !defined( PHEROMONE_HPP )
#define PHEROMONE_HPP

    #include "SFML/Graphics.hpp"

    enum PheromoneType
    {
        HomePheromone,
        FoodPheromone,
        BorderPheromone,
        NoPheromone
    };

    const int PheromoneSize = 3;
    class Pheromone: public sf::Drawable
    {
        protected:
            sf::Vector2f position;
            int strength;
            PheromoneType type;

        public:
            Pheromone( PheromoneType type, sf::Vector2f position = {0,0} )
            {
                setPosition( position );
                setStrength( type == BorderPheromone ? 1000000 : 1000 );
                setType( type );
            }

            sf::Vector2f getPosition() const
            {
                return this->position;
            }

            int getStrength() const
            {
                return this->strength;
            }

            PheromoneType getType() const
            {
                return this->type;
            }

            void setPosition( sf::Vector2f position )
            {
                this->position = position;
            }

            void setStrength( float strength )
            {
                this->strength = strength;
            }

            void setType( PheromoneType type )
            {
                this->type = type;
            }

            void update()
            {
                if ( getType() != BorderPheromone )
                    setStrength( getStrength() - 1 );
            }

            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
            {
                sf::CircleShape pheromone( PheromoneSize );

                pheromone.setOrigin( { PheromoneSize, PheromoneSize } );
                pheromone.setPosition( getPosition() );
                pheromone.setFillColor( { 255, 0, 0, std::min( float( getStrength() ) / 1000.f, 1.f ) * 255 });

                target.draw( pheromone );
            }
    };

#endif /* PHEROMONE_HPP */