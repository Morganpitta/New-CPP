#if !defined( BLACK_JACK_HPP )
#define BLACK_JACK_HPP

    #include "deck.h++"
    #include <iostream>

    #if defined(_WIN32)
        #define clear() system("cls")
    #else
        #define clear() system("clear")
    #endif

    std::string lower( std::string string )
    {
        std::transform(string.begin(), string.end(), string.begin(), ::tolower);
        return string;
    }

    class BlackJack
    {
        struct Player
        {
            Deck hand;
            bool standing = false;
            bool ai = false;
        };

        Deck deck;
        std::vector<Player> players;

        public:
            BlackJack( std::size_t numberOfPlayers )
            {
                resetDeck( deck );
                deck.shuffle();
                players.resize(numberOfPlayers, Player() );
                for ( int index = 0; index < 2; index++ )
                {
                    for ( Player &player: players )
                    {
                        player.hand.addToTop( deck.removeTop() );
                    }
                }
            }

            Player &getPlayer( std::size_t playerNumber )
            {
                return this->players[playerNumber];
            }

            bool handlePlayer( std::size_t playerNumber )
            {
                Player &player = getPlayer( playerNumber );
                if ( !player.standing )
                {
                    while ( true )
                    {
                        std::cout << "Your hand: " << std::string(player.hand) << "\n(Hit) or (Stand): ";
                        std::string response;
                        std::cin >> response;

                        if ( lower(response) == "hit")
                        {
                            Card card = deck.removeTop();
                            player.hand.addToBottom( card );
                            std::cout << "You got a: " << std::string( card ) << std::endl;
                        }
                        else if ( lower(response) == "stand" )
                        {
                            player.standing = true;
                            return true;
                        }
                        std::cout << "Invalid option\n";
                    }
                }
                return false;
            }

            void play()
            {
                int currentPlayer = 0;
                int standingPlayers = 0;

                while ( standingPlayers < players.size() )
                {
                    if ( handlePlayer(currentPlayer) )
                        standingPlayers++;

                    if ( ++currentPlayer >= players.size() ) currentPlayer = 0;
                }
            }
    };

#endif /* BLACK_JACK_HPP */