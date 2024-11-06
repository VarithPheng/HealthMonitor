#ifndef FRAME1_H
#define FRAME1_H

#include <wx/wx.h>


class Frame1 : public wxFrame {
	public:
		Frame1(const wxString& title);
	private:
		std::string storedName;
		std::string storedGender;
		bool isMaleChecked;
		bool isFemaleChecked;
		std::string storedAgeGroup;
		std::string storedExactAge;

		int storedHeartRate;
		int storedBloodPressure1;
		int storedBloodPressure2;
		double storedTemperature;

		wxStaticText* welcomeText;
		wxStaticText* instructionText;
		wxStaticText* nameText;
		wxStaticText* genderText;
		wxStaticText* ageGroupText;
		wxStaticText* exactAgeText;
		wxStaticText* heartRateText;
		wxStaticText* bloodPressureText;
		wxStaticText* temperatureText;
		wxStaticText* labelText;

		wxTextCtrl* nameInput;
		wxTextCtrl* heartRateInput;
		wxTextCtrl* bloodPressureInput1;
		wxTextCtrl* bloodPressureInput2;
		wxTextCtrl* temperatureInput;
		wxTextCtrl* exactAgeInput;

		wxCheckBox* maleCheckBox;
		wxCheckBox* femaleCheckBox;

		wxChoice* ageGroupChoice;

		wxButton* continueButton;

		void drawLine(wxPaintEvent& event);
		void styleInputBox(wxTextCtrl* nameInput);
		void styleButton(wxButton* continueButton);
		//void AgeGroupSelected(wxCommandEvent& event);
		void continueButtonClicked(wxCommandEvent& event);
};

#endif