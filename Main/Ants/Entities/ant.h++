#if !defined( ANT_HPP )
#define ANT_HPP

    #include "SFML/Graphics.hpp"
    #include "pheromone.h++"
    #include "angle.h++"
    #include "random.h++"

    sf::Texture antTexture;

    bool loadAntTexture()
    {
        if ( !antTexture.loadFromFile("Ants/ant.png") )
            return false;

        return true;
    }

    class Ant: public sf::Drawable
    {
        protected:
            sf::Vector2f position;
            float rotation;
            float targetRotation;
            int pheromoneCooldown;

        public:
            Ant( sf::Vector2f position = {0,0} )
            {
                setPosition( position );
                setRotation( randomFloat( 0, 360 ) );
                pheromoneCooldown = 20;
            }

            sf::Vector2f getPosition() const
            {
                return this->position;
            }

            float getRotation() const
            {
                return this->rotation;
            }

            float getTargetRotation() const
            {
                return this->targetRotation;
            }

            sf::Vector2f relativePositionOf( sf::Vector2f position )
            {
                return position - getPosition();
            }

            void setPosition( sf::Vector2f position )
            {
                this->position = position;
            }

            void setRotation( float rotation )
            {
                this->rotation = normaliseAngle( rotation );
            }

            void moveForward( float distance )
            {
                setPosition( getPosition() + get2DUnitVector( getRotation() ) * distance );
            }

            void turnLeft( float angle )
            {
                setRotation( getRotation() + angle);
            }

            void turnRight( float angle )
            {
                setRotation( getRotation() - angle);
            }

            bool shouldRepel( PheromoneType type ) const
            {
                if ( type == BorderPheromone )
                    return true;

                return false;
            }

            void updateTargetRotation( std::vector<Pheromone> &pheromones )
            {
                sf::Vector2f resultant = {0,0};
                int count = 0;

                std::for_each( pheromones.begin(), pheromones.end(), [this, &resultant, &count]( Pheromone &pheromone ) {
                    sf::Vector2f relativePosition = { pheromone.getPosition().x - getPosition().x, pheromone.getPosition().y - getPosition().y };
                    float distance = sqrt( relativePosition.x * relativePosition.x + relativePosition.y * relativePosition.y );
                    if ( distance <= 100 && distance > 0 )
                    {
                        float angle = angleOf( relativePosition );

                        if ( normaliseAngle( angle - getRotation() ) <= 90 || 
                             normaliseAngle( angle - getRotation() ) >= 270
                        )
                        {
                            resultant += get2DUnitVector( angle ) * float(pheromone.getStrength()) * ( shouldRepel( pheromone.getType() ) ? -1.f : 1.f );

                            count++;
                        }
                    }
                });

                if ( count == 0 )
                    this->targetRotation = getRotation();
                else
                    this->targetRotation = angleOf(resultant);
            }

            void updatePosition()
            {
                float rotationOffset = normaliseAngle( this->targetRotation - getRotation() );

                if ( rotationOffset <= 180 && rotationOffset > 0 )
                {
                    turnLeft( 2 );
                }
                else if ( rotationOffset > 180 && rotationOffset < 360 )
                {
                    turnRight( 2 );
                }

                moveForward( 1 );
            }

            void update( std::vector<Pheromone> &pheromones )
            {    
                updateTargetRotation( pheromones );

                if ( --pheromoneCooldown < 0 )
                {
                    pheromones.push_back( Pheromone( FoodPheromone, getPosition() ) );
                    pheromoneCooldown = 20;
                }

                updatePosition();
            }

            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const
            {
                sf::Sprite ant;

                ant.setTexture( antTexture );
                ant.setOrigin( { antTexture.getSize().x/2.f,antTexture.getSize().y/2.f } );
                ant.setPosition( getPosition() );
                ant.setRotation( normaliseAngle(180-getRotation()) );
                ant.setScale(0.1,0.1);

                sf::VertexArray rotations( sf::PrimitiveType::Lines, 2 );

                rotations[0].position = getPosition();
                rotations[1].position = getPosition()+get2DUnitVector(getTargetRotation())*20.f;
                rotations[0].color = sf::Color::Blue;
                rotations[1].color = sf::Color::Blue;

                target.draw( ant );

                target.draw( rotations );
            }
    };

#endif /* ANT_HPP */