#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/statline.h>
#include <libpq-fe.h>  // Add PostgreSQL header

MainFrame::MainFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800))
{
    SetBackgroundColour(bgColor);
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Header section
    titleText = new wxStaticText(this, wxID_ANY, "Health Monitoring System");
    
    wxFont titleFont = titleText->GetFont();
    titleFont.SetPointSize(24);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    titleText->SetFont(titleFont);
    titleText->SetForegroundColour(textColor);
    
    mainSizer->Add(titleText, 0, wxALL | wxALIGN_LEFT, 20);
    
    // Buttons panel
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    generateButton = new wxButton(this, wxID_ANY, "Generate Data");
    loadButton = new wxButton(this, wxID_ANY, "Load Data");
    analyzeButton = new wxButton(this, wxID_ANY, "Analyze Data");
    
    std::vector<wxButton*> buttons = {generateButton, loadButton, analyzeButton};
    for (auto btn : buttons) {
        btn->SetBackgroundColour(buttonColor);
        btn->SetForegroundColour(textColor);
        buttonSizer->Add(btn, 1, wxALL | wxEXPAND, 5);
    }
    
    mainSizer->Add(buttonSizer, 0, wxALL | wxEXPAND, 15);
    
    // Time filter
    wxBoxSizer* filterSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* filterLabel = new wxStaticText(this, wxID_ANY, "Filter:");
    filterLabel->SetForegroundColour(textColor);
    timeFilter = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    timeFilter->Append("This Week");
    timeFilter->Append("Last 2 Weeks");
    timeFilter->Append("All Time");
    timeFilter->SetSelection(0);
    
    filterSizer->Add(filterLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    filterSizer->Add(timeFilter, 1);
    mainSizer->Add(filterSizer, 0, wxALL | wxEXPAND, 20);
    
    // Create scrolled window
    scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    scrolledWindow->SetScrollRate(0, 10);  // Vertical scrolling only
    scrolledWindow->SetBackgroundColour(bgColor);
    
    // Results panel inside scrolled window
    resultsPanel = new wxPanel(scrolledWindow);
    resultsPanel->SetBackgroundColour(bgColor);
    resultsSizer = new wxBoxSizer(wxVERTICAL);
    resultsPanel->SetSizer(resultsSizer);
    
    // Add results panel to scrolled window
    wxBoxSizer* scrollSizer = new wxBoxSizer(wxVERTICAL);
    scrollSizer->Add(resultsPanel, 1, wxEXPAND);
    scrolledWindow->SetSizer(scrollSizer);
    
    mainSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 20);
    
    SetSizer(mainSizer);
    
    // Bind events
    generateButton->Bind(wxEVT_BUTTON, &MainFrame::OnGenerateData, this);
    loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadData, this);
    analyzeButton->Bind(wxEVT_BUTTON, &MainFrame::OnAnalyzeData, this);
    timeFilter->Bind(wxEVT_CHOICE, &MainFrame::OnTimeFilterChange, this);
    
    analyzeButton->Enable(false);
    
    Layout();
}

MainFrame::~MainFrame()
{
    if (dbConn) {
        PQfinish(dbConn);
    }
}

bool MainFrame::ConnectToDatabase()
{
    if (dbConn) {
        PQfinish(dbConn);
    }

    dbConn = PQconnectdb("dbname=test user=postgres password=tii007");

    if (PQstatus(dbConn) != CONNECTION_OK) {
        wxMessageBox(
            wxString::Format("Failed to connect to database: %s", 
                           PQerrorMessage(dbConn)),
            "Error",
            wxOK | wxICON_ERROR
        );
        PQfinish(dbConn);
        dbConn = nullptr;
        return false;
    }
    return true;
}

void MainFrame::OnGenerateData(wxCommandEvent& evt)
{
    if (!ConnectToDatabase()) return;
    
    PGresult* res = PQexec(dbConn, 
        "INSERT INTO vital_signs (patient_id, heart_rate, blood_pressure, temperature) "
        "SELECT p.patient_id, "
        "random() * 40 + 60, "  // heart rate between 60 and 100
        "random() * 40 + 90, "  // blood pressure between 90 and 130
        "random() * 2 + 97 "    // temperature between 97 and 99
        "FROM patients p LIMIT 10"
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        wxMessageBox(
            wxString::Format("Failed to generate data: %s", 
                           PQerrorMessage(dbConn)),
            "Error",
            wxOK | wxICON_ERROR
        );
        PQclear(res);
        return;
    }

    PQclear(res);
    wxMessageBox("Generated new vital signs data successfully!",
                "Success",
                wxOK | wxICON_INFORMATION);
    analyzeButton->Enable(true);
}

wxString MainFrame::GetTimeFilterCondition()
{
    wxString condition;
    int selection = timeFilter->GetSelection();
    
    switch(selection) {
        case 0: // This Week
            condition = "v.recorded_at >= NOW() - INTERVAL '1 week'";
            break;
        case 1: // Last 2 Weeks
            condition = "v.recorded_at >= NOW() - INTERVAL '2 weeks'";
            break;
        default: // All Time
            condition = "TRUE";
            break;
    }
    
    return condition;
}

void MainFrame::LoadDataFromDB()
{
    if (!ConnectToDatabase()) return;
    
    normalPatients.clear();
    abnormalPatients.clear();

    // Get the time filter condition
    wxString timeCondition;
    switch(timeFilter->GetSelection()) {
        case 0: // This Week
            timeCondition = "WHERE v.recorded_at >= NOW() - INTERVAL '7 days'";
            break;
        case 1: // Last 2 Weeks
            timeCondition = "WHERE v.recorded_at >= NOW() - INTERVAL '14 days'";
            break;
        default: // All Time
            timeCondition = "";
            break;
    }

    // Construct the query with time filter
    wxString queryStr = wxString::Format(
        "SELECT p.name, p.gender, p.age, "
        "v.heart_rate, v.blood_pressure, v.temperature, v.is_normal, v.age_group, v.recorded_at "
        "FROM patients p "
        "JOIN vital_signs v ON p.patient_id = v.patient_id "
        "%s "
        "ORDER BY v.recorded_at DESC",
        timeCondition
    );

    PGresult* res = PQexec(dbConn, queryStr.mb_str().data());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        wxMessageBox(
            wxString::Format("Failed to load data: %s", 
                           PQerrorMessage(dbConn)),
            "Error",
            wxOK | wxICON_ERROR
        );
        PQclear(res);
        return;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        Patient p;
        p.name = wxString::FromUTF8(PQgetvalue(res, i, 0));
        p.gender = wxString::FromUTF8(PQgetvalue(res, i, 1));
        p.age = atoi(PQgetvalue(res, i, 2));
        p.heartRate = atof(PQgetvalue(res, i, 3));
        p.bloodPressure = atof(PQgetvalue(res, i, 4));
        p.temperature = atof(PQgetvalue(res, i, 5));
        p.isNormal = strcmp(PQgetvalue(res, i, 6), "t") == 0;
        p.ageGroup = wxString::FromUTF8(PQgetvalue(res, i, 7));
        p.recordedAt = wxString::FromUTF8(PQgetvalue(res, i, 8));

        if (p.isNormal) {
            normalPatients.push_back(p);
        } else {
            abnormalPatients.push_back(p);
        }
    }

    PQclear(res);
}

void MainFrame::OnLoadData(wxCommandEvent& evt)
{
    LoadDataFromDB();
    wxMessageBox(
        wxString::Format("Data loaded successfully!\nFound %zu normal and %zu abnormal patients.", 
                        normalPatients.size(), 
                        abnormalPatients.size()),
        "Load Complete",
        wxOK | wxICON_INFORMATION
    );
    analyzeButton->Enable(true);
}

void MainFrame::OnAnalyzeData(wxCommandEvent& evt)
{
    ProcessData();
    DisplayResults();
}

void MainFrame::ProcessData()
{
    // TODO: Implement data processing
}

void MainFrame::DisplayResults()
{
    // Clear existing results
    resultsSizer->Clear(true);
    
    // Add normal patients section
    if (!normalPatients.empty()) {
        wxStaticText* normalHeader = new wxStaticText(resultsPanel, wxID_ANY, "Normal Patients");
        wxFont headerFont = normalHeader->GetFont();
        headerFont.SetPointSize(16);
        headerFont.SetWeight(wxFONTWEIGHT_BOLD);
        normalHeader->SetFont(headerFont);
        normalHeader->SetForegroundColour(textColor);
        resultsSizer->Add(normalHeader, 0, wxALL, 10);
        
        for (const auto& patient : normalPatients) {
            CreatePatientPanel(resultsPanel, patient, true);
        }
    }
    
    // Add abnormal patients section
    if (!abnormalPatients.empty()) {
        wxStaticText* abnormalHeader = new wxStaticText(resultsPanel, wxID_ANY, "Abnormal Patients");
        wxFont headerFont = abnormalHeader->GetFont();
        headerFont.SetPointSize(16);
        headerFont.SetWeight(wxFONTWEIGHT_BOLD);
        abnormalHeader->SetFont(headerFont);
        abnormalHeader->SetForegroundColour(textColor);
        resultsSizer->Add(abnormalHeader, 0, wxALL, 10);
        
        for (const auto& patient : abnormalPatients) {
            CreatePatientPanel(resultsPanel, patient, false);
        }
    }
    
    // Refresh the layout
    resultsPanel->Layout();
    scrolledWindow->FitInside();  // Ensure scroll bars update correctly
    scrolledWindow->Refresh();
}

void MainFrame::CreatePatientPanel(wxPanel* parent, const Patient& patient, bool isNormal)
{
    wxPanel* panel = new wxPanel(parent);
    panel->SetBackgroundColour(wxColour(45, 55, 72));
    
    wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxString info = wxString::Format("Name: %s, Gender: %s, Age Group: %s",
                                   patient.name, patient.gender, patient.ageGroup);
    wxStaticText* infoText = new wxStaticText(panel, wxID_ANY, info);
    infoText->SetForegroundColour(textColor);
    
    wxButton* viewButton = new wxButton(panel, wxID_ANY, "View Details");
    viewButton->SetBackgroundColour(buttonColor);
    viewButton->SetForegroundColour(textColor);
    
    panelSizer->Add(infoText, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    panelSizer->Add(viewButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    
    panel->SetSizer(panelSizer);
    resultsSizer->Add(panel, 0, wxEXPAND | wxALL, 5);
    
    viewButton->Bind(wxEVT_BUTTON, [this, patient](wxCommandEvent&) {
        PatientDetailsDialog dialog(this, patient.name, patient.gender, 
                                  patient.ageGroup, patient.age,
                                  patient.heartRate, patient.bloodPressure, 
                                  patient.temperature,
                                  "60-100 bpm", "90-120 / 60-80 mmHg", "97-99°F");
        dialog.ShowModal();
    });
}

void MainFrame::OnTimeFilterChange(wxCommandEvent& evt)
{
    LoadDataFromDB();
    if (!normalPatients.empty() || !abnormalPatients.empty()) {
        analyzeButton->Enable(true);
    }
}