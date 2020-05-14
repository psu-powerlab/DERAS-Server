#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include <string>
#include <mysqlx/xdevapi.h>

class MySqlDatabase {
public:
    MySqlDatabase (const std::string& ip, const unsigned int port);

    ~MySqlDatabase ();

    void query (std::string statement);

private:
    void connect ();

    std::string ip_address_;
    unsigned int port_;
    mysqlx::Session* session_;
    mysqlx::Schema* schema_;
};

#endif // MYSQLDATABASE_H
