#include "eventsCalendar.h++"
#include "file.h++"

int main()
{
    setWorkingDirectoryToDefault();

    EventsCalendar calendar( "Events Calendar/database.db" );
    
    std::string input;

    while ( true )
    {
        std::cout << "1. add person\n2. add event\n3. add attendee to event\n4. view all events\n5. view all people\n6. view persons events\n7. view event attendees\n";
        std::getline( std::cin, input );

        switch( std::stoi(input) )
        {
            case 1:
                std::cout << "Enter name: ";
                std::getline( std::cin, input );

                calendar.addPerson( {input} );
                break;
            case 2:
            {
                std::cout << "Enter name: ";
                std::getline( std::cin, input );
                std::string name = input;
                std::cout << "Enter date: ";
                std::getline( std::cin, input );
                
                calendar.addEvent( {name, input} );
                break;
            }
            case 3:
            {
                std::cout << "Enter name of event: ";
                std::getline( std::cin, input );
                std::string eventName = input;
                std::cout << "Enter name of attendee: ";
                std::getline( std::cin, input );
                
                calendar.addAttendee( eventName, input );
                break;
            }
            case 4:
            {
                Database::Table events = calendar.execute( "SELECT * FROM Events" );
                for ( int index = 0; index < events.records.size(); index++ )
                {
                    Database::Record &record = events.records[index];
                    std::cout << record["name"] << " at " << record["Date"] << std::endl;
                }
                break;
            }
            case 5:
            {
                Database::Table events = calendar.execute( "SELECT * FROM People" );
                for ( int index = 0; index < events.records.size(); index++ )
                {
                    Database::Record &record = events.records[index];
                    std::cout << record["name"] << std::endl;
                }
                break;
            }
            case 6:
            {
                std::cout << "Enter name of person: ";
                std::getline( std::cin, input );
                Database::Table events = calendar.execute( "SELECT * FROM Attendees WHERE PersonId = " + input );
                for ( int index = 0; index < events.records.size(); index++ )
                {
                    Database::Record &record = events.records[index];
                    std::cout << record["EventName"] << std::endl;
                }
                break;
            }
            case 7:
            {
                std::cout << "Enter name of event: ";
                std::getline( std::cin, input );
                Database::Table events = calendar.execute( "SELECT * FROM Attendees WHERE EventId = " + input );
                for ( int index = 0; index < events.records.size(); index++ )
                {
                    Database::Record &record = events.records[index];
                    std::cout << record["PersonName"] << std::endl;
                }
                break;
            }
        }
    }

    return 0;
}