#include "databaseConnection.h"
#include <libpq-fe.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace std;

DatabaseConnection::DatabaseConnection()
    : conn(nullptr) {
    connectionInfo = getConnectionInfo();
}

PGconn* DatabaseConnection::getConnection() {
    if (!conn) {
        conn = PQconnectdb(connectionInfo.c_str());
        if (PQstatus(conn) != CONNECTION_OK) {
            cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
            PQfinish(conn);
            conn = nullptr;
        }
    }
    return conn;
}

DatabaseConnection::~DatabaseConnection() {
    if (conn) {
        PQfinish(conn);
    }
}

string DatabaseConnection::getConnectionInfo() {
    ifstream file("src/env.json");
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open env.json");
    }

    nlohmann::json config;
    file >> config;

    string connectionInfo = 
        "host=localhost" 
        " port=" + config["port"].get<string>() +
        " dbname=" + config["dbname"].get<string>() +
        " user=" + config["user"].get<string>() +
        " password=" + config["password"].get<string>();

    return connectionInfo;
}

void DatabaseConnection::insertPatientData(PGconn* conn, const string& name, const string& gender, const string& ageGroup,
    const string& exactAge, int heartRate, int bloodPressure1, int bloodPressure2, double temperature) {
    string sql = "INSERT INTO patient_health_data (name, gender, ageGroup, exactAge, heartRate, bloodPressure1, bloodPressure2, temperature) "
                 "VALUES ($1, $2, $3, $4, $5, $6, $7, $8);";

    string heartRateStr = to_string(heartRate);
    string bloodPressure1Str = to_string(bloodPressure1);
    string bloodPressure2Str = to_string(bloodPressure2);
    string temperatureStr = to_string(temperature);

    const char* paramValues[8] = { name.c_str(), gender.c_str(), ageGroup.c_str(), exactAge.c_str(), 
                                  heartRateStr.c_str(), bloodPressure1Str.c_str(), bloodPressure2Str.c_str(), 
                                  temperatureStr.c_str() };

    PGresult* res = PQexecParams(conn, sql.c_str(), 8, nullptr, paramValues, nullptr, nullptr, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        cerr << "Insert failed: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        return;
    }

    PQclear(res);
    cout << "Data inserted successfully!" << endl;
}

void DatabaseConnection::retrievePatientId(PGconn* conn, int& id, string name) {
    string query = "SELECT id FROM patient_health_data WHERE name = '" + name + "';";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        cerr << "Query failed: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        return;
    }

    int numRows = PQntuples(res);
    if (numRows == 0) {
        cerr << "No patient found with ID " << id << endl;
        PQclear(res);
        return;
    }

    id = stoi(PQgetvalue(res, 0, 0));
    PQclear(res);
}

void DatabaseConnection::retrievePatientData(PGconn* conn, int id, string& name, string& gender, string& ageGroup,
    string& exactAge, int& heartRate, int& bloodPressure1, int& bloodPressure2, double& temperature) {
    string query = "SELECT name, gender, ageGroup, exactAge, heartRate, bloodPressure1, bloodPressure2, temperature "
                  "FROM patient_health_data WHERE id = $1;";

    string idStr = to_string(id);
    const char* paramValues[1] = { idStr.c_str() };

    PGresult* res = PQexecParams(conn, query.c_str(), 1, nullptr, paramValues, nullptr, nullptr, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        cerr << "Query failed: " << PQerrorMessage(conn) << endl;
        PQclear(res);
        return;
    }

    int numRows = PQntuples(res);
    if (numRows == 0) {
        cerr << "No patient found with ID " << id << endl;
        PQclear(res);
        return;
    }

    name = string(PQgetvalue(res, 0, 0));
    gender = string(PQgetvalue(res, 0, 1));
    ageGroup = string(PQgetvalue(res, 0, 2));
    exactAge = string(PQgetvalue(res, 0, 3));
    heartRate = stoi(PQgetvalue(res, 0, 4));
    bloodPressure1 = stoi(PQgetvalue(res, 0, 5));
    bloodPressure2 = stoi(PQgetvalue(res, 0, 6));
    temperature = round(stof(PQgetvalue(res, 0, 7)) * 10) / 10;

    PQclear(res);
}