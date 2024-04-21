#if !defined( COLLISION_RECT_HPP )
#define COLLISION_RECT_HPP

    #include "collidable.h++"

    class CollisionRect: public Collider 
    {
        sf::Vector2f dimensions;
        // Relative to the center of the rect.
        sf::Vector2f position;
        // In radians
        float rotation;

        public:
            CollisionRect( sf::Vector2f dimensions, sf::Vector2f position, float rotation = 0 ): dimensions(dimensions), position(position), rotation(rotation)
            {

            }

            PolygonPoints getPoints() const override
            {
                return {
                    position + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
                    position + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
                    position + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
                    position + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
                };
            }

            PolygonNormals getNormals() const override
            {
                return {
                    rotatePosition({1,0},rotation),
                    rotatePosition({1,0},rotation+M_PI/2.f)
                };
            }

            sf::Vector2f getDimensions() { return this->dimensions; };
            sf::Vector2f getPosition() { return this->position; };
            float getRotation() { return this->rotation; };

            void setDimensions( sf::Vector2f dimensions ) { this->dimensions = dimensions; };
            void setPosition( sf::Vector2f position ) { this->position = position; };
            void setRotation( float rotation ) { this->rotation = normaliseAngle( rotation ); };
            
            void move( sf::Vector2f amount ) { this->position += amount; };
            void rotate( float amount ) { setRotation( getRotation() + amount ); };
    };

#endif /* COLLISION_RECT_HPP */