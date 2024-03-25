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

class CollisionRect
{
    typedef std::vector<sf::Vector2f> PolygonPoints;

    public:
        sf::Vector2f center;
        sf::Vector2f dimensions;
        float rotation;

        CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation ): center(center), dimensions(dimensions), rotation(rotation)
        {
        }

        PolygonPoints toPoints() const
        {
            return {
                center + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
                center + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
                center + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
                center + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
            };
        }

        static std::pair<float,float> minAndMaxPoints( const PolygonPoints &rect, sf::Vector2f projectionVector )
        {
            std::vector<float> dots;
            for ( int index = 0; index < rect.size(); index++ )
            {
                dots.push_back(vectorDot( rect[index], projectionVector ));
            }

            return std::make_pair(*std::min_element(dots.begin(),dots.end()), *std::max_element(dots.begin(),dots.end()));
        }

        static bool isCollidingOnVector( const PolygonPoints &rect1, const PolygonPoints &rect2, sf::Vector2f projectionVector )
        {
            std::pair<float,float> rect1MinAndMax = minAndMaxPoints(rect1, projectionVector);
            std::pair<float,float> rect2MinAndMax = minAndMaxPoints(rect2, projectionVector);

            return rect1MinAndMax.first < rect2MinAndMax.first && rect2MinAndMax.first < rect1MinAndMax.second ||
                   rect2MinAndMax.first < rect1MinAndMax.first && rect1MinAndMax.first < rect2MinAndMax.second;
        }

        std::pair<bool,sf::Vector2f> isColliding( const CollisionRect &rect ) const
        {
            PolygonPoints selfPoints = toPoints();
            PolygonPoints rectPoints = rect.toPoints();

            std::vector<sf::Vector2f> normals = { 
                { -(selfPoints[0].y - selfPoints[1].y), selfPoints[0].x - selfPoints[1].x },
                { -(selfPoints[1].y - selfPoints[2].y), selfPoints[1].x - selfPoints[2].x },
                { -(rectPoints[0].y - rectPoints[1].y), rectPoints[0].x - rectPoints[1].x },
                { -(rectPoints[1].y - rectPoints[2].y), rectPoints[1].x - rectPoints[2].x }
            };

            for ( sf::Vector2f normal: normals )
            {
                if ( !isCollidingOnVector(selfPoints,rectPoints,normal) )
                    return std::make_pair(false,normal);
            }

            return std::make_pair(true,sf::Vector2f(0,0));
        }

        void draw( sf::RenderWindow &window )
        {
            sf::RectangleShape rect( dimensions );
            rect.setOrigin( dimensions/2.f );
            rect.setPosition( center );
            rect.setRotation( rotation * (180/M_PI) );
            rect.setFillColor(sf::Color::Blue);

            window.draw(rect);
        }
};

int main()
{
    sf::RenderWindow window( sf::VideoMode({800,800} ), "Rects" );

    CollisionRect rect1( {100,100}, {100,100}, 0 );
    CollisionRect rect2( {300,100}, {100,100}, 0 );

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
                    rect1.rotation += event.mouseWheelScroll.delta / 10.f;
                    break;
            }
        }

        rect1.center = sf::Vector2f( sf::Mouse::getPosition(window) );

        std::pair<bool, sf::Vector2f> colliding = rect1.isColliding(rect2);

        window.clear( !colliding.first? sf::Color::White : sf::Color::Green );

        if ( true )
        {
            sf::VertexArray line(sf::PrimitiveType::Lines,2);
            line[0].position = {100,100};
            line[0].color = sf::Color::Black;
            line[1].position = sf::Vector2f(100,100) + colliding.second;
            line[1].color = sf::Color::Black;
            window.draw(line);
        }

        rect1.draw(window);
        rect2.draw(window);

        window.display();
    }

    return 0;
}