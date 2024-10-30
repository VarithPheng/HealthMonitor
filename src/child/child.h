#ifndef CHILD_H
#define CHILD_H

#include <string>
using namespace std;

class Child {
	private:
		bool isHeartRateNormal;
		bool isBloodPressureNormal;
		bool isTemperatureNormal;

	public:
		Child();

		void heartRate(const string& ageGroup, int bpm);
		void bloodPressure(const string& ageGroup, int sys, int dia);
		void temperature(const string& ageGroup, double temp);

		bool getHeartRateNormal() const;
		bool getBloodPressureNormal() const;
		bool getTemperatureNormal() const;
};

#endif
