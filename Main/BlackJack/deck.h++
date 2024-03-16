#if !defined( DECK_HPP )
#define DECK_HPP

    #include "card.h++"
    #include <deque>
    #include <algorithm>
    #include <random>

    std::default_random_engine rng = std::default_random_engine {};

    class Deck
    {
        std::deque<Card> cards;

        public:
            Deck()
            {
            }

            std::deque<Card> &getCards() { return this->cards; };

            Card peekTop()
            {
                return getCards().front();
            }

            Card peekBottom()
            {
                return getCards().back();
            }

            Card removeTop()
            {
                Card card = peekTop();
                getCards().pop_front();
                return card;
            };

            Card removeBottom()
            {
                Card card = peekBottom();
                getCards().pop_back();
                return card;
            };

            void addToBottom( Card card )
            {
                getCards().push_back( card );
            };

            void addToTop( Card card )
            {
                getCards().push_front( card );
            };

            void clear()
            {
                getCards().clear();
            }

            void shuffle()
            {
                std::shuffle( cards.begin(), cards.end(), rng );
            }

            operator std::string()
            {
                std::string string;
                std::string separator = "";

                for ( Card card: getCards() )
                {
                    string += separator + std::string( card );
                    separator = ", ";
                }

                return string;
            }
    };

    void resetDeck(Deck &deck)
    {
        deck.clear();
        forEachSuit( suit )
        {
            forEachCardType( type )
            {
                deck.addToBottom( Card(suit, type) );
            }
        }
    }

#endif /* DECK_HPP */