#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "../child/child.h"
#include "../female/female.h"
#include "../male/male.h"
#include "../func/function.h"
#include <iomanip>

using namespace std;

// Structure to hold patient data
struct Patient {
    string name;
    int age;
    double heartRate;
    double bloodPressure;
    double temperature;
    bool isNormal;
};

// Function to determine age group based on age
int getAgeChoice(int age) {
    if (age < 1) return 1;  // Newborn
    else if (age == 1) return 2;  // Infant
    else if (age >= 1 && age <= 3) return 3;  // Toddler
    else if (age >= 3 && age <= 5) return 4;  // Preschooler
    else if (age >= 5 && age <= 12) return 5;  // School-aged
    else if (age >= 12 && age <= 18) return 6;  // Teenager
    else if (age >= 18 && age <= 65) return 7;  // Adult
    else return 8;  // Older adult
}

int main() {
    // Create instances of classes
    Child child;
    Male male;
    Female female;
    
    // Vectors to store patient data
    vector<Patient> patients;
    vector<Patient> normalPatients;
    vector<Patient> abnormalPatients;

    // Read from file
    ifstream inFile("data/my_data.txt");
    if (!inFile) {
        cerr << "Error: Unable to open my_data.txt" << endl;
        return 1;
    }
    
    string line;
    getline(inFile, line); // Skip header

    // Read and process each line
    while (getline(inFile, line)) {
        stringstream ss(line);
        Patient p;
        ss >> p.name >> p.age >> p.heartRate >> p.bloodPressure >> p.temperature;

        // Determine age group and process health checks
        int ageChoice = getAgeChoice(p.age);
        string ageGroup = assignAgeGroup(ageChoice);
        bool isNormal;

        if (ageChoice <= 6) {
            child.heartRate(ageGroup, p.heartRate);
            child.bloodPressure(ageGroup, p.bloodPressure, p.bloodPressure * 0.6); // Approximate diastolic
            child.temperature(ageGroup, p.temperature);
            isNormal = child.getHeartRateNormal() && 
                      child.getBloodPressureNormal() && 
                      child.getTemperatureNormal();
        } else {
            // Assume gender based on name (this is a simplification)
            bool isMalePatient = (p.name == "Pain" || p.name == "Nagato" || 
                                p.name == "Itachi" || p.name == "Tobi" || 
                                p.name == "Madara" || p.name == "Naruto" || 
                                p.name == "Kakashi");

            if (isMalePatient) {
                male.heartRate(p.age, p.heartRate);
                male.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                male.temperature(p.age, p.temperature);
                isNormal = male.getHeartRateNormal() && 
                          male.getBloodPressureNormal() && 
                          male.getTemperatureNormal();
            } else {
                female.heartRate(p.age, p.heartRate);
                female.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                female.temperature(p.age, p.temperature);
                isNormal = female.getHeartRateNormal() && 
                          female.getBloodPressureNormal() && 
                          female.getTemperatureNormal();
            }
        }

        p.isNormal = isNormal;
        patients.push_back(p);
        if (isNormal) {
            normalPatients.push_back(p);
        } else {
            abnormalPatients.push_back(p);
        }
    }

    // Display all patients with a clean format
    cout << "\nAll Patients:\n";
    cout << "-------------------------------------------------\n";
    for (const auto& p : patients) {
        cout << left << setw(15) << p.name 
             << "Age " << setw(3) << p.age << ": "
             << (p.isNormal ? "Normal" : "Abnormal") << endl;
    }

    // Display normal patients
    cout << "\nNormal Patients:\n";
    cout << "-------------------------------------------------\n";
    for (const auto& p : normalPatients) {
        cout << left << setw(15) << p.name << "Age " << p.age << endl;
    }

    // Display abnormal patients with details
    cout << "\nAbnormal Patients:\n";
    cout << "-------------------------------------------------\n";
    for (const auto& p : abnormalPatients) {
        cout << left << setw(15) << p.name << "Age " << setw(3) << p.age << endl;
        
        // Check each vital sign
        int ageChoice = getAgeChoice(p.age);
        string ageGroup = assignAgeGroup(ageChoice);
        
        if (ageChoice <= 6) {
            child.heartRate(ageGroup, p.heartRate);
            child.bloodPressure(ageGroup, p.bloodPressure, p.bloodPressure * 0.6);
            child.temperature(ageGroup, p.temperature);
            
            cout << "    Heart Rate: " << p.heartRate 
                 << (!child.getHeartRateNormal() ? " (Abnormal)" : "") << endl;
            cout << "    Blood Pressure: " << p.bloodPressure 
                 << (!child.getBloodPressureNormal() ? " (Abnormal)" : "") << endl;
            cout << "    Temperature: " << p.temperature 
                 << (!child.getTemperatureNormal() ? " (Abnormal)" : "") << endl;
        } else {
            bool isMalePatient = (p.name == "Pain" || p.name == "Nagato" || 
                                p.name == "Itachi" || p.name == "Tobi" || 
                                p.name == "Madara" || p.name == "Naruto" || 
                                p.name == "Kakashi");
            
            if (isMalePatient) {
                male.heartRate(p.age, p.heartRate);
                male.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                male.temperature(p.age, p.temperature);
                
                cout << "    Heart Rate: " << p.heartRate 
                     << (!male.getHeartRateNormal() ? " (Abnormal)" : "") << endl;
                cout << "    Blood Pressure: " << p.bloodPressure 
                     << (!male.getBloodPressureNormal() ? " (Abnormal)" : "") << endl;
                cout << "    Temperature: " << p.temperature 
                     << (!male.getTemperatureNormal() ? " (Abnormal)" : "") << endl;
            } else {
                female.heartRate(p.age, p.heartRate);
                female.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                female.temperature(p.age, p.temperature);
                
                cout << "    Heart Rate: " << p.heartRate 
                     << (!female.getHeartRateNormal() ? " (Abnormal)" : "") << endl;
                cout << "    Blood Pressure: " << p.bloodPressure 
                     << (!female.getBloodPressureNormal() ? " (Abnormal)" : "") << endl;
                cout << "    Temperature: " << p.temperature 
                     << (!female.getTemperatureNormal() ? " (Abnormal)" : "") << endl;
            }
        }
        cout << endl;
    }

    return 0;
}
