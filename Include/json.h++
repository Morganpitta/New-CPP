#if !defined( JSON_H )
#define JSON_H

    #include <nlohmann/json.hpp>
    #include "file.h++"

    // Documentation: https://github.com/nlohmann/json#read-json-from-a-file;

    // Literally just renaming for easier use. Thanks for the library nlohmann!
    typedef nlohmann::json Json; 

    Json parseFile( std::string fileName )
    {
        setWorkingDirectoryToDefault();
        std::ifstream file( fileName );
        assertCondition( file.is_open(), "Unable to open file" );
        return Json::parse( file );
    }

#endif /* JSON_H */