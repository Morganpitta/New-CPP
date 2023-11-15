#include "eventsCalendar.h++"
#include "file.h++"

int main()
{
    setWorkingDirectoryToDefault();

    EventsCalendar calendar( "Events Calendar/database.db" );
    
    std::string input;

    while ( true )
    {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "1. add person\n2. add event\n3. add attendee to event\n4. view all people\n5. view all events\n6. view persons events\n7. view event attendees\n";
        std::getline( std::cin, input );
        std::cout << "--------------------------------------------------" << std::endl;

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
                std::vector<std::string> people = calendar.getAllPeople();
                for ( std::string person: people )
                {
                    std::cout << person << std::endl;
                }

                break;
            }
            case 5:
            {
                std::vector<std::string> events = calendar.getAllEvents();
                for ( std::string event: events )
                {
                    std::cout << event << std::endl;
                }

                break;
            }
            case 6:
            {
                std::cout << "Enter name of person: ";
                std::getline( std::cin, input );

                std::vector<std::string> events = calendar.getEventByPerson( input );
                for ( std::string event: events )
                {
                    std::cout << event << std::endl;
                }

                break;
            }
            case 7:
            {
                std::cout << "Enter name of event: ";
                std::getline( std::cin, input );

                std::vector<std::string> people = calendar.getAttendees( input );
                for ( std::string person: people )
                {
                    std::cout << person << std::endl;
                }

                break;
            }
        }
    }

    return 0;
}