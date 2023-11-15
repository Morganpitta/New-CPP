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
        int nextEventId = 0;
        int nextPersonId = 0;

        public:

            EventsCalendar( std::string file ): Database( file )
            {
                execute( 
                    "CREATE TABLE IF NOT EXISTS People("
                    "   Name VARCHAR(255) NOT NULL,"
                    ");"
                );

                execute( 
                    "CREATE TABLE IF NOT EXISTS Events("
                    "   Name VARCHAR(255) NOT NULL,"
                    "   Date VARCHAR(255) NOT NULL,"
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
                    + person.name +
                    ")"
                );
            }

            void addEvent( Event event )
            {
                execute(
                    "INSERT INTO Events ( Name, Date )"
                    "Values("
                    + event.name + ","
                    + event.date +
                    ")"
                );
            }

            void addAttendee( std::string eventName, std::string personName )
            {
                execute(
                    "INSERT INTO Attendees ( EventName, PersonName )"
                    "Values("
                    + eventName + ","
                    + personName +
                    ")"
                );
            }
    };

#endif /* EVENTS_CALENDAR_HPP */