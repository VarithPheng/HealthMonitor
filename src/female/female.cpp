#include <iostream>
#include <string>
#include "../child/child.h"
#include "female.h"
using namespace std;

// Constructor
Female::Female() {
	isHeartRateNormal = false;
	isBloodPressureNormal = false;
	isTemperatureNormal = false;
}

// Override the heartRate function in class Child
void Female::heartRate(int age, int bpm) {
	if (age > 0 && bpm > 0) {
		if (age >= 18 && age <= 25) {
			if (bpm >= 66 && bpm <= 78) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age >= 26 && age <= 35) {
			if (bpm >= 65 && bpm <= 76) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age >= 36 && age <= 45) {
			if (bpm >= 65 && bpm <= 78) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age >= 46 && age <= 55) {
			if (bpm >= 66 && bpm <= 77) {
				isHeartRateNormal = true;
			} else {
			isHeartRateNormal = false;}
		}

		if (age >= 56 && age <= 65) {
			if (bpm >= 65 && bpm <= 77) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}

		if (age > 65) {
			if (bpm >= 65 && bpm <= 76) {
				isHeartRateNormal = true;
			} else {
				isHeartRateNormal = false;
			}
		}
	} else {
		cout << "Error: Both age and heart rate must be positive.";
	}
}

// Override the bloodPressure function in class Child
void Female::bloodPressure(int age, int sys, int dia) {
	if (age > 0 && sys > 0 && dia > 0) {
		if (age >= 18 && age <= 39) {
			if ((sys < 110) && (dia < 68)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (age >= 40 && age <= 59) {
			if ((sys < 122) && (dia < 74)) {
				isBloodPressureNormal = true;
			} else {
				isBloodPressureNormal = false;
			}
		}

		if (age >= 60) {
			if ((sys < 139) && (dia < 68)) {
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
void Female::temperature(int age, double temp) {
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
bool Female::getHeartRateNormal() const {
	return isHeartRateNormal;
}

bool Female::getBloodPressureNormal() const {
	return isBloodPressureNormal;
}

bool Female::getTemperatureNormal() const {
	return isTemperatureNormal;
}
