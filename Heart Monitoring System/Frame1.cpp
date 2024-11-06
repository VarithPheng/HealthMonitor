#include "Frame1.h"
#include "Frame2.h"
#include <wx/font.h>

Frame1::Frame1(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 680),
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    wxPanel* panel = new wxPanel(this);

    // Welcome Text
    welcomeText = new wxStaticText(panel, wxID_ANY, "Welcome!", wxPoint(165, 15));
    wxFont font1(37, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    welcomeText->SetFont(font1);
    welcomeText->SetForegroundColour(*wxBLACK);

    // Draw the line that separates Welcome and Instruction text, and Instruction text and input
    panel->Bind(wxEVT_PAINT, &Frame1::drawLine, this);

    // Set font for all static text
    wxFont staticFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    wxFont boxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");

    // Instruction Text
    instructionText = new wxStaticText(panel, wxID_ANY,
        "Please enter the details below to monitor your\n"
        "health metrics. This information will help us track\n"
        "your health status accurately.",
        wxPoint(25, 113));
    
    instructionText->SetFont(staticFont);
    instructionText->SetForegroundColour(*wxBLACK);

    // Name Text
    nameText = new wxStaticText(panel, wxID_ANY, "Name", wxPoint(25, 264));
    nameText->SetFont(staticFont);
    nameText->SetForegroundColour(*wxBLACK);

    nameInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(25, 299), wxSize(205, 34));

    genderText = new wxStaticText(panel, wxID_ANY, "Gender", wxPoint(25, 343));
    genderText->SetFont(staticFont);
    genderText->SetForegroundColour(*wxBLACK);

    maleCheckBox = new wxCheckBox(panel, wxID_ANY, " Male", wxPoint(46, 383), wxSize(210, 25));
    maleCheckBox->SetFont(boxFont);
    maleCheckBox->SetForegroundColour(*wxBLACK);

    femaleCheckBox = new wxCheckBox(panel, wxID_ANY, " Female", wxPoint(46, 422), wxSize(210, 25));
    femaleCheckBox->SetFont(boxFont);
    femaleCheckBox->SetForegroundColour(*wxBLACK);

    ageGroupText = new wxStaticText(panel, wxID_ANY, "Age Group", wxPoint(25, 460));
    ageGroupText->SetFont(staticFont);
    ageGroupText->SetForegroundColour(*wxBLACK);

    wxArrayString choices = {
        "Newborn",
        "Infant",
        "Toddler",
        "Preschooler",
        "School-aged child",
        "Teenager",
        "Adult",
        "Older Adult"
    };
    ageGroupChoice = new wxChoice(panel, wxID_ANY, wxPoint(25, 497), wxSize(190, 34), choices);
    ageGroupChoice->SetFont(boxFont);
    ageGroupChoice->SetForegroundColour(*wxBLACK);

    exactAgeText = new wxStaticText(panel, wxID_ANY,
        "What is your\n"
        "exact age?",
        wxPoint(25, 541));
    exactAgeText->SetFont(boxFont);
    exactAgeText->SetForegroundColour(*wxBLACK);

    exactAgeInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(128, 568), wxSize(100, 27));
    wxFont exactAgeFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    exactAgeInput->SetFont(exactAgeFont);
    exactAgeInput->SetForegroundColour(*wxBLACK);

    heartRateText = new wxStaticText(panel, wxID_ANY, "Heart Rate (bpm)", wxPoint(294, 264));
    heartRateText->SetFont(staticFont);
    heartRateText->SetForegroundColour(*wxBLACK);

    heartRateInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(294, 299), wxSize(100, 34));

    bloodPressureText = new wxStaticText(panel, wxID_ANY, "Blood Pressure (mmHg)", wxPoint(294, 346));
    bloodPressureText->SetFont(staticFont);
    bloodPressureText->SetForegroundColour(*wxBLACK);

    bloodPressureInput1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(294, 381), wxSize(70, 34));
    bloodPressureInput2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(394, 381), wxSize(70, 34));

    temperatureText = new wxStaticText(panel, wxID_ANY, "Temperature (°C)", wxPoint(294, 428));
    temperatureText->SetFont(staticFont);
    temperatureText->SetForegroundColour(*wxBLACK);

    temperatureInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(294, 463), wxSize(100, 34));

    continueButton = new wxButton(panel, wxID_ANY, "Continue", wxPoint(294, 517), wxSize(143, 40));

    labelText = new wxStaticText(panel, wxID_ANY, "", wxPoint(117, 607));
    wxFont labelTextFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    labelText->SetFont(labelTextFont);
    labelText->SetForegroundColour(*wxRED);

    styleInputBox(nameInput);
    styleInputBox(heartRateInput);
    styleInputBox(bloodPressureInput1);
    styleInputBox(bloodPressureInput2);
    styleInputBox(temperatureInput);

    styleButton(continueButton);

    continueButton->Bind(wxEVT_BUTTON, &Frame1::continueButtonClicked, this);
}

void Frame1::drawLine(wxPaintEvent& event)
{
    wxPanel* panel = dynamic_cast<wxPanel*>(event.GetEventObject());
    wxPaintDC dc(panel);
    wxPen pen(*wxBLACK, 2);
    dc.SetPen(pen);

    dc.DrawLine(173, 88, 407, 88);
    dc.DrawLine(25, 237, 555, 237);
}

void Frame1::styleInputBox(wxTextCtrl* inputBox)
{
    inputBox->SetBackgroundColour(*wxWHITE);
    inputBox->SetForegroundColour(*wxBLACK);
    wxFont inputFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    inputBox->SetFont(inputFont);
}

void Frame1::styleButton(wxButton* continueButton)
{
    continueButton->SetBackgroundColour(wxColour("#7ed957"));
    continueButton->SetForegroundColour(*wxBLACK);
    wxFont inputFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    continueButton->SetFont(inputFont);
}

void Frame1::continueButtonClicked(wxCommandEvent& event)
{
    wxString name = nameInput->GetValue();
    bool isMaleChecked = maleCheckBox->IsChecked();
    bool isFemaleChecked = femaleCheckBox->IsChecked();
    int selectionIndex = ageGroupChoice->GetSelection();
    wxString exactAge = exactAgeInput->GetValue();
    wxString heartRate = heartRateInput->GetValue();
    wxString bloodPressure1 = bloodPressureInput1->GetValue();
    wxString bloodPressure2 = bloodPressureInput2->GetValue();
    wxString temperature = temperatureInput->GetValue();

    if ((!name.IsEmpty()) && (isMaleChecked || isFemaleChecked) && (selectionIndex != wxNOT_FOUND) &&
        (!heartRate.IsEmpty()) && (!bloodPressure1.IsEmpty()) && (!bloodPressure2.IsEmpty()) && (!temperature.IsEmpty()) &&
        (!exactAge.IsEmpty()))
    {
        wxString selectedAgeGroup = ageGroupChoice->GetStringSelection();
        if (isMaleChecked && isFemaleChecked) {
            labelText->SetLabel("Select Male or Female, not Both!");
        } else {
            wxString storedGender = isMaleChecked ? "Male" : "Female";
            wxInitAllImageHandlers();
            Frame2* frame2 = new Frame2("Health Monitor", name.ToStdString(), storedGender.ToStdString(),
                                        selectedAgeGroup.ToStdString(), exactAge.ToStdString(), wxAtoi(heartRate),
                                        wxAtoi(bloodPressure1), wxAtoi(bloodPressure2), wxAtof(temperature));
            frame2->Show();
            Close();
        }
    }
    else {
        labelText->SetLabel("Please don't leave anything blank!");
    }
}
