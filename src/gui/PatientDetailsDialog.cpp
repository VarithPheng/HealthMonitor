#include "PatientDetailsDialog.h"
#include <wx/statline.h>
#include <wx/grid.h>

PatientDetailsDialog::PatientDetailsDialog(
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
    const wxString& normalTemperature)
    : wxDialog(parent, wxID_ANY, "Patient Information", wxDefaultPosition, wxSize(800, 500))
{
    SetBackgroundColour(wxColour(26, 32, 44));  // Dark blue background
    wxColour textColor(237, 242, 247);          // Light gray text
    wxColour headerColor(66, 153, 225);         // Light blue for headers
    wxColour normalColor(72, 187, 120);         // Green for normal values

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Title
    wxStaticText* titleText = new wxStaticText(this, wxID_ANY, "Patient Information");
    wxFont titleFont = titleText->GetFont();
    titleFont.SetPointSize(24);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    titleText->SetFont(titleFont);
    titleText->SetForegroundColour(textColor);
    mainSizer->Add(titleText, 0, wxALL, 20);

    // Patient Basic Info - with larger spacing and cleaner look
    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    
    // Add info rows with more spacing and larger font
    auto AddBasicInfoRow = [&](const wxString& label, const wxString& value) {
        wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* labelText = new wxStaticText(this, wxID_ANY, label);
        wxStaticText* valueText = new wxStaticText(this, wxID_ANY, value);
        
        wxFont font = labelText->GetFont();
        font.SetPointSize(14);  // Larger font
        labelText->SetFont(font);
        valueText->SetFont(font);
        
        labelText->SetForegroundColour(textColor);
        valueText->SetForegroundColour(textColor);
        
        rowSizer->Add(labelText);
        rowSizer->Add(valueText, 0, wxLEFT, 5);
        
        return rowSizer;
    };
    
    infoSizer->Add(AddBasicInfoRow("Name: ", name), 0, wxALL, 5);
    infoSizer->Add(AddBasicInfoRow("Gender: ", gender), 0, wxALL, 5);
    infoSizer->Add(AddBasicInfoRow("Age Group: ", ageGroup), 0, wxALL, 5);
    infoSizer->Add(AddBasicInfoRow("Exact Age: ", wxString::Format("%d years", age)), 0, wxALL, 5);
    
    mainSizer->Add(infoSizer, 0, wxALL, 20);

    // Separator line
    mainSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->AddSpacer(20);  // Space after line

    // Grid layout for vital signs
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(4, 5, 15, 40);  // rows, cols, vgap, hgap

    // Headers
    std::vector<wxString> headers = {"Tests", "Results", "Units", "Reference Interval", "Normality"};
    for (const auto& header : headers) {
        wxStaticText* headerText = new wxStaticText(this, wxID_ANY, header);
        wxFont headerFont = headerText->GetFont();
        headerFont.SetPointSize(14);
        headerText->SetFont(headerFont);
        headerText->SetForegroundColour(wxColour(66, 153, 225));  // Light blue
        gridSizer->Add(headerText);
    }

    // Data rows
    auto AddDataRow = [&](const wxString& test, const wxString& result, 
                         const wxString& unit, const wxString& reference,
                         bool isNormal) {
        wxFont rowFont;
        rowFont.SetPointSize(14);

        wxStaticText* testText = new wxStaticText(this, wxID_ANY, test);
        wxStaticText* resultText = new wxStaticText(this, wxID_ANY, result);
        wxStaticText* unitText = new wxStaticText(this, wxID_ANY, unit);
        wxStaticText* refText = new wxStaticText(this, wxID_ANY, reference);
        wxStaticText* normalText = new wxStaticText(this, wxID_ANY, isNormal ? "Normal" : "Abnormal");

        std::vector<wxStaticText*> texts = {testText, resultText, unitText, refText, normalText};
        for (auto* text : texts) {
            text->SetFont(rowFont);
            text->SetForegroundColour(textColor);
        }
        normalText->SetForegroundColour(isNormal ? wxColour(72, 187, 120) : wxColour(244, 67, 54));

        for (auto* text : texts) {
            gridSizer->Add(text);
        }
    };

    // In the constructor, convert the temperature from Fahrenheit to Celsius
    double celsiusTemp = (temperature - 32) * 5/9;  // Convert F to C

    // Update the temperature row in the grid
    AddDataRow("Heart Rate", wxString::Format("%.0f", heartRate), "bpm", 
               normalHeartRate, IsHeartRateNormal(heartRate));
    AddDataRow("Blood Pressure", wxString::Format("%.0f", bloodPressure), "mmHg", 
               normalBloodPressure, IsBloodPressureNormal(bloodPressure));
    AddDataRow("Temperature", 
              wxString::Format("%.1f", celsiusTemp),  // Display with 1 decimal place
              "°C",  // Changed from °F to °C
              "36.1-37.2°C",  // Updated reference range in Celsius
              IsTemperatureNormal(celsiusTemp));

    mainSizer->Add(gridSizer, 1, wxALL, 20);

    SetSizer(mainSizer);
}