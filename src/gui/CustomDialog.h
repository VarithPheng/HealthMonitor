#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <wx/wx.h>
#include <wx/stattext.h>
#include <vector>

struct PatientAlert {
    std::string name;
    int age;
    double heartRate;
    double bloodPressure;
    double temperature;
    bool isHeartRateAbnormal;
    bool isBloodPressureAbnormal;
    bool isTemperatureAbnormal;
};

class CustomDialog : public wxDialog {
public:
    CustomDialog(wxWindow* parent, const std::vector<PatientAlert>& patients);

private:
    wxColour bgColor = wxColour(245, 245, 245);
    wxColour headerColor = wxColour(231, 76, 60);
    wxColour textColor = wxColour(44, 62, 80);
    wxColour buttonColor = wxColour(52, 152, 219);
    wxColour patientBgColor = wxColour(255, 255, 255);
    wxColour patientTextColor = wxColour(33, 33, 33);
    wxColour abnormalColor = wxColour(231, 76, 60);  // Red for abnormal values
};

#endif