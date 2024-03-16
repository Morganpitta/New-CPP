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
                reset();
            }

            std::deque<Card> &getCards() { return this->cards; };

            Card dequeue() 
            { 
                Card card = this->cards.front();
                this->cards.pop_front();
                return card;
            };

            void addToBottom( Card card ) 
            { 
                this->cards.push_back( card );
            };

            void addToFront( Card card ) 
            { 
                this->cards.push_front( card );
            };

            void reset()
            {
                cards.clear();
                forEachSuit( suit )
                {
                    forEachCardType( type )
                    {
                        cards.push_back( Card(suit, type) );
                    }
                }
            }

            void shuffle()
            {
                std::shuffle( cards.begin(), cards.end(), rng );
            }

            operator std::string()
            {
                std::string string;

                for ( Card card: this->cards )
                {
                    string += std::string( card ) + ", ";
                }

                return string;
            }
    };

#endif /* DECK_HPP */