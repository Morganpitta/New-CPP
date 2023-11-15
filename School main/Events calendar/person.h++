#if !defined( PERSON_HPP )
#define PERSON_HPP

    #include "sql.h++"

    struct Person
    {
        std::string name;
        int id = -1;
    };

    class PeopleDatabase: public Database
    {
        public:
            PeopleDatabase( std::string file ): Database(file)
            {
                execute( 
                    "CREATE TABLE IF NOT EXISTS People("
                    "ID INT PRIMARY KEY NOT NULL,"
                    "NAME TEXT NOT NULL);" 
                );
            }

            Person get( int id )
            {
                Person person;
                Table data = execute( 
                    "SELECT * FROM People "
                    "WHERE ID = "+ std::to_string( id ) + ";"
                );

                person.id = std::stoi( data["ID"][0] );
                person.name = data["NAME"][0];

                return person;
            }

            void set( int id, Person person )
            {
                execute(
                    "UPDATE People "
                    "SET ID = " + std::to_string( person.id ) + " "
                    "NAME = " + person.name + " "
                    "WHERE ID = "+ std::to_string( id ) + ";"
                );
            }

            void add( Person person )
            {
                execute(
                    "INSERT INTO People (ID,NAME) "
                    "VALUES ("
                    + std::to_string( person.id ) + ", "
                    "'" + person.name + "'"
                    ");"
                );
            }
            
            bool has( int id )
            {
                Table data = execute(
                    "SELECT * FROM People WHERE ID = " + std::to_string(id) + ";"
                );

                return  data["ID"].size() > 0;
            }
    };

#endif /* PERSON_HPP */