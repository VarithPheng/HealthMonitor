#include <iostream>
#include <string>

#include "../child/child.h"
#include "../female/female.h"
#include "../male/male.h"
#include "../func/function.h"

using namespace std;

int main() {
	// Create instances of classes
	Child child;
	Male male;
	Female female;

	// input
    string name, gender; // name and gender
    int ageChoice, exactAge; // for choice and real age
    string ageGroup; // Ex: Newborn, Teenager...
    int bpm; // Heart Rate
    int sys, dia; // Blood Pressure (Systolic and Diastolic)
    double temp; // Temperature

    cout << "Enter patient's name: ";
    getline(cin, name); // include space in name

    cout << "Enter patient's gender (Male / Female): ";
    cin >> gender;

    for (auto &c : gender) c = tolower(c); // convert gender input to lowercase

    cout << "Age Group\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Newborn [birth - 1 month]\n";
    cout << "2. Infant [1 month - 1 year]\n";
    cout << "3. Toddler [1 year - 3 years]\n";
    cout << "4. Preschooler [3 years - 5 years]\n";
    cout << "5. School-aged children [5 years - 12 years]\n";
    cout << "6. Teenager [12 years - 18 years]\n";
    cout << "7. Adult [18 years - 65 years]\n";
    cout << "8. Older adult [65 years or above]\n";

    cout << "Which group do you belong to? (Choose between 1 and 8): ";
    cin >> ageChoice;

    cout << "Enter heart beat per minute (bpm): ";
    cin >> bpm;

    cout << "Enter blood pressure (mm Hg) or (Systolic first and Diastolic second): ";
    cin >> sys >> dia;

    cout << "Enter temperature in celsius (°C): ";
    cin >> temp;

    if (ageChoice >= 1 && ageChoice <= 8) {
    	// Assign to each age group
    	ageGroup = assignAgeGroup(ageChoice);

    	// from Newborn to Teenager, gender is irrelevant
    	if (ageChoice <= 6) {
    		child.heartRate(ageGroup, bpm);
    		child.bloodPressure(ageGroup, sys, dia);
    		child.temperature(ageGroup, temp);

    		displayHealth(child.getHeartRateNormal(), child.getBloodPressureNormal(), child.getTemperatureNormal());

    	} else {
    		cout << "What is your exact age? (18 or above): ";
    		cin >> exactAge;

    		if (isMale(gender)) {
    			male.heartRate(exactAge, bpm);
    			male.bloodPressure(exactAge, sys, dia);
    			male.temperature(exactAge, temp);

    			displayHealth(male.getHeartRateNormal(), male.getBloodPressureNormal(), male.getTemperatureNormal());
    		} else {
    			female.heartRate(exactAge, bpm);
    			female.bloodPressure(exactAge, sys, dia);
    			female.temperature(exactAge, temp);

    			displayHealth(female.getHeartRateNormal(), female.getBloodPressureNormal(), female.getTemperatureNormal());
    		}
    	}

    } else {
    	cout << "Choose between 1 and 8.";
    }

    return 0;
}
