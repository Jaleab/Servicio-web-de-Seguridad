#ifndef _CONECTORMODULAR
#define _CONECTORMODULAR
#include <mysql/mysql.h>

class ConectorModular {
   public:
      MYSQL* connection();
      MYSQL_RES* query(MYSQL* connection, const char* sql_query);
};
#endif
