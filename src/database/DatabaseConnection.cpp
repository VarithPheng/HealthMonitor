#include "DatabaseConnection.h"
#include <stdexcept>

DatabaseConnection::DatabaseConnection(const char* conninfo) {
    conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        throw std::runtime_error(std::string("Connection to database failed: ") + PQerrorMessage(conn));
    }
}

DatabaseConnection::~DatabaseConnection() {
    if (conn) {
        PQfinish(conn);
    }
}

PGresult* DatabaseConnection::executeQuery(const char* query) {
    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string error = PQerrorMessage(conn);
        PQclear(res);
        throw std::runtime_error("Query failed: " + error);
    }
    return res;
}

std::shared_ptr<DatabaseConnection> DatabaseConnection::getInstance() {
    static std::shared_ptr<DatabaseConnection> instance(
        new DatabaseConnection("dbname=test user=postgres password=tii007 hostaddr=127.0.0.1 port=5432")
    );
    return instance;
} 