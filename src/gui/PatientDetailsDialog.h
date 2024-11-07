#ifndef PATIENTDETAILSDIALOG_H
#define PATIENTDETAILSDIALOG_H

#include <wx/wx.h>

class PatientDetailsDialog : public wxDialog {
public:
    PatientDetailsDialog(
        wxWindow* parent,
        const wxString& name,
        const wxString& gender,
        const wxString& ageGroup,
        int age,
        double heartRate,
        double bloodPressure,
        double temperature,
        const wxString& normalHeartRate,
        const wxString& normalBloodPressure,
        const wxString& normalTemperature
    );

private:
    void AddInfoRow(wxWindow* parent, 
                   wxBoxSizer* sizer, 
                   const wxString& label, 
                   const wxString& value,
                   const wxColour& textColor);

    bool IsHeartRateNormal(double heartRate) {
        return heartRate >= 60 && heartRate <= 100;
    }
    
    bool IsBloodPressureNormal(double bloodPressure) {
        return bloodPressure >= 90 && bloodPressure <= 120;
    }
    
    bool IsTemperatureNormal(double temperature) {
        return temperature >= 36.1 && temperature <= 37.2;
    }
};

#endif 