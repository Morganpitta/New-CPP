#if !defined( TABLETOP_CARD_HPP )
#define TABLETOP_CARD_HPP

    #include "card.h++"
    #include "Collision/collisionRect.h++"
    #include <deque>

    const sf::Vector2f cardDimensions = sf::Vector2f(25, 35) * 2.f;

    class CardCollection: public sf::Drawable
    {
        std::deque<Card *> cards;
        sf::Vector2f position;
        Collider *collider;
        float rotation;
        bool faceUp;

        public:
            CardCollection( 
                std::deque<Card *> cards,
                sf::Vector2f position = {0,0},
                bool faceUp = false
            ): cards( cards ), 
               collider( new CollisionRect( cardDimensions, position )), 
               position( position ), 
               faceUp( faceUp )
            {

            }

            CardCollection( 
                Card *card, 
                sf::Vector2f position = {0,0}, 
                bool faceUp = false 
            ): CardCollection( std::deque<Card*>{card}, position, faceUp )
            {

            }

            const Card *peekTopCard() const;
            const Card *peekBottomCard() const;
            sf::Vector2f getPosition() const;
            float getRotation() const;
            bool isFaceUp() const;

            const Collider *getCollider();

            Card *popTopCard();
            Card *popBottomCard();
            void addToTop( Card *card );
            void addToBottom( Card *card );

            void setPosition( sf::Vector2f position );
            void setRotation( float rotation );
            void setFaceUp( bool faceUp = true );
            
            void move( sf::Vector2f amount );
            void rotate( float amount );

            void combine( CardCollection &collection )
            {
                cards.insert( cards.begin(), collection.cards.begin(), collection.cards.end() );
                collection.cards.clear();
            }

            virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
    };

    const Card *CardCollection::peekTopCard() const { return this->cards.front(); }
    const Card *CardCollection::peekBottomCard() const { return this->cards.back(); }
    sf::Vector2f CardCollection::getPosition() const { return this->position; }
    float CardCollection::getRotation() const { return this->rotation; }
    bool CardCollection::isFaceUp() const { return this->faceUp; }

    const Collider *CardCollection::getCollider()
    {
        CollisionRect *collisionRect = dynamic_cast<CollisionRect*>( this->collider );
        collisionRect->setPosition( getPosition() );
        collisionRect->setRotation( getRotation() );
        return this->collider;
    }

    Card *CardCollection::popTopCard() { Card *card = this->cards.front(); this->cards.pop_front(); return card; }
    Card *CardCollection::popBottomCard() { Card *card = this->cards.back(); this->cards.pop_back(); return card; }
    void CardCollection::addToTop( Card *card ) { this->cards.push_front( card ); }
    void CardCollection::addToBottom( Card *card ) { this->cards.push_back( card ); }

    void CardCollection::setPosition( sf::Vector2f position ) { this->position = position; }
    void CardCollection::setRotation( float rotation ) { this->rotation = normaliseAngle( rotation ); }
    void CardCollection::setFaceUp( bool faceUp ) { this->faceUp = faceUp; }
    
    void CardCollection::move( sf::Vector2f amount ) { this->position += amount; }
    void CardCollection::rotate( float amount ) { setRotation( getRotation() + amount ); }

    void CardCollection::draw( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        const Card *topCard = peekTopCard();
        const sf::Texture *texture = faceUp ? topCard->getTexture() : topCard->getBackTexture();

        sf::RectangleShape rect( cardDimensions );
        rect.setOrigin( cardDimensions/2.f );
        rect.setPosition( getPosition() );
        rect.setRotation( -getRotation() * (180.f/M_PI) );

        target.draw( rect );
    }

#endif /* TABLETOP_CARD_HPP */