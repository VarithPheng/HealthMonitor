#ifndef FEMALE_H
#define FEMALE_H

#include "../child/child.h"
using namespace std;

class Female : public Child {
	private:
		bool isHeartRateNormal;
		bool isBloodPressureNormal;
		bool isTemperatureNormal;

	public:
		Female();

		void heartRate(int age, int bpm);
		void bloodPressure(int age, int sys, int dia);
		void temperature(int age, double temp);

		bool getHeartRateNormal() const;
		bool getBloodPressureNormal() const;
		bool getTemperatureNormal() const;
};

#endif
