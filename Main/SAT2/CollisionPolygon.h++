#if !defined( COLLISION_POLYGON_HPP )
#define COLLISION_POLYGON_HPP

    #include <SFML/System.hpp>
    #include <vector>

    float vectorDot( sf::Vector2f vector1, sf::Vector2f vector2 )
    {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

    class CollisionPolygon
    {
        typedef std::vector<sf::Vector2f> PolygonPoints;
        struct Projection
        {
            float min;
            float max;
        };

        public:
            virtual std::vector<sf::Vector2f> getPoints() const = 0;

            static bool isColliding( const CollisionPolygon *polygon1, const CollisionPolygon *polygon2 )
            {

            }
    };

#endif /* COLLISION_POLYGON_HPP */