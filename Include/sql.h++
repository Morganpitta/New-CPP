#if !defined( SQL_HPP )
#define SQL_HPP

    #include "sqlite3.h"
    #include "assert.h++"
    #include <functional>
    #include <map>

    class Database
    {
        public:
            typedef std::map<std::string, std::string> Record;
            
            class Table
            {
                public:
                    std::vector<Record> records;
                    std::vector<std::string> attributes;

                    void clear()
                    {
                        records.clear();
                        attributes.clear();
                    }
            };

        private:
            sqlite3* database;
            bool error = false;
            std::string errorMessage = "";
            Table callbackValue;

            static int callbackWrapper(void *objPtr, int argc, char **argv, char **azColName) {
                return ((Database *)objPtr)->callback(argc, argv, azColName);
            }

            int callback( int numberOfColumns, char **items, char **columnNames )
            {
                Record record;
                for ( int index = 0; index < numberOfColumns; index++ )
                {
                    record[columnNames[index]] = items[index] == NULL ? "NULL" : items[index];
                }
                callbackValue.records.push_back( record );

                return 0;
            }

        public:
            Database( std::string file )
            {
                open( file );
            }

            void open( std::string file )
            {
                if ( sqlite3_open( file.c_str(), &this->database ) != SQLITE_OK )
                {
                    this->error = true;
                    this->errorMessage = sqlite3_errmsg( this->database );
                }
            }

            Table execute( std::string sql )
            {
                char *errorMessage = 0;
                callbackValue.clear();
                if ( sqlite3_exec( this->database, sql.c_str(), &callbackWrapper, this, &errorMessage ) != SQLITE_OK )
                {
                    this->error = true;
                    if ( errorMessage )
                    {
                        this->errorMessage = errorMessage;
                        sqlite3_free( errorMessage );
                    }
                }

                return callbackValue;
            }

            bool failed()
            {
                return this->error;
            }

            std::string getErrorMessage()
            {
                return this->errorMessage;
            }

            void close()
            {
                sqlite3_close( database );
            }

            ~Database()
            {
                close();
            }
    };

#endif /* SQL_HPP */