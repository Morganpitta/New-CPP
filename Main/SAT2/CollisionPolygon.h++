#if !defined( COLLISION_POLYGON_HPP )
#define COLLISION_POLYGON_HPP

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <cmath>

    float vectorDot( sf::Vector2f vector1, sf::Vector2f vector2 )
    {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

    float absMin( float value1, float value2 )
    {
        return abs(value1) < abs(value2) ? value1 : value2;
    }

    sf::Vector2f rotatePosition( sf::Vector2f position, float angle )
    {
        // The 2D rotation matrix
        return {
            static_cast<float>( 
                position.x*cos( angle ) + position.y*sin( angle )
            ),
            static_cast<float>( 
                - position.x*sin( angle ) + position.y*cos( angle )
            )
        };
    }

    class CollisionPolygon: public sf::Drawable
    {
        protected:
            typedef std::vector<sf::Vector2f> PolygonPoints;
            typedef std::vector<sf::Vector2f> PolygonNormals;

            struct Projection
            {
                float min;
                float max;

                bool contains( float value )
                {
                    return min <= value && value <= max;
                }

                static bool areOverlapping( Projection projection1, Projection projection2 )
                {
                    bool oneInsideTwo = projection2.contains( projection1.min ) ||
                                        projection2.contains( projection1.max ); 
                    bool twoInsideOne = projection1.contains( projection2.min ) ||
                                        projection1.contains( projection2.max ); 

                    return oneInsideTwo || twoInsideOne;
                }

                static float getOverlap( Projection projection1, Projection projection2 )
                {
                    float overlap1 = projection2.max - projection1.min;
                    float overlap2 = projection2.min - projection1.max;

                    return absMin( overlap1, overlap2 );
                }
            };

            static Projection project( sf::Vector2f normal, PolygonPoints points )
            {
                float dot = vectorDot(normal,points[0]);
                Projection projection = { dot, dot };
                for ( int index = 1; index < points.size(); index++ )
                {
                    float dot = vectorDot(normal,points[index]);
                    if ( dot < projection.min ) projection.min = dot;
                    if ( dot > projection.max ) projection.max = dot;
                }

                return projection;
            }

            static bool containsAlongNormal( sf::Vector2f normal, PolygonPoints points, sf::Vector2f point )
            {
                Projection projection = project( normal, points );
                float dot = vectorDot( normal, point );

                return projection.contains( dot );
            }

            static bool areOverlappingAlongNormal( sf::Vector2f normal, PolygonPoints points1, PolygonPoints points2 )
            {
                Projection projection1 = project( normal, points1 );
                Projection projection2 = project( normal, points2 );

                return Projection::areOverlapping( projection1, projection2 );
            }

            static float getOverlapAlongNormal( sf::Vector2f normal, PolygonPoints points1, PolygonPoints points2 )
            {
                Projection projection1 = project( normal, points1 );
                Projection projection2 = project( normal, points2 );

                if ( !areOverlappingAlongNormal( normal, points1, points2 ) )
                    return 0;

                return Projection::getOverlap( projection1, projection2 );
            }

        public:
            virtual PolygonPoints getPoints() const = 0;
            virtual PolygonNormals getNormals() const = 0;

            bool contains( sf::Vector2f position )
            {
                PolygonPoints points = getPoints();
                PolygonNormals normals = getNormals();

                for ( sf::Vector2f normal: normals )
                {
                    if ( !containsAlongNormal( normal, points, position ) )
                        return false;
                }

                return true;
            }

            static bool areColliding( const CollisionPolygon *polygon1, const CollisionPolygon *polygon2 )
            {
                PolygonPoints points1 = polygon1->getPoints();
                PolygonPoints points2 = polygon2->getPoints();

                PolygonNormals normals = polygon1->getNormals();
                PolygonNormals normalsTmp = polygon2->getNormals();
                normals.insert( normals.end(), normalsTmp.begin(), normalsTmp.end() );

                for ( sf::Vector2f normal: normals )
                {
                    if ( !areOverlappingAlongNormal( normal, points1, points2 ) )
                        return false;
                }

                return true;
            }

            static sf::Vector2f getCollision( const CollisionPolygon *polygon1, const CollisionPolygon *polygon2 )
            {
                PolygonPoints points1 = polygon1->getPoints();
                PolygonPoints points2 = polygon2->getPoints();

                PolygonNormals normals = polygon1->getNormals();
                PolygonNormals normalsTmp = polygon2->getNormals();
                normals.insert( normals.end(), normalsTmp.begin(), normalsTmp.end() );

                float mtvDistance = 0; sf::Vector2f mtvDirection = {0,0};
                for ( sf::Vector2f normal: normals )
                {
                    float overlap = getOverlapAlongNormal( normal, points1, points2 );
                    if ( overlap == 0 )
                        return {0,0};
                    
                    if ( mtvDistance == 0 || abs(overlap) < abs(mtvDistance) )
                    {
                        mtvDistance = overlap;
                        mtvDirection = normal;
                    }
                }

                return mtvDistance * mtvDirection;
            }

            virtual void draw( sf::RenderTarget& target, sf::RenderStates states) const
            {
                PolygonPoints points = getPoints();

                sf::VertexArray array( sf::PrimitiveType::TriangleFan, points.size() );

                for ( int index = 0; index < points.size(); index++ )
                {
                    array[index] = sf::Vertex( points[index] );
                }

                target.draw( array, states );
            }
    };

#endif /* COLLISION_POLYGON_HPP */