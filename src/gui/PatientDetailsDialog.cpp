#include "PatientDetailsDialog.h"

PatientDetailsDialog::PatientDetailsDialog(
    wxWindow* parent,
    const wxString& name,
    const wxString& gender,
    const wxString& ageGroup,
    int exactAge,
    double heartRate,
    double bloodPressure,
    double temperature,
    const wxString& referenceHR,
    const wxString& referenceBP,
    const wxString& referenceTemp)
    : wxDialog(parent, wxID_ANY, "Patient Information", wxDefaultPosition, wxSize(800, 400))
{
    SetBackgroundColour(bgColor);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Header section
    wxPanel* headerPanel = new wxPanel(this, wxID_ANY);
    headerPanel->SetBackgroundColour(bgColor);
    wxBoxSizer* headerSizer = new wxBoxSizer(wxVERTICAL);

    // Title
    wxStaticText* titleText = new wxStaticText(headerPanel, wxID_ANY, "Patient Information");
    wxFont titleFont = titleText->GetFont();
    titleFont.SetPointSize(24);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    titleText->SetFont(titleFont);
    titleText->SetForegroundColour(textColor);

    // Patient info
    wxStaticText* nameText = new wxStaticText(headerPanel, wxID_ANY, 
        wxString::Format("Name: %s", name));
    wxStaticText* genderText = new wxStaticText(headerPanel, wxID_ANY, 
        wxString::Format("Gender: %s", gender));
    wxStaticText* ageGroupText = new wxStaticText(headerPanel, wxID_ANY, 
        wxString::Format("Age Group: %s", ageGroup));
    wxStaticText* exactAgeText = new wxStaticText(headerPanel, wxID_ANY, 
        wxString::Format("Exact Age: %d years", exactAge));

    std::vector<wxStaticText*> infoTexts = {nameText, genderText, ageGroupText, exactAgeText};
    for (auto text : infoTexts) {
        text->SetForegroundColour(textColor);
        wxFont font = text->GetFont();
        font.SetPointSize(12);
        text->SetFont(font);
    }

    headerSizer->Add(titleText, 0, wxALL | wxALIGN_LEFT, 10);
    headerSizer->Add(new wxStaticLine(headerPanel), 0, wxEXPAND | wxALL, 5);
    for (auto text : infoTexts) {
        headerSizer->Add(text, 0, wxALL, 5);
    }
    headerPanel->SetSizer(headerSizer);

    // Results grid
    wxPanel* gridPanel = new wxPanel(this, wxID_ANY);
    gridPanel->SetBackgroundColour(bgColor);
    wxGridSizer* grid = new wxGridSizer(4, 5, 5, 5);

    // Headers
    std::vector<wxString> headers = {"Tests", "Results", "Units", "Reference Interval", "Normality"};
    for (const auto& header : headers) {
        wxStaticText* headerText = new wxStaticText(gridPanel, wxID_ANY, header);
        headerText->SetForegroundColour(headerColor);
        wxFont font = headerText->GetFont();
        font.SetPointSize(12);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        headerText->SetFont(font);
        grid->Add(headerText, 0, wxALL, 5);
    }

    // Heart Rate row
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, "Heart Rate"), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, wxString::Format("%.0f", heartRate)), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, "bpm"), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, referenceHR), 0, wxALL, 5);
    
    wxStaticText* hrNormality = new wxStaticText(gridPanel, wxID_ANY, 
        (heartRate >= 60 && heartRate <= 100) ? "Normal" : "Alert");
    hrNormality->SetForegroundColour((heartRate >= 60 && heartRate <= 100) ? normalColor : alertColor);
    grid->Add(hrNormality, 0, wxALL, 5);

    // Blood Pressure row
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, "Blood Pressure"), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, wxString::Format("%.0f", bloodPressure)), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, "mmHg"), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, referenceBP), 0, wxALL, 5);
    
    wxStaticText* bpNormality = new wxStaticText(gridPanel, wxID_ANY, 
        (bloodPressure >= 90 && bloodPressure <= 120) ? "Normal" : "Alert");
    bpNormality->SetForegroundColour((bloodPressure >= 90 && bloodPressure <= 120) ? normalColor : alertColor);
    grid->Add(bpNormality, 0, wxALL, 5);

    // Temperature row
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, "Temperature"), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, wxString::Format("%.1f", temperature)), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, "°F"), 0, wxALL, 5);
    grid->Add(new wxStaticText(gridPanel, wxID_ANY, referenceTemp), 0, wxALL, 5);
    
    wxStaticText* tempNormality = new wxStaticText(gridPanel, wxID_ANY, 
        (temperature >= 97.0 && temperature <= 99.0) ? "Normal" : "Alert");
    tempNormality->SetForegroundColour((temperature >= 97.0 && temperature <= 99.0) ? normalColor : alertColor);
    grid->Add(tempNormality, 0, wxALL, 5);

    gridPanel->SetSizer(grid);

    mainSizer->Add(headerPanel, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(gridPanel, 0, wxEXPAND | wxALL, 5);

    SetSizer(mainSizer);
} 