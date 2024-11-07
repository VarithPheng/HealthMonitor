#ifndef PATIENTDETAILSDIALOG_H
#define PATIENTDETAILSDIALOG_H

#include <wx/wx.h>
#include <wx/statline.h>

class PatientDetailsDialog : public wxDialog {
public:
    PatientDetailsDialog(wxWindow* parent, 
                        const wxString& name,
                        const wxString& gender,
                        const wxString& ageGroup,
                        int exactAge,
                        double heartRate,
                        double bloodPressure,
                        double temperature,
                        const wxString& referenceHR,
                        const wxString& referenceBP,
                        const wxString& referenceTemp);

private:
    wxColour bgColor = wxColour(26, 32, 44);  // Dark background
    wxColour headerColor = wxColour(66, 153, 225);  // Blue
    wxColour textColor = wxColour(237, 242, 247);  // Light text
    wxColour alertColor = wxColour(244, 67, 54);  // Red
    wxColour normalColor = wxColour(76, 175, 80);  // Green
};

#endif 