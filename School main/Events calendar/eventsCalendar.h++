#if !defined( EVENTS_CALENDAR_HPP )
#define EVENTS_CALENDAR_HPP

    #include "event.h++"
    #include "person.h++"
    
    class EventsCalendar
    {
        int nextEventId = 0;
        int nextPersonId = 0;

        public:
            EventsDatabase events;
            PeopleDatabase people;
            Database attendees;

            EventsCalendar( std::string file ): events(file), people(file), attendees(file)
            {
                attendees.execute( 
                    "CREATE TABLE IF NOT EXISTS Attendees("
                    "   EVENTID INT NOT NULL,"
                    "   PERSONID INT NOT NULL,"
                    "   PRIMARY KEY (EVENTID,PERSONID)"
                    ");"
                );
            }

            int addPerson( Person person )
            {
                if ( person.id == -1 )
                    person.id = nextPersonId++;
                people.add(person);
                return person.id;
            }

            int addEvent( Event event )
            {
                if ( event.id == -1 )
                    event.id = nextEventId++;
                events.add(event);
                return event.id;
            }

            void addAttendee( int eventId, int personId )
            {
                attendees.execute( 
                    "INSERT INTO Events (EVENTID,PERSONID) "
                    "VALUES ("
                    + std::to_string( eventId ) + ", "
                    + std::to_string( personId ) + " "
                    ");"
                );
            }

            Database::Table getAttendees( int eventId )
            {
                return attendees.execute(
                    "SELECT * FROM Attendees WHERE EVENTID = " + std::to_string( eventId ) + ";"
                );
            }

            Database::Table getPersonEvents( int personId )
            {
                return attendees.execute(
                    "SELECT * FROM Attendees WHERE PERSONID = " + std::to_string( personId ) + ";"
                );
            }
    };

#endif /* EVENTS_CALENDAR_HPP */