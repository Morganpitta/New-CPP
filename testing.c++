#include "sql.h++"

int main()
{
    Database database("database.db");

    database.execute( "CREATE TABLE COMPANY("
      "ID INT PRIMARY KEY NOT NULL,"
      "NAME TEXT NOT NULL,"
      "AGE INT NOT NULL,"
      "ADDRESS CHAR(50),"
      "SALARY REAL );" );

    database.execute(
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
      "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
      "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
      "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );"
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
      "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );" );

    Database::Table data = database.execute( "SELECT * from COMPANY" );

    return 0;
}