#include "event.h++"

int main()
{
    EventsDatabase events("database.db");

    Database::Table data = events.execute(
                    "SELECT * FROM Events"
                );

    events.add( { 1, "name", "someday" } );
}