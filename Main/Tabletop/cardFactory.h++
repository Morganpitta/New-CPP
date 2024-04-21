#if !defined( CARD_FACTORY_HPP )
#define CARD_FACTORY_HPP

    #include "card.h++"
    #include <set>
    #include <map>

    class CardFactory
    {
        std::map<CardType,sf::Texture*> cardTextures;
        std::set<CardType> cardTypes;
        sf::Texture *backTexture;

        public:
            // Enforces singleton
            static CardFactory &GetInstance()
            {
                static CardFactory instance;
                return instance;
            }

            const std::set<CardType>& getCardTypes() const { return cardTypes; }
            bool hasCardType( CardType cardType ) const { return getCardTypes().count( cardType ) != 0; }
            const sf::Texture *getTexture( CardType cardType ) const { return cardTextures.at(cardType); }


            void registerCard( CardType cardType, sf::Texture *texture )
            {
                cardTypes.insert( cardType );
                cardTextures[cardType] = texture;
            }
            
            Card *createCard( CardId cardId, CardType cardType )
            {
                if ( !hasCardType( cardType ) )
                    return nullptr;
                return new Card( cardId, cardType, getTexture( cardType ), backTexture );
            }

            // Enforces singleton by preventing creation of new factories.
            CardFactory( const CardFactory& ) = delete;
            void operator=( const CardFactory& ) = delete;

        protected:
            // Protected so only this class can make an instance.
            CardFactory(): cardTypes(), cardTextures(), backTexture( nullptr )
            {
            }
    };

#endif /* CARD_FACTORY_HPP */