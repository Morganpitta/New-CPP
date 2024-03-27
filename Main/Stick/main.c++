#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f get2DUnitVector( float angle )
{
    return { sin( angle ), cos( angle ) };
}

class Stick
{
    sf::Vector2f position = {400,400};
    sf::Vector2f velocity = {0,0};
    sf::Vector2f acceleration = {0,0};
    float rotation = 0;
    float rotationalVelocity = 0;
    float rotationalAcceleration = 0;
    float length = 10;
    float mass = 100*10;
    float momentOfInteria = (1/12.f)*mass*length*length;

    public:
        Stick()
        {

        }

        void applyForceAtEnd( float amount )
        {
            rotationalAcceleration += amount / ( momentOfInteria * 100 );
            acceleration += (get2DUnitVector(rotation) * amount)/mass;
        }

        void update()
        {
            velocity += acceleration;
            position += velocity;
            rotationalVelocity += rotationalAcceleration;
            rotation += rotationalVelocity;
        }

        void display( sf::RenderWindow &window )
        {
            sf::RectangleShape rect({length,2});

            rect.setFillColor(sf::Color::Blue);
            rect.setOrigin(rect.getSize()/2.f);
            rect.setPosition(position/1000.f);
            rect.setRotation(-rotation);

            window.draw(rect);
        }
};

int main()
{
    sf::RenderWindow window( sf::VideoMode({800,800} ), "Stick" );
    Stick stick;

    while (true)
    {
        stick.applyForceAtEnd(0.1);
        stick.update();

        window.clear(sf::Color::White);

        stick.display(window);

        window.display();
    }

    return 0;
}