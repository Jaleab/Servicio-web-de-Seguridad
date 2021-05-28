#include "ConectorModular.h"
#include<iostream>
#include <mysql/mysql.h>
#include <cstdlib>
using namespace std;

    struct connection_details{
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

    MYSQL* ConectorModular::connection(){
        MYSQL *con;	// the connection
        struct connection_details mysqlD;
        mysqlD.server = "localhost";  // where the mysql database is
        mysqlD.user = "comunicador"; // user
        mysqlD.password = "abcd1234!@#"; // the password for the database
        mysqlD.database = "prueba";     // the databse

        // connect to the mysql database        
        return mysql_connection_setup(mysqlD);
    }

    MYSQL_RES* ConectorModular::query(MYSQL* connection, const char* sql_query){        
        return mysql_perform_query(connection, sql_query);
    }
