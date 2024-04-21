#if !defined( CARD_FACTOR_HPP )
#define CARD_FACTOR_HPP

    #include "card.h++"
    #include <set>
    #include <map>

    class CardFactory
    {
        static std::set<CardType> cardTypes;
        static std::map<CardType,sf::Texture*> cardTextures;
        static sf::Texture *backTexture;

        public:
            // Enforces singleton
            static CardFactory &GetInstance()
            {
                static CardFactory instance;
                return instance;
            }

            const std::set<CardType>& getCardTypes() const { return cardTypes; };
            const sf::Texture *getTexture( CardType cardType ) const { return cardTextures[cardType]; };

            bool hasCardType( CardType cardType ) const { return getCardTypes().count( cardType ) != 0; }

            void registerCard( CardType cardType, sf::Texture *texture )
            {
                cardTypes.insert( cardType );
                cardTextures[cardType] = texture;
            }

            Card *createCard( CardType cardType ) const
            {
                if ( !hasCardType( cardType ) )
                    return nullptr;
                return new Card( cardType, getTexture( cardType ), backTexture );
            }

            // Enforces singleton by preventing creation of new factories.
            CardFactory( const CardFactory& ) = delete;
            void operator=( const CardFactory& ) = delete;

        protected:
            // Protected so only this class can make an instance.
            CardFactory() 
            {
                cardTypes = {};
                cardTextures = {};
                backTexture = nullptr;
            }
    };

#endif /* CARD_FACTOR_HPP */