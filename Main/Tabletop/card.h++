#if !defined ( CARD_HPP )
#define CARD_HPP

    #include <SFML/Graphics.hpp>

    typedef std::string CardType;
    typedef int CardId;
    const CardId NullId = -1;

    class Card
    {
        const sf::Texture *backTexture;
        const sf::Texture *texture;
        CardType cardType;
        CardId cardId;

        public:
            Card( CardId id, CardType cardType, const sf::Texture *texture, const sf::Texture *backTexture ): backTexture( backTexture ), texture( texture ), cardType( cardType ), cardId( cardId )
            {

            }

            CardId getId() const { return this->cardId; }
            CardType getType() const { return this->cardType; }
            const sf::Texture *getTexture() const { return this->texture; }
            const sf::Texture *getBackTexture() const { return this->backTexture; }
    };

#endif /* CARD_HPP */