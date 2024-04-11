#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

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

float vectorDot( sf::Vector2f vector1, sf::Vector2f vector2 )
{
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

float absMin( float value1, float value2 )
{
    return abs(value1) < abs(value2) ? value1 : value2;
}

float lengthSquared( sf::Vector2f vector )
{
    return vector.x * vector.x + vector.y * vector.y;
}

float length( sf::Vector2f vector )
{
    return sqrt( lengthSquared(vector) );
}

bool invalidNormal( sf::Vector2f vector )
{
    return vector.x + 0.0f == 0.0f && vector.y + 0.0f == 0.0f;
}

class CollisionRect
{
    typedef std::vector<sf::Vector2f> PolygonPoints;
    struct Projection
    {
        float min;
        float max;

        bool contains( Projection projection2 )
        {
            return min <= projection2.min && projection2.min <= max ||
                   min <= projection2.max && projection2.max <= max; 
        }
    };

    public:
        sf::Vector2f center;
        sf::Vector2f dimensions;
        float rotation;

        CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation ): center(center), dimensions(dimensions), rotation(rotation)
        {
        }

        PolygonPoints getPoints() const
        {
            return {
                center + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
                center + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
                center + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
                center + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
            };
        }

        static Projection getProjection( const PolygonPoints &rect, sf::Vector2f projectionVector )
        {
            std::vector<float> dots;
            for ( int index = 0; index < rect.size(); index++ )
            {
                dots.push_back(vectorDot( rect[index], projectionVector ));
            }

            return {*std::min_element(dots.begin(),dots.end()), *std::max_element(dots.begin(),dots.end())};
        }

        static float overlap( Projection projection1, Projection projection2 )
        {
            if ( projection1.contains( projection2 ) || projection2.contains(projection1) )
            {
                float start = std::max(projection1.min,projection2.min);
                float end = std::min(projection1.max,projection2.max);
                return ( end - start );
            }

            return 0;
        }

        static float overlapOnVector( const PolygonPoints &rect1, const PolygonPoints &rect2, sf::Vector2f projectionVector )
        {
            Projection rect1Projection = getProjection(rect1, projectionVector);
            Projection rect2Projection = getProjection(rect2, projectionVector);

            return overlap(rect1Projection, rect2Projection);
        }

        static std::pair<bool,sf::Vector2f> isColliding( const CollisionRect &rect1, const CollisionRect &rect2 )
        {
            PolygonPoints rect1Points = rect1.getPoints();
            PolygonPoints rect2Points = rect2.getPoints();

            std::vector<sf::Vector2f> normals = { 
                { -(rect1Points[0].y - rect1Points[1].y), rect1Points[0].x - rect1Points[1].x },
                { -(rect1Points[1].y - rect1Points[2].y), rect1Points[1].x - rect1Points[2].x },
                { -(rect2Points[0].y - rect2Points[1].y), rect2Points[0].x - rect2Points[1].x },
                { -(rect2Points[1].y - rect2Points[2].y), rect2Points[1].x - rect2Points[2].x }
            };

            normals.erase( std::remove_if(
                normals.begin(),
                normals.end(), 
                invalidNormal
            ), normals.end() );

            if ( normals.size() == 0 )
                return std::make_pair(false,sf::Vector2f(0,0));

            std::pair<float,sf::Vector2f> smallestDistance = std::make_pair(0,sf::Vector2f(0,0));
            std::vector<std::pair<float,sf::Vector2f>> distances;

            for ( sf::Vector2f normal: normals )
            {
                float overlap = overlapOnVector(rect1Points,rect2Points,normal);
                if ( overlap != 0 )
                {
                    overlap /= length( normal );
                    if ( abs(smallestDistance.first) > abs(overlap) || smallestDistance.first == 0 )
                    {
                        normal /= length( normal );
                        smallestDistance = std::make_pair(overlap,normal);
                    }
                    distances.push_back(std::make_pair(overlap,normal));
                }
                else
                {
                    return std::make_pair(false,sf::Vector2f(0,0));
                }
            }

            // Minimum Translation Vector
            sf::Vector2f MTV = smallestDistance.first * smallestDistance.second;
            
            bool invertDirection = vectorDot(rect2.center - rect1.center, smallestDistance.second) < 0;
            if ( invertDirection )
                MTV *= -1.f;

            return std::make_pair(true,MTV);
        }

        void draw( sf::RenderWindow &window )
        {
            sf::RectangleShape rect( dimensions );

            rect.setOrigin( dimensions/2.f );
            rect.setPosition( center );
            rect.setRotation( -rotation * (180/M_PI) );
            rect.setFillColor(sf::Color::Blue);

            window.draw(rect);
        }
};

int main()
{
    sf::RenderWindow window( sf::VideoMode({800,800} ), "Rects" );

    std::vector<CollisionRect> rects;
    for ( int index = 0; index < 10; index++ )
    {
        rects.push_back( CollisionRect( {10*index,100}, {100,100}, 0 ) );
    }

    while ( window.isOpen() )
    {
        sf::Event event;
        while ( window.pollEvent(event) )
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseWheelScrolled:
                    rects[0].rotation += event.mouseWheelScroll.delta / 10.f;
                    break;
            }
        }

        rects[0].center = sf::Vector2f( sf::Mouse::getPosition(window) );

        for ( auto rect1 = rects.begin(); rect1 != rects.end(); rect1++ )
        {
            auto rect2 = rect1;
            for ( rect2++; rect2 != rects.end(); rect2++ )
            {
                CollisionRect::isColliding(*rect1,*rect2);
                std::pair<bool, sf::Vector2f> colliding = CollisionRect::isColliding(*rect1,*rect2);

                if ( colliding.first )
                {
                    (*rect1).center -= colliding.second/2.f;
                    (*rect2).center += colliding.second/2.f;
                }
            }
        }

        window.clear( sf::Color::Green );

        //rect2.rotation += 0.01;

        for ( CollisionRect &rect: rects )
        {
            rect.draw(window);
        }

        window.display();
    }

    return 0;
}