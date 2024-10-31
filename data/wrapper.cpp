#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include "data.h"

using namespace std;

// Constants for vital signs
const double heart_mean = 65.9;
const double heart_std = 9.7;
const double systolic_bp_mean = 110.1;
const double systolic_bp_std = 9.9;
const double diastolic_bp_mean = 68.5;
const double diastolic_bp_std = 8.7;
const double body_temp_mean = 98.25;
const double body_temp_std = 0.73;

// Number of records to generate
const int NUM_RECORDS = 10;

// Character names database
const vector<string> character_names = {
    "Minato",   "Pain",   "Konan", "Nagato", "Itachi",
    "Tobi",   "Madara", "Naruto", "Boruto", "Kakashi"
};

// Helper function to get random name
string get_random_name() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, character_names.size() - 1);
    return character_names[dis(gen)];
}

// Helper function to get random age between 1 and 69
int get_random_age() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 69);
    return dis(gen);
}

int main() {
    // Initialize data vectors
    vector<string> name_data;
    vector<int> age_data;
    
    // Generate random data for 80 records
    for(int i = 0; i < NUM_RECORDS; i++) {
        name_data.push_back(get_random_name());
        age_data.push_back(get_random_age());
    }
    
    vector<double> heart_data = generate_data(heart_mean, heart_std, NUM_RECORDS);
    vector<double> systolic_bp_data = generate_data(systolic_bp_mean, systolic_bp_std, NUM_RECORDS);
    vector<double> body_temp_data = generate_data(body_temp_mean, body_temp_std, NUM_RECORDS);

    // Clear the file before writing new data
    clear_table("data/my_data.txt");

    // Write data to file
    write_data("data/my_data.txt", 
               name_data, 
               age_data, 
               heart_data, 
               systolic_bp_data, 
               body_temp_data);

    // Display summary
    cout << "Generated " << NUM_RECORDS << " records successfully!" << endl;
    cout << "Data has been written to data/my_data.txt" << endl;

    return 0;
}