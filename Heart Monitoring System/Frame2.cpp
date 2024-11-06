#include "Frame2.h"
#include "child.h"
#include "male.h"
#include "female.h"
#include <wx/font.h>
#include <string>

Frame2::Frame2(const wxString& title, const std::string& name, const std::string gender, const std::string ageGroup, const std::string exactAge,
    int heartRate, int bloodPressure1, int bloodPressure2, double temperature)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1920, 680),
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    wxPanel* panel = new wxPanel(this);

    // Patient Text
    patientText = new wxStaticText(panel, wxID_ANY, "Patient", wxPoint(838, 4));
    wxFont font1(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    patientText->SetFont(font1);
    patientText->SetForegroundColour(*wxBLACK);

    // Draw line that separates the Patient Text and Patient Information
    panel->Bind(wxEVT_PAINT, &Frame2::drawShape, this);

    // Patient Information
    patientName = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 123));
    patientGender = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 176));
    patientAgeGroup = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 226));
    patientExactAge = new wxStaticText(panel, wxID_ANY, "", wxPoint(587, 279));

    wxFont font2(28, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");
    patientName->SetFont(font2);
    patientName->SetForegroundColour(*wxBLACK);
    patientGender->SetFont(font2);
    patientGender->SetForegroundColour(*wxBLACK);
    patientAgeGroup->SetFont(font2);
    patientAgeGroup->SetForegroundColour(*wxBLACK);
    patientExactAge->SetFont(font2);
    patientExactAge->SetForegroundColour(*wxBLACK);

    patientName->SetLabel("Name: " + name);
    patientGender->SetLabel("Gender: " + gender);
    patientAgeGroup->SetLabel("Age Group: " + ageGroup);
    patientExactAge->SetLabel("Exact Age: " + exactAge + " (years)");

    // Load Monitor Image
    wxImage image;
    if (!image.LoadFile("monitor.png", wxBITMAP_TYPE_PNG)) {
        wxLogError("Could not load image");
        return;
    }

    wxSize imageSize(227, 227);
    image = image.Scale(imageSize.GetWidth(), imageSize.GetHeight());
    wxBitmap bitmap(image);

    wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(1106, 110));

    wxFont font3(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Georgia");
    wxFont font4(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Georgia");

    testsText = new wxStaticText(panel, wxID_ANY, "TESTS", wxPoint(26, 367));
    testsText->SetFont(font3);
    testsText->SetForegroundColour(*wxWHITE);
    testsText->SetBackgroundColour(wxColour(56, 182, 255));

    resultsText = new wxStaticText(panel, wxID_ANY, "RESULTS", wxPoint(350, 367));
    resultsText->SetFont(font3);
    resultsText->SetForegroundColour(*wxWHITE);
    resultsText->SetBackgroundColour(wxColour(56, 182, 255));

    unitsText = new wxStaticText(panel, wxID_ANY, "UNITS", wxPoint(750, 367));
    unitsText->SetFont(font3);
    unitsText->SetForegroundColour(*wxWHITE);
    unitsText->SetBackgroundColour(wxColour(56, 182, 255));

    referenceIntervalText = new wxStaticText(panel, wxID_ANY, "REFERENCE INTERVAL", wxPoint(1104, 367));
    referenceIntervalText->SetFont(font3);
    referenceIntervalText->SetForegroundColour(*wxWHITE);
    referenceIntervalText->SetBackgroundColour(wxColour(56, 182, 255));

    normalityText = new wxStaticText(panel, wxID_ANY, "NORMALITY", wxPoint(1629, 367));
    normalityText->SetFont(font3);
    normalityText->SetForegroundColour(*wxWHITE);
    normalityText->SetBackgroundColour(wxColour(56, 182, 255));

    heartRateText = new wxStaticText(panel, wxID_ANY, "Heart Rate", wxPoint(26, 430));
    heartRateText->SetFont(font4);
    heartRateText->SetForegroundColour(*wxBLACK);

    bloodPressureText = new wxStaticText(panel, wxID_ANY, "Blood Pressure", wxPoint(26, 492));
    bloodPressureText->SetFont(font4);
    bloodPressureText->SetForegroundColour(*wxBLACK);

    temperatureCelsiusText = new wxStaticText(panel, wxID_ANY, "Temperature (°C)", wxPoint(26, 553));
    temperatureCelsiusText->SetFont(font4);
    temperatureCelsiusText->SetForegroundColour(*wxBLACK);

    heartRateResult = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 430));
    bloodPressureResult = new wxStaticText(panel, wxID_ANY, "", wxPoint(385, 492));
    temperatureCelsiusResult = new wxStaticText(panel, wxID_ANY, "", wxPoint(400, 553));

    heartRateResult->SetFont(font4);
    heartRateResult->SetForegroundColour(*wxBLACK);
    bloodPressureResult->SetFont(font4);
    bloodPressureResult->SetForegroundColour(*wxBLACK);
    temperatureCelsiusResult->SetFont(font4);
    temperatureCelsiusResult->SetForegroundColour(*wxBLACK);

    heartRateResult->SetLabel(wxString::Format("%d", heartRate));
    bloodPressureResult->SetLabel(wxString::Format("%d / %d", bloodPressure1, bloodPressure2));
    temperatureCelsiusResult->SetLabel(wxString::Format("%.1f", temperature));

    heartRateUnit = new wxStaticText(panel, wxID_ANY, "bpm (beat per minute)", wxPoint(662, 430));
    heartRateUnit->SetFont(font4);
    heartRateUnit->SetForegroundColour(*wxBLACK);

    bloodPressureUnit = new wxStaticText(panel, wxID_ANY, "mmHg (millimeters of mercury)", wxPoint(584, 492));
    bloodPressureUnit->SetFont(font4);
    bloodPressureUnit->SetForegroundColour(*wxBLACK);

    temperatureCelsiusUnit = new wxStaticText(panel, wxID_ANY, "°C (Degree Celsius)", wxPoint(674, 553));
    temperatureCelsiusUnit->SetFont(font4);
    temperatureCelsiusUnit->SetForegroundColour(*wxBLACK);

    heartRateInterval = new wxStaticText(panel, wxID_ANY, "", wxPoint(1234, 430));
    bloodPressureInterval = new wxStaticText(panel, wxID_ANY, "", wxPoint(1187, 492));
    temperatureCelsiusInterval = new wxStaticText(panel, wxID_ANY, "", wxPoint(1224, 553));

    Initialize(gender, ageGroup, exactAge, heartRate, bloodPressure1, bloodPressure2, temperature);

    heartRateInterval->SetLabel(retrievedHeartRateInterval);
    bloodPressureInterval->SetLabel(retrievedBloodPressureInterval);
    temperatureCelsiusInterval->SetLabel(retrievedTemperatureCelsiusInterval);

    heartRateInterval->SetFont(font4);
    heartRateInterval->SetForegroundColour(*wxBLACK);

    bloodPressureInterval->SetFont(font4);
    bloodPressureInterval->SetForegroundColour(*wxBLACK);

    temperatureCelsiusInterval->SetFont(font4);
    temperatureCelsiusInterval->SetForegroundColour(*wxBLACK);

    heartRateNormality = new wxStaticText(panel, wxID_ANY, "", wxPoint(1712, 430));
    bloodPressureNormality = new wxStaticText(panel, wxID_ANY, "", wxPoint(1712, 492));
    temperatureCelsiusNormality = new wxStaticText(panel, wxID_ANY, "", wxPoint(1712, 553));

    checkNormality(panel, font4);
}

void Frame2::drawShape(wxPaintEvent& event)
{
    wxPanel* panel = dynamic_cast<wxPanel*>(event.GetEventObject());
    wxPaintDC dc(panel);
    dc.SetPen(wxPen(wxColour("#38b6ff"), 2));
    dc.SetBrush(wxBrush(wxColour("#38b6ff")));
    dc.DrawLine(553, 88, 1367, 88);
    dc.DrawRectangle(0, 359, 1920, 54);
}

void Frame2::Initialize(const std::string gender, const std::string ageGroup, const std::string exactAge,
    int heartRate, int bloodPressure1, int bloodPressure2, double temperature)
{
    // Create instances
    Child child;
    Male male;
    Female female;

    if (ageGroup == "Newborn" || ageGroup == "Infant" || ageGroup == "Toddler" || ageGroup == "Preschooler" ||
        ageGroup == "School-aged child" || ageGroup == "Teenager")
    {
        child.heartRate(ageGroup, heartRate);
        child.bloodPressure(ageGroup, bloodPressure1, bloodPressure2);
        child.temperature(ageGroup, temperature);

        retrievedHeartRateInterval = child.getHeartRateInterval();
        retrievedBloodPressureInterval = child.getBloodPressureInterval();
        retrievedTemperatureCelsiusInterval = child.getTemperatureInterval();

        retrievedIsHeartRateNormal = child.getHeartRateNormal();
        retrievedIsBloodPressureNormal = child.getBloodPressureNormal();
        retrievedIsTemperatureNormal = child.getTemperatureNormal();
    }
    else {
        if (gender == "Male") {
            male.heartRate(std::stoi(exactAge), heartRate);
            male.bloodPressure(std::stoi(exactAge), bloodPressure1, bloodPressure2);
            male.temperature(std::stoi(exactAge), temperature);

            retrievedHeartRateInterval = male.getHeartRateInterval();
            retrievedBloodPressureInterval = male.getBloodPressureInterval();
            retrievedTemperatureCelsiusInterval = male.getTemperatureInterval();

            retrievedIsHeartRateNormal = male.getHeartRateNormal();
            retrievedIsBloodPressureNormal = male.getBloodPressureNormal();
            retrievedIsTemperatureNormal = male.getTemperatureNormal();
        }
        else
        {
            female.heartRate(std::stoi(exactAge), heartRate);
            female.bloodPressure(std::stoi(exactAge), bloodPressure1, bloodPressure2);
            female.temperature(std::stoi(exactAge), temperature);

            retrievedHeartRateInterval = female.getHeartRateInterval();
            retrievedBloodPressureInterval = female.getBloodPressureInterval();
            retrievedTemperatureCelsiusInterval = female.getTemperatureInterval();

            retrievedIsHeartRateNormal = female.getHeartRateNormal();
            retrievedIsBloodPressureNormal = female.getBloodPressureNormal();
            retrievedIsTemperatureNormal = female.getTemperatureNormal();
        }
    }
}

void Frame2::checkNormality(wxPanel* panel, wxFont font4)
{
    wxImage image;

    if (!retrievedIsHeartRateNormal)
    {
        if (!image.LoadFile("warning.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxBitmap bitmap(image.Scale(38, 38));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(1660, 430));

        heartRateNormality->SetLabel("Alert");
        heartRateNormality->SetFont(font4);
        heartRateNormality->SetForegroundColour(wxColour("#fa2b3a"));
    }
    else
    {
        if (!image.LoadFile("accept.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxBitmap bitmap(image.Scale(38, 38));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(1660, 430));

        heartRateNormality->SetLabel("Normal");
        heartRateNormality->SetFont(font4);
        heartRateNormality->SetForegroundColour(wxColour("#4bae4f"));
    }

    if (!retrievedIsBloodPressureNormal)
    {
        if (!image.LoadFile("warning.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxBitmap bitmap(image.Scale(38, 38));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(1660, 492));

        bloodPressureNormality->SetLabel("Alert");
        bloodPressureNormality->SetFont(font4);
        bloodPressureNormality->SetForegroundColour(wxColour("#fa2b3a"));
    }
    else
    {
        if (!image.LoadFile("accept.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxBitmap bitmap(image.Scale(38, 38));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(1660, 492));

        bloodPressureNormality->SetLabel("Normal");
        bloodPressureNormality->SetFont(font4);
        bloodPressureNormality->SetForegroundColour(wxColour("#4bae4f"));
    }

    if (!retrievedIsTemperatureNormal)
    {
        if (!image.LoadFile("warning.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxBitmap bitmap(image.Scale(38, 38));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(1660, 553));

        temperatureCelsiusNormality->SetLabel("Alert");
        temperatureCelsiusNormality->SetFont(font4);
        temperatureCelsiusNormality->SetForegroundColour(wxColour("#fa2b3a"));
    }
    else
    {
        if (!image.LoadFile("accept.png", wxBITMAP_TYPE_PNG)) {
            wxLogError("Could not load image");
            return;
        }

        wxBitmap bitmap(image.Scale(38, 38));
        wxStaticBitmap* imageDisplay = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(1660, 553));

        temperatureCelsiusNormality->SetLabel("Normal");
        temperatureCelsiusNormality->SetFont(font4);
        temperatureCelsiusNormality->SetForegroundColour(wxColour("#4bae4f"));
    }
}
