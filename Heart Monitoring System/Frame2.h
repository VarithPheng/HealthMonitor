#ifndef FRAME2_H
#define FRAME2_H

#include <wx/wx.h>

class Frame2 : public wxFrame {
	public:
		Frame2(const wxString& title, const std::string& name, const std::string gender, const std::string ageGroup, const std::string exactAge,
			int heartRate, int bloodPressure1, int bloodPressure2, double temperature);

	private:
		// 1
		wxStaticText* patientText;
		wxStaticText* patientName;
		wxStaticText* patientGender;
		wxStaticText* patientAgeGroup;
		wxStaticText* patientExactAge;

		// 2
		wxStaticText* testsText;
		wxStaticText* resultsText;
		wxStaticText* unitsText;
		wxStaticText* referenceIntervalText;
		wxStaticText* normalityText;

		// 3
		wxStaticText* heartRateText;
		wxStaticText* bloodPressureText;
		wxStaticText* temperatureCelsiusText;
		// 4
		wxStaticText* heartRateResult;
		wxStaticText* bloodPressureResult;
		wxStaticText* temperatureCelsiusResult;

		// 5
		wxStaticText* heartRateUnit;
		wxStaticText* bloodPressureUnit;
		wxStaticText* temperatureCelsiusUnit;

		std::string retrievedHeartRateInterval;
		std::string retrievedBloodPressureInterval;
		std::string retrievedTemperatureCelsiusInterval;

		bool retrievedIsHeartRateNormal;
		bool retrievedIsBloodPressureNormal;
		bool retrievedIsTemperatureNormal;

		wxStaticText* heartRateInterval;
		wxStaticText* bloodPressureInterval;
		wxStaticText* temperatureCelsiusInterval;

		wxStaticText* heartRateNormality;
		wxStaticText* bloodPressureNormality;
		wxStaticText* temperatureCelsiusNormality;

		void drawShape(wxPaintEvent& event);
		void Initialize(const std::string gender, const std::string ageGroup, const std::string exactAge,
			int heartRate, int bloodPressure1, int bloodPressure2, double temperature);
		void checkNormality(wxPanel* panel, wxFont font4);
};

#endif