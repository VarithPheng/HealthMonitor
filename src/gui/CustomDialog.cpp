#include "CustomDialog.h"
#include <wx/statline.h>

CustomDialog::CustomDialog(wxWindow* parent, 
                         const std::vector<PatientAlert>& patients)
    : wxDialog(parent, wxID_ANY, "Health Alert", 
              wxDefaultPosition, wxSize(500, 600))
{
    // Create main panel with background color
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(bgColor);

    // Create vertical sizer for layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add header
    wxPanel* headerPanel = new wxPanel(panel);
    headerPanel->SetBackgroundColour(headerColor);
    wxBoxSizer* headerSizer = new wxBoxSizer(wxVERTICAL);

    // Add warning icon and text to header
    wxStaticText* headerText = new wxStaticText(headerPanel, wxID_ANY, 
        "⚠️ Attention Required", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont headerFont = headerText->GetFont();
    headerFont.SetPointSize(16);
    headerFont.SetWeight(wxFONTWEIGHT_BOLD);
    headerText->SetFont(headerFont);
    headerText->SetForegroundColour(*wxWHITE);

    headerSizer->Add(headerText, 0, wxALL | wxALIGN_CENTER, 15);
    headerPanel->SetSizer(headerSizer);

    // Add subtitle
    wxStaticText* subtitle = new wxStaticText(panel, wxID_ANY,
        "The following patients require immediate attention:");
    wxFont subtitleFont = subtitle->GetFont();
    subtitleFont.SetPointSize(12);
    subtitleFont.SetWeight(wxFONTWEIGHT_BOLD);
    subtitle->SetFont(subtitleFont);
    subtitle->SetForegroundColour(textColor);

    // Create scrolled window for patient list
    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(panel);
    scrolledWindow->SetBackgroundColour(patientBgColor);
    wxBoxSizer* scrollSizer = new wxBoxSizer(wxVERTICAL);

    // Add patient information
    for (const auto& patient : patients) {
        wxPanel* patientPanel = new wxPanel(scrolledWindow);
        patientPanel->SetBackgroundColour(patientBgColor);
        wxBoxSizer* patientSizer = new wxBoxSizer(wxVERTICAL);

        // Patient name and age
        wxStaticText* nameText = new wxStaticText(patientPanel, wxID_ANY,
            wxString::Format("Patient: %s (Age: %d)", patient.name, patient.age));
        wxFont patientFont = nameText->GetFont();
        patientFont.SetPointSize(11);
        patientFont.SetWeight(wxFONTWEIGHT_BOLD);
        nameText->SetFont(patientFont);
        nameText->SetForegroundColour(patientTextColor);

        // Vital signs with abnormal indicators
        wxFont vitalFont = patientFont;
        vitalFont.SetWeight(wxFONTWEIGHT_NORMAL);

        wxStaticText* heartRateText = new wxStaticText(patientPanel, wxID_ANY,
            wxString::Format("Heart Rate: %.2f", patient.heartRate));
        heartRateText->SetFont(vitalFont);
        if (patient.isHeartRateAbnormal) {
            heartRateText->SetForegroundColour(abnormalColor);
            heartRateText->SetLabel(heartRateText->GetLabel() + " ⚠️ ABNORMAL");
        }

        wxStaticText* bpText = new wxStaticText(patientPanel, wxID_ANY,
            wxString::Format("Blood Pressure: %.2f", patient.bloodPressure));
        bpText->SetFont(vitalFont);
        if (patient.isBloodPressureAbnormal) {
            bpText->SetForegroundColour(abnormalColor);
            bpText->SetLabel(bpText->GetLabel() + " ⚠️ ABNORMAL");
        }

        wxStaticText* tempText = new wxStaticText(patientPanel, wxID_ANY,
            wxString::Format("Temperature: %.2f", patient.temperature));
        tempText->SetFont(vitalFont);
        if (patient.isTemperatureAbnormal) {
            tempText->SetForegroundColour(abnormalColor);
            tempText->SetLabel(tempText->GetLabel() + " ⚠️ ABNORMAL");
        }

        patientSizer->Add(nameText, 0, wxALL, 5);
        patientSizer->Add(heartRateText, 0, wxALL, 5);
        patientSizer->Add(bpText, 0, wxALL, 5);
        patientSizer->Add(tempText, 0, wxALL, 5);
        patientSizer->Add(new wxStaticLine(patientPanel), 0, wxEXPAND | wxALL, 5);

        patientPanel->SetSizer(patientSizer);
        scrollSizer->Add(patientPanel, 0, wxEXPAND | wxALL, 5);
    }

    scrolledWindow->SetSizer(scrollSizer);
    scrolledWindow->FitInside();
    scrolledWindow->SetScrollRate(5, 5);

    // Create OK button
    wxButton* okButton = new wxButton(panel, wxID_OK, "Acknowledge");
    okButton->SetBackgroundColour(buttonColor);
    okButton->SetForegroundColour(*wxWHITE);
    wxFont buttonFont = okButton->GetFont();
    buttonFont.SetPointSize(12);
    buttonFont.SetWeight(wxFONTWEIGHT_BOLD);
    okButton->SetFont(buttonFont);

    // Add everything to main sizer
    mainSizer->Add(headerPanel, 0, wxEXPAND);
    mainSizer->Add(subtitle, 0, wxALL | wxALIGN_LEFT, 15);
    mainSizer->Add(scrolledWindow, 1, wxEXPAND | wxLEFT | wxRIGHT, 15);
    mainSizer->Add(okButton, 0, wxALL | wxALIGN_CENTER, 15);

    panel->SetSizer(mainSizer);
    Centre();
}