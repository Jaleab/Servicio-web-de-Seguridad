// g++ `mysql_config --cflags --libs` codigo/connector.cpp -o test
// ./test
#include <iostream>
// Verificar cual libreria tiene find /usr/ -name 'mysql.h'
#include <mysql/mysql.h> // /usr/includes/mariadb/mysql.h  /usr/includes/mysql/mysql.h
#include <cstdlib>

struct connection_details
{
    const char *server, *user, *password, *database;
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL); // mysql instance
    
    //connect database
    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)){
        std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1); 
    }

    return connection;
}

// mysql_res = mysql result
MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query){
    //send query to db
    if(mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }

    return mysql_use_result(connection);
}

int main(int argc, char const *argv[])
{
    MYSQL *con;	// the connection
    MYSQL_RES *res;	// the results
    MYSQL_ROW row;	// the results rows (array)

    struct connection_details mysqlD;
    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "comunicador"; // user
    mysqlD.password = "abcd1234!@#"; // the password for the database
    mysqlD.database = "prueba";	// the databse

    // connect to the mysql database
    con = mysql_connection_setup(mysqlD);

    // get the results from executing commands
    res = mysql_perform_query(con, "select * from Usuario;");

    std::cout << ("Database Output:\n") << std::endl;

    while ((row = mysql_fetch_row(res)) != NULL){
        // the below row[] parametes may change depending on the size of the table and your objective
        //std::cout << row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << " | " << row[4] << std::endl << std::endl;
        std::cout << row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << std::endl;
    }

    // clean up the database result
    mysql_free_result(res);
    
    // close database connection
    mysql_close(con);

    return 0;
}
