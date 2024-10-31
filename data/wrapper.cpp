#include <iostream>
#include "functions.h"
#include <vector>
#include <iomanip>
using namespace std;

const double heart_mean = 65.9; const double heart_std = 9.7;
const double systolic_bp_mean = 110.1; const double systolic_bp_std = 9.9;
const double diastolic_bp_mean = 68.5; const double diastolic_bp_std = 8.7;
const double body_temp_mean = 98.25; const double body_temp_std = 0.73;

vector<double> heartRates;
vector<double> bloodPressures;
vector<double> bodyTemperatures;

int main() {
    vector<double> heart_data = generate_data(heart_mean, heart_std, 1);
    vector<double> systolic_bp_data = generate_data(systolic_bp_mean, systolic_bp_std, 1);
    vector<double> body_temp_data = generate_data(body_temp_mean, body_temp_std, 1);


    // Call the function to write the table
    write_data("my_data.txt", heart_data, systolic_bp_data, body_temp_data);

    // Call the function to clear the table
    // clear_table("my_data.txt");

    // Read the table from the file
    // vector<int> indices = {1, 2, 4};
    // readTableFromFile("my_data.txt", indices, heartRates, bloodPressures, bodyTemperatures);

    // // Display the values
    // size_t size = sizeof(heart_data) / sizeof(systolic_bp_data);
    // cout << "Heart Rate" << setw(30) << "Blood Pressure" << setw(30) << "Body Temperature" << endl;
    // for (size_t i = 0; i < heartRates.size(); ++i) {
    //     cout << heartRates[i] << setw(30) << bloodPressures[i] << setw(30) << bodyTemperatures[i] << endl;;
    // }

    cout << (heart_data[0]) << endl;
    cout << (systolic_bp_data[0]) << endl;
    cout << (body_temp_data[0]) << endl;

    return 0;
    
}