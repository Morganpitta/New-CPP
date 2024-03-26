#if !defined( DECK_HPP )
#define DECK_HPP

    #include "card.h++"
    #include <deque>


    class Deck
    {
        std::deque<CardType> cards;

        public:
            Deck( std::deque<CardType> cards = {} ): cards(cards) {}
            Deck( std::deque<CardType>::iterator begin, std::deque<CardType>::iterator end ): cards(begin,end) {}

            std::deque<CardType> &getCards() { return cards; }
            CardType peekTop() { return getCards().front(); }
            CardType removeTop() 
            { 
                CardType type = peekTop(); getCards().pop_front();
                return type;
            }

            Deck removeTop( int amount )
            {
                Deck deck(getCards().begin(),getCards().begin()+amount);
                getCards().erase(getCards().begin(),getCards().begin()+amount);
                return deck;
            }

            void addToTop( CardType )
    };

#endif /*DECK_HPP*/