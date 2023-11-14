#if !defined( EVENT_HPP )
#define EVENT_HPP

    #include "sql.h++"

    struct Event
    {
        int id;
        std::string name;
        std::string date;
    };

    class EventsDatabase: public Database
    {
        public:
            EventsDatabase( std::string file ): Database(file)
            {
                execute( 
                    "CREATE TABLE IF NOT EXISTS Events("
                    "'ID' INT PRIMARY KEY NOT NULL,"
                    "'NAME' TEXT NOT NULL,"
                    "'DATE' TEXT NOT NULL );" 
                );
            }

            Event get( int id )
            {
                Event event;
                Table data = execute( 
                    "SELECT * FROM Events "
                    "WHERE ID = "+ std::to_string( id ) + ";"
                );

                event.id = std::stoi( data["ID"][0] );
                event.name = data["NAME"][0];
                event.date = data["DATE"][0];

                return event;
            }

            void set( int id, Event event )
            {
                Table data = execute(
                    "UPDATE Events "
                    "SET ID = " + std::to_string( event.id ) + " "
                    "NAME = " + event.name + " "
                    "DATE = " + event.date + " "
                    "WHERE ID = "+ std::to_string( id ) + ";"
                );
            }

            void add( Event event )
            {
                Table data = execute(
                    "INSERT INTO Events (ID,NAME,DATE) "
                    "VALUES ("
                    + std::to_string( event.id ) + ", "
                    + event.name + ", "
                    + event.date +
                    ");"
                );
            }
    };

#endif /* EVENT_HPP */