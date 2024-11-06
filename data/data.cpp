#include "data.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>
#include <iomanip>


using namespace std;

const double PI = 3.14159265358979323846;

double normal_pdf(double x, double mean, double std_dev) {
    return (1.0 / (std_dev * sqrt(2 * PI))) * exp(-0.5 * pow((x - mean) / std_dev, 2));
}

double cumulative_distribution(double x, double mean, double std_dev) {
    return 0.5 * (1 + erf((x - mean) / (std_dev * sqrt(2))));
}

double random_normal(double mean, double std_dev) {
    random_device rd;  // Obtain a random number from hardware
    mt19937 generator(rd());  // Seed the generator
    normal_distribution<double> distribution(mean, std_dev);  // Create a normal distribution

    return distribution(generator);  // Generate a random number
} 

void draw(double mean, double std_dev) {
    ofstream file("normal_distribution.dat");
    int num_points = 1000; // Set to 1000 points

    // Calculate the range from mean - 4*std_dev to mean + 4*std_dev
    double min_x = mean - 4 * std_dev;
    double max_x = mean + 4 * std_dev;
    
    // Generate 1000 points evenly spaced in this range
    for (int i = 0; i < num_points; ++i) {
        double x = min_x + i * (max_x - min_x) / (num_points - 1); // Evenly spaced points
        double y = normal_pdf(x, mean, std_dev);  // Use the probability density function
        file << x << " " << y << endl;
    }
    file.close();

    system("gnuplot -e \"set terminal png; set output 'normal_distribution.png'; plot 'normal_distribution.dat' with lines title 'Normal Distribution';\"");
}


vector<double> generate_data(double mean, double std, int points) {
    vector<double> data;
    for (int i = 0; i < points; ++i) {
        double random_x = random_normal(mean, std);
        if (mean == 98.25) {
            random_x = (random_x - 32.0) * 5.0/9.0;
        }
        data.push_back(random_x);
    }
    return data;
}

void test(double x, double mean, double std) {
    double probability = cumulative_distribution(x, mean, std);
    cout << "Randomly chosen X = " << x << " with cumulative probability: " << probability << endl;
}

void write_data(const string& filename, 
    const vector<string>& names,
    const vector<int>& ages,
    const vector<double>& numbers1, 
    const vector<double>& numbers2, 
    const vector<double>& numbers3) {
    
    ofstream outFile(filename, ios::app);

    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    if (outFile.tellp() == 0) {
        outFile << left 
                << setw(20) << "Name"
                << setw(10) << "Age"
                << setw(20) << "Heart Rate" 
                << setw(20) << "Blood Pressure" 
                << setw(20) << "Body Temperature" << endl;
    }

    size_t size = numbers1.size();
    for (size_t i = 0; i < size; ++i) {
        outFile << left 
                << setw(20) << names[i]
                << setw(10) << ages[i]
                << setw(20) << fixed << setprecision(4) << numbers1[i]
                << setw(20) << fixed << setprecision(4) << numbers2[i]
                << setw(20) << fixed << setprecision(4) << numbers3[i] << endl;
    }

    outFile.close();
    cout << "Data has been successfully written to " << filename << endl;
}

void clear_table(const string& filename) {
    ofstream outFile(filename);

    // Check if the file opened successfully
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Write header for the table with all columns
    outFile << left 
            << setw(20) << "Name"
            << setw(10) << "Age"
            << setw(20) << "Heart Rate" 
            << setw(20) << "Blood Pressure" 
            << setw(20) << "Body Temperature" << endl;

    // Close the file
    outFile.close();
    cout << "Data has been successfully cleared from " << filename << endl;
}


void readTableFromFile(const string& filename, vector<double>& heartRates, vector<double>& bloodPressures, vector<double>& bodyTemperatures) {
    ifstream inFile(filename);
    string line;

    // Skip the header line
    getline(inFile, line);

    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;  // temporary variables to skip name
        int age;      // temporary variables to skip age
        double heartRate, bloodPressure, bodyTemperature;

        // Read all values, including name and age
        ss >> name >> age >> heartRate >> bloodPressure >> bodyTemperature;

        // Only store the numerical values
        heartRates.push_back(heartRate);
        bloodPressures.push_back(bloodPressure);
        bodyTemperatures.push_back(bodyTemperature);
    }

    inFile.close();
}

void readTableFromFile(const string& filename, const vector<int>& indices, vector<double>& heartRates, vector<double>& bloodPressures, vector<double>& bodyTemperatures) {
    ifstream inFile(filename);
    string line;

    // Skip the header line
    getline(inFile, line);

    // Read through the file line by line
    int lineNumber = 0;
    while (getline(inFile, line)) {
        // Only process the lines that are in the specified indices
        if (find(indices.begin(), indices.end(), lineNumber) != indices.end()) {
            stringstream ss(line);
            string name;  // temporary variables to skip name
            int age;      // temporary variables to skip age
            double heartRate, bloodPressure, bodyTemperature;

            // Read all values, including name and age
            ss >> name >> age >> heartRate >> bloodPressure >> bodyTemperature;

            // Store only the numerical values
            heartRates.push_back(heartRate);
            bloodPressures.push_back(bloodPressure);
            bodyTemperatures.push_back(bodyTemperature);
        }
        lineNumber++; // Increment line number
    }

    inFile.close();
}

void generate_db_data(int num_records) {
    auto db = DatabaseConnection::getInstance();
    
    // Seed the random number generator
    srand(time(nullptr));
    
    // More realistic ranges for vital signs
    const double MIN_HEART_RATE = 60.0;
    const double MAX_HEART_RATE = 100.0;
    const double MIN_BLOOD_PRESSURE = 90.0;
    const double MAX_BLOOD_PRESSURE = 120.0;
    const double MIN_TEMP = 36.0;
    const double MAX_TEMP = 37.5;
    
    // Generate random patient data
    for (int i = 0; i < num_records; i++) {
        try {
            // Generate random values within normal ranges
            double heart_rate = MIN_HEART_RATE + (rand() % static_cast<int>((MAX_HEART_RATE - MIN_HEART_RATE) * 10)) / 10.0;
            double blood_pressure = MIN_BLOOD_PRESSURE + (rand() % static_cast<int>((MAX_BLOOD_PRESSURE - MIN_BLOOD_PRESSURE) * 10)) / 10.0;
            double temperature = MIN_TEMP + (rand() % static_cast<int>((MAX_TEMP - MIN_TEMP) * 10)) / 10.0;
            
            // Generate random name and age
            vector<string> names = {"Minato", "Pain", "Konan", "Nagato", "Itachi",
                                   "Tobi", "Madara", "Naruto", "Boruto", "Kakashi"};
            string name = names[rand() % names.size()];
            int age = 18 + (rand() % 50);  // Ages between 18 and 67
            string gender = (rand() % 2 == 0) ? "M" : "F";
            
            // Determine age group
            string age_group;
            if (age < 1) age_group = "Newborn";
            else if (age == 1) age_group = "Infant";
            else if (age <= 3) age_group = "Toddler";
            else if (age <= 5) age_group = "Preschooler";
            else if (age <= 12) age_group = "School-aged";
            else if (age <= 18) age_group = "Teenager";
            else if (age <= 65) age_group = "Adult";
            else age_group = "Older adult";
            
            // Insert patient
            string patient_query = "INSERT INTO patients (name, age, gender) VALUES ('" +
                                 name + "', " + to_string(age) + ", '" + gender + 
                                 "') RETURNING patient_id;";
            
            PGresult* res = db->executeQuery(patient_query.c_str());
            string patient_id = PQgetvalue(res, 0, 0);
            PQclear(res);
            
            // Insert vital signs
            string vitals_query = "INSERT INTO vital_signs (patient_id, heart_rate, blood_pressure, temperature, age_group) VALUES (" +
                                patient_id + ", " + to_string(heart_rate) + ", " +
                                to_string(blood_pressure) + ", " + to_string(temperature) +
                                ", '" + age_group + "');";
            
            res = db->executeQuery(vitals_query.c_str());
            PQclear(res);
            
        } catch (const exception& e) {
            cerr << "Error generating record " << i << ": " << e.what() << endl;
            continue;  // Skip to next record if there's an error
        }
    }
}

// int main() {

//     const double heart_mean = 65.9; const double heart_std = 9.7;
//     const double systolic_bp_mean = 110.1; const double systolic_bp_std = 9.9;
//     const double diastolic_bp_mean = 68.5; const double diastolic_bp_std = 8.7;
//     const double body_temp_mean = 36.8;  // 98.25°F converted to Celsius
//     const double body_temp_std = 0.4;    // 0.73°F converted to Celsius

//     draw(105, 2);

//     return 0;
// }





