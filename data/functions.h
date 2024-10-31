// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector> 
#include <string>
using namespace std;

double normal_pdf(double x, double mean, double std_dev);
double cumulative_distribution(double x, double mean, double std_dev);  // Function declaration
double random_normal(double mean, double std_dev);
vector<double> generate_data(double mean, double std, int points);
void test(double x, double mean, double std);
void write_data(const string& filename, const vector<double>& numbers1, const vector<double>& numbers2, const vector<double>& numbers3);
void clear_table(const string& filename);
void readTableFromFile(const string& filename, vector<double>& heartRates, vector<double>& bloodPressures, vector<double>& bodyTemperatures);
void readTableFromFile(const string& filename, const vector<int>& indices, vector<double>& heartRates, vector<double>& bloodPressures, vector<double>& bodyTemperatures);

#endif  // End of header guard
