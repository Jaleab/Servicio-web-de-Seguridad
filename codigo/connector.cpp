// g++ `mysql_config --cflags --libs` connector.cpp ConectorModular.cpp -o Consulta
// ./Consulta
#include <iostream>
#include <mysql/mysql.h> // /usr/includes/mariadb/mysql.h  /usr/includes/mysql/mysql.h
#include <cstdlib>
#include "ConectorModular.h"

int main(int argc, char const *argv[])
{
    ConectorModular* conectorModularPtr;
    MYSQL* con;
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    con = conectorModularPtr->connection();
    res = conectorModularPtr->query(con, "SELECT COUNT(*) FROM Usuario WHERE usuario = 'Jaleab' AND clave = '1234678';");

    std::cout << ("Database Output:\n") << std::endl;

    while ((row = mysql_fetch_row(res)) != NULL){
        // the below row[] parametes may change depending on the size of the table and your objective
        //std::cout << row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << " | " << row[4] << std::endl << std::endl;
        std::cout << row[0] << " | " << row[1] << " | " << row[2] << std::endl;
    }

    // clean up the database result
    mysql_free_result(res);
    
    // close database connection
    mysql_close(con);

    return 0;
}
