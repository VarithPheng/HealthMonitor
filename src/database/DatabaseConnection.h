#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <libpq-fe.h>
#include <memory>
#include <string>

class DatabaseConnection {
private:
    PGconn* conn;
    DatabaseConnection(const char* conninfo);

public:
    ~DatabaseConnection();
    PGresult* executeQuery(const char* query);
    static std::shared_ptr<DatabaseConnection> getInstance();
};

#endif 