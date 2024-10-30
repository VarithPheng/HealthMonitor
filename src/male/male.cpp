#include <iostream>
#include <string>
#include "../child/child.h"
#include "male.h"
using namespace std;

Male::Male() {
	isHeartRateNormal = false;
	isBloodPressureNormal = false;
	isTemperatureNormal = false;
}

// Override the heartRate function in class Child
void Male::heartRate(int age, int bpm) {
	if (age > 0 && bpm > 0) {
		if (age >= 18 && age <= 25) {
			if (bpm >= 62 && bpm <= 73) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age >= 26 && age <= 35) {
			if (bpm >= 62 && bpm <= 74) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age >= 36 && age <= 45) {
			if (bpm >= 63 && bpm <= 75) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age >= 46 && age <= 55) {
			if (bpm >= 63 && bpm <= 76) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age >= 56 && age <= 65) {
			if (bpm >= 62 && bpm <= 75) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age > 65) {
			if (bpm >= 62 && bpm <= 73) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}
	} else {
		cout << "Error: both age and heart rate must be positive.";
	}

}

// Override the bloodPressure function in class Child
void Male::bloodPressure(int age, int sys, int dia) {
	if (age > 0 && sys > 0 && dia > 0) {
		if (age >= 18 && age <= 39) {
			if ((sys < 119) && (dia < 70)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (age >= 40 && age <= 59) {
			if ((sys < 124) && (dia < 77)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (age >= 60) {
			if ((sys < 133) && (dia < 69)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}
	} else {
		cout << "Error: age, systolic, and diastolic must be positive.";
	}
}

// Override the temperature function in class Child
void Male::temperature(int age, double temp) {
	if (age > 0) {
		if (age >= 18 && age <= 64) {
			if (temp >= 36.2 && temp <= 37.8) {
				isTemperatureNormal = true;
			} else {
				isTemperatureNormal = false;
			}
		}

		if (age >= 65) {
			if (temp >= 35.5 && temp <= 37.1) {
				isTemperatureNormal = true;
			} else {
				isTemperatureNormal = false;
			}
		}
	} else {
		cout << "Error: age must be positive.";
	}
}

// This is the same as class Child
bool Male::getHeartRateNormal() const {
	return isHeartRateNormal;
}

bool Male::getBloodPressureNormal() const {
	return isBloodPressureNormal;
}

bool Male::getTemperatureNormal() const {
	return isTemperatureNormal;
}
