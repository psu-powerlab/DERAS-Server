#include <iostream>
#include "MySqlDatabase.h"
using namespace ::mysqlx;

MySqlDatabase::MySqlDatabase(const std::string& ip, const unsigned int port)
    : ip_address_(ip), port_(port)
{
    connect();
    // Get a list of all available schemas
    std::list<Schema> schemaList = session_->getSchemas();

    std::cout << "Available schemas in this session:" << std::endl;

    // Loop over all available schemas and print their name
    for (Schema schema : schemaList) {
        std::cout << schema.getName() << std::endl;
    }

    std::string create_db = R"(create database if not exists deras;)";

    std::string create_table = R"(
        CREATE TABLE IF NOT EXISTS deras.tasks (
            task_id INT AUTO_INCREMENT PRIMARY KEY,
            title VARCHAR(255) NOT NULL,
            start_date DATE,
            due_date DATE,
            status TINYINT NOT NULL,
            priority TINYINT NOT NULL,
            description TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    session_->sql(create_db).execute();

    session_->sql(create_table).execute();
}

MySqlDatabase::~MySqlDatabase()
{
    session_->close();
    delete session_;
}

// TODO: figure out what I should be returning. For the most part it should just
// be resource objects, but I might want to do other things.
void MySqlDatabase::query(std::string statement)
{
    session_->sql(statement).execute();
}

void MySqlDatabase::connect ()
{
    try {
            // Connect to MySQL Server on a network machine
            // *** CHANGE TO SOMETHING SECURE BEFORE IMPLEMENTING
            session_ = new Session (SessionOption::HOST, ip_address_,
                              SessionOption::PORT, port_,
                              SessionOption::USER, "root",
                              SessionOption::PWD, "1111");
            Schema schema_(*session_, "deras");
        }
    catch (const mysqlx::Error &err)
    {
      std::cout << "ERROR: " << err << std::endl;
    }
}
