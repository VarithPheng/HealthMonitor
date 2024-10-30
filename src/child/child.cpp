#include <iostream>
#include <string>
#include "child.h"
using namespace std;

// Constructor
Child::Child() {
	isHeartRateNormal = false;
	isBloodPressureNormal = false;
	isTemperatureNormal = false;
}

void Child::heartRate(const string& ageGroup, int bpm) {
	if (bpm > 0) {
		if (ageGroup == "Newborn") {
			if (bpm >= 100 && bpm <= 205) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (ageGroup == "Infant") {
			if (bpm >= 100 && bpm <= 180) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (ageGroup == "Toddler") {
			if (bpm >= 98 && bpm <= 140) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (ageGroup == "Preschooler") {
			if (bpm >= 80 && bpm <= 120) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (ageGroup == "School-aged children") {
			if (bpm >= 75 && bpm <= 118) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (ageGroup == "Teenager") {
			if (bpm >= 60 && bpm <= 100) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}
	} else {
		cout << "Error: heart rate must be positive.";
	}
}


// sys for Systolic and dia for Diastolic (in excel sheet)
void Child::bloodPressure(const string& ageGroup, int sys, int dia) {
	if (sys > 0 && dia > 0) {
		if (ageGroup == "Newborn") {
			if ((sys >= 60 && sys <= 90) && (dia >= 20 && dia <= 60)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (ageGroup == "Infant") {
			if ((sys >= 87 && sys <= 105) && (dia >= 53 && dia <= 66)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (ageGroup == "Toddler") {
			if ((sys >= 95 && sys <= 105) && (dia >= 53 && dia <= 66)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (ageGroup == "Preschooler") {
			if ((sys >= 95 && sys <= 110) && (dia >= 56 && dia <= 70)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (ageGroup == "School-aged children") {
			if ((sys >= 97 && sys <= 112) && (dia >= 57 && dia <= 71)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (ageGroup == "Teenager") {
			if ((sys >= 112 && sys <= 128) && (dia >= 66 && dia <= 80)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}
	} else {
		cout << "Error: both systolic, and diastolic must be positive.";
	}
}


// in degree celsius
void Child::temperature(const string& ageGroup, double temp) {
	if (ageGroup == "Newborn" || ageGroup == "Infant" || ageGroup == "Toddler" ||
			ageGroup == "Preschooler" || ageGroup == "School-aged children") {

		if (temp >= 35.2 && temp <= 37.8) {
			isTemperatureNormal = true;
		} else {
			isTemperatureNormal = false;
		}
	}

	if (ageGroup == "Teenager") {
		if (temp >= 36.2 && temp <= 37.8) {
			isTemperatureNormal = true;
		} else {
			isTemperatureNormal = false;
		}
	}
}


// For encapsulation, we only use Getter (no Setter)
// because we don't need to manually modify the boolean values.
bool Child::getHeartRateNormal() const {
	return isHeartRateNormal;
}

bool Child::getBloodPressureNormal() const {
	return isBloodPressureNormal;
}

bool Child::getTemperatureNormal() const {
	return isTemperatureNormal;
}
