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
                std::cout << "Enter id of event: ";
                std::getline( std::cin, input );
                int eventId = std::stoi( input );
                std::cout << "Enter id of attendee: ";
                std::getline( std::cin, input );
                
                calendar.addAttendee( eventId, std::stoi(input) );
                break;
            }
            case 4:    
                Database::Table events = calendar.events.execute( "SELECT * FROM Events" );
                for ( int index = 0; index < events["ID"].size(); index++ )
                {
                    std::cout << events["ID"][index] << ": " << events["NAME"][index] << " at " << events["DATE"][index] << std::endl;
                }
                break;
        }
    }

    return 0;
}