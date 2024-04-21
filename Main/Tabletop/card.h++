#if !defined ( CARD_HPP )
#define CARD_HPP

    #include <SFML/Graphics.hpp>

    typedef std::string CardType;

    class Card
    {
        const sf::Texture *backTexture;
        const sf::Texture *texture;
        CardType cardType;

        public:
            Card( CardType cardType, const sf::Texture *texture, const sf::Texture *backTexture ): cardType( cardType ), texture( texture ), backTexture( backTexture )
            {

            }

            CardType getType() const { return this->cardType; }
            const sf::Texture *getTexture() const { return this->texture; }
            const sf::Texture *getBackTexture() const { return this->backTexture; }
    };

#endif /* CARD_HPP */