#if !defined( EVENTS_CALENDAR_HPP )
#define EVENTS_CALENDAR_HPP

    #include "sql.h++"
    
    struct Person
    {
        std::string name;
    };

    struct Event
    {
        std::string name;
        std::string date;
    };
    
    class EventsCalendar: public Database
    {
        public:
            EventsCalendar( std::string file ): Database( file )
            {
                execute( 
                    "CREATE TABLE IF NOT EXISTS People("
                    "   Name VARCHAR(255) NOT NULL"
                    ");"
                );

                execute( 
                    "CREATE TABLE IF NOT EXISTS Events("
                    "   Name VARCHAR(255) NOT NULL,"
                    "   Date VARCHAR(255) NOT NULL"
                    ");"
                );

                execute( 
                    "CREATE TABLE IF NOT EXISTS Attendees("
                    "   EventName VARCHAR(255) NOT NULL,"
                    "   PersonName VARCHAR(255) NOT NULL,"
                    "   PRIMARY KEY ( EventName, PersonName )"
                    ");"
                );
            }

            void addPerson( Person person )
            {
                execute(
                    "INSERT INTO People ( Name )"
                    "Values("
                    "'" + person.name + "'"
                    ")"
                );
            }

            void addEvent( Event event )
            {
                execute(
                    "INSERT INTO Events ( Name, Date )"
                    "Values("
                    "'" + event.name + "',"
                    "'" + event.date + "'"
                    ")"
                );
            }

            void addAttendee( std::string eventName, std::string personName )
            {
                execute(
                    "INSERT INTO Attendees ( EventName, PersonName )"
                    "Values("
                    "'" + eventName + "',"
                    "'" + personName + "'"
                    ")"
                );
            }

            std::vector<std::string> getAllPeople()
            {
                Database::QueryResult data = execute( "SELECT * FROM People" );
                std::vector<std::string> people;
                for ( int index = 0; index < data.records.size(); index++ )
                {
                    Database::Record &record = data.records[index];
                    people.push_back( record["Name"] );
                }

                return people;
            }

            std::vector<std::string> getAllEvents()
            {
                Database::QueryResult data = execute( "SELECT * FROM Events" );
                std::vector<std::string> events;
                for ( int index = 0; index < data.records.size(); index++ )
                {
                    Database::Record &record = data.records[index];
                    events.push_back( record["Name"] );
                }

                return events;
            }

            std::vector<std::string> getEventByPerson( std::string personName )
            {
                Database::QueryResult data = execute( "SELECT * FROM Attendees WHERE PersonName = '" + personName + "'" );
                std::vector<std::string> events;
                for ( int index = 0; index < data.records.size(); index++ )
                {
                    Database::Record &record = data.records[index];
                    events.push_back( record["EventName"] );
                }

                return events;
            }

            std::vector<std::string> getAttendees( std::string eventName )
            {
                Database::QueryResult data = execute( "SELECT * FROM Attendees WHERE EventName = '" + eventName + "'" );
                std::vector<std::string> people;
                for ( int index = 0; index < data.records.size(); index++ )
                {
                    Database::Record &record = data.records[index];
                    people.push_back( record["PersonName"] );
                }

                return people;
            }
    };

#endif /* EVENTS_CALENDAR_HPP */