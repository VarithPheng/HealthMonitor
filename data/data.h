#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include "../src/database/DatabaseConnection.h"

using namespace std;

// Statistical functions
double normal_pdf(double x, double mean, double std_dev);
double cumulative_distribution(double x, double mean, double std_dev);
double random_normal(double mean, double std_dev);
vector<double> generate_data(double mean, double std, int points);
void test(double x, double mean, double std);

// File operations
void write_data(
    const string& filename,
    const vector<string>& names,
    const vector<int>& ages,
    const vector<double>& heartRates,
    const vector<double>& bloodPressures,
    const vector<double>& bodyTemperatures
);

void clear_table(const string& filename);

// Read operations - all data
void readTableFromFile(
    const string& filename,
    vector<string>& names,
    vector<int>& ages,
    vector<double>& heartRates,
    vector<double>& bloodPressures,
    vector<double>& bodyTemperatures
);

// Read operations - numerical data only
void readTableFromFile(
    const string& filename,
    vector<double>& heartRates,
    vector<double>& bloodPressures,
    vector<double>& bodyTemperatures
);

// Read operations with indices
void readTableFromFile(
    const string& filename,
    const vector<int>& indices,
    vector<double>& heartRates,
    vector<double>& bloodPressures,
    vector<double>& bodyTemperatures
);

void readTableFromFile(
    const string& filename,
    const vector<int>& indices,
    vector<string>& names,
    vector<int>& ages,
    vector<double>& heartRates,
    vector<double>& bloodPressures,
    vector<double>& bodyTemperatures
);

void generate_db_data(int num_records);

#endif  // DATA_H