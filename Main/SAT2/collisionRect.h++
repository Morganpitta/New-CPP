#if !defined( COLLISION_RECT_HPP )
#define COLLISION_RECT_HPP

    #include "collisionPolygon.h++"

    class CollisionRect: public CollisionPolygon 
    {
        public:
            sf::Vector2f center;
            sf::Vector2f dimensions;
            float rotation;

            CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation = 0 ): center(center), dimensions(dimensions), rotation(rotation)
            {

            }

            PolygonPoints getPoints() const override
            {
                return {
                    center + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
                    center + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
                    center + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
                    center + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
                };
            }

            PolygonNormals getNormals() const override
            {
                return {
                    rotatePosition({1,0},rotation),
                    rotatePosition({1,0},rotation+M_PI/2.f)
                };
            }
    };

#endif /* COLLISION_RECT_HPP */