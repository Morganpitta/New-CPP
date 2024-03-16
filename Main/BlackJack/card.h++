#if !defined( CARD_HPP )
#define CARD_HPP

    #include <math.h>
    #include <string>

    enum SuitType
    {
        Clubs,
        Diamonds,
        Hearts,
        Spades,
        NumberOfSuits
    };

    std::string suitToString( SuitType suit )
    {
        switch( suit )
        {
            case Clubs: return "Clubs"; break;
            case Diamonds: return "Diamonds"; break;
            case Hearts: return "Hearts"; break;
            case Spades: return "Spades"; break;
        }
        
        return "Unknown";
    };

    #define forEachSuit( suit ) for ( SuitType suit = Clubs; suit < NumberOfSuits; suit = SuitType( int(suit) + 1 ) )

    enum CardType
    {
        Ace,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        NumberOfCardTypes
    };

    std::string cardTypeToString( CardType type )
    {
        switch( type )
        {
            case Ace: return "Ace"; break;
            case Two: return "Two"; break;
            case Three: return "Three"; break;
            case Four: return "Four"; break;
            case Five: return "Five"; break;
            case Six: return "Six"; break;
            case Seven: return "Seven"; break;
            case Eight: return "Eight"; break;
            case Nine: return "Four"; break;
            case Ten: return "Ten"; break;
            case Jack: return "Jack"; break;
            case Queen: return "Queen"; break;
            case King: return "King"; break;
        }

        return "Unknown";
    };

    #define forEachCardType( type ) for ( CardType type = Ace; type < NumberOfCardTypes; type = CardType( int(type) + 1 ) )

    int getTypeScore( CardType type )
    {
        return std::min(10, int(type)+1);
    }

    class Card
    {
        SuitType suit;
        CardType type;

        public:
            Card( SuitType suit, CardType type ): suit( suit ), type( type )
            {

            }

            SuitType getSuit() { return suit; }
            CardType getType() { return type; }

            void setSuit( SuitType suit ) { this->suit = suit; };
            void setType( CardType type ) { this->type = type; };

            operator std::string()
            {
                return cardTypeToString(type)+ " of " + suitToString(suit);
            }
    };

#endif /* CARD_HPP */