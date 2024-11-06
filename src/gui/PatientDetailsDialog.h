#ifndef PATIENTDETAILSDIALOG_H
#define PATIENTDETAILSDIALOG_H

#include <wx/wx.h>
#include <wx/statline.h>
#include <string>
using namespace std;

class PatientDetailsDialog : public wxDialog {
public:
    PatientDetailsDialog(wxWindow* parent, 
                        const string& name,
                        const string& gender,
                        const string& ageGroup,
                        int exactAge,
                        double heartRate,
                        double bloodPressure,
                        double temperature,
                        const string& referenceHR,
                        const string& referenceBP,
                        const string& referenceTemp);

private:
    wxColour bgColor = wxColour(51, 51, 51);  // Dark gray
    wxColour headerColor = wxColour(33, 150, 243);  // Blue
    wxColour textColor = wxColour(255, 255, 255);  // White
    wxColour alertColor = wxColour(244, 67, 54);  // Red
    wxColour normalColor = wxColour(76, 175, 80);  // Green
};

#endif 