// g++ `mysql_config --cflags --libs` registro.cpp ConectorModular.cpp -o ../cgi-bin/login.cgi
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

/* INSERT INTO Usuario(correo, nombre, appelido1, apellido2, telefono, usuario, contraseña) VALUES('javier.abarca@ucr.ac.cr','Javier','Abarca','Jimenez','12345678','Jaleab','1234678');


Verificar campos de la base de datos Appelido1******
*/

    con = conectorModularPtr->connection();
    res = conectorModularPtr->query(con, "SELECT COUNT(*) FROM Usuario WHERE usuario = 'Jaleab' AND clave = '1234678';");
    cout << res[1] << "<br>";

    // clean up the database result
    mysql_free_result(res);
    
    // close database connection
    mysql_close(con);



    return 0;
}
