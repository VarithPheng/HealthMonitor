#include <iostream>
#include <string>
#include "function.h"
using namespace std;

// check if the input is male
bool isMale(string gender) {
    if (gender == "male") {
        return true;
    } else {
        return false;
    }
}

// check if the input is female
bool isFemale(string gender) {
    if (gender == "female") {
        return true;
    } else {
        return false;
    }
}

// assign the input into respective ageGroup
string assignAgeGroup(int ageGroup) {
    string ageGroupArray[8] = {
        "Newborn",
        "Infant",
        "Toddler",
        "Preschooler",
        "School-Aged Children",
        "Teenager",
        "Adult",
        "Older Adult"
    };
    return ageGroupArray[ageGroup - 1];
}

// Display Health for those who work on this part
void displayHealth(bool isHeartRateNormal, bool isBloodPressureNormal, bool isTemperatureNormal) {
	if (isHeartRateNormal && isBloodPressureNormal && isTemperatureNormal) {
		cout << "Everything is good!\n";

	} else {
		cout << "Your Heart Rate, Blood Pressure, and Temperature are abnormal. You need to see doctor ASAP!!!\n";
	}
}
