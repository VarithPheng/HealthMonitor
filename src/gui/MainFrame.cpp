#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/stattext.h>
#include <vector>

MainFrame::MainFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800))
{
    dbConn = nullptr;
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
    
    // Create scrolled window
    scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    scrolledWindow->SetScrollRate(0, 10);
    scrolledWindow->SetBackgroundColour(bgColor);
    
    // Create results panel inside scrolled window
    resultsPanel = new wxPanel(scrolledWindow);
    resultsPanel->SetBackgroundColour(bgColor);
    resultsSizer = new wxBoxSizer(wxVERTICAL);
    resultsPanel->SetSizer(resultsSizer);
    
    wxBoxSizer* scrollSizer = new wxBoxSizer(wxVERTICAL);
    scrollSizer->Add(resultsPanel, 1, wxEXPAND);
    scrolledWindow->SetSizer(scrollSizer);
    
    mainSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 20);
    SetSizer(mainSizer);
    
    // Bind events
    generateButton->Bind(wxEVT_BUTTON, &MainFrame::OnGenerateData, this);
    loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadData, this);
    analyzeButton->Bind(wxEVT_BUTTON, &MainFrame::OnAnalyzeData, this);
    
    analyzeButton->Enable(false);
}

MainFrame::~MainFrame()
{
    if (dbConn) {
        PQfinish(dbConn);
        dbConn = nullptr;
    }
}

void MainFrame::LoadDataFromDB()
{
    if (!ConnectToDatabase()) return;
    
    normalPatients.clear();
    abnormalPatients.clear();

    PGresult* res = PQexec(dbConn, 
        "SELECT p.name, p.gender, p.age, "
        "v.heart_rate, v.blood_pressure, v.temperature, v.is_normal, v.age_group, "
        "to_char(v.recorded_at, 'Mon DD') as week_of "
        "FROM patients p "
        "JOIN vital_signs v ON p.patient_id = v.patient_id "
        "ORDER BY p.name, v.recorded_at DESC"
    );

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

    // Process results
    int rows = PQntuples(res);
    wxString currentName = "";
    Patient* currentPatient = nullptr;

    for (int i = 0; i < rows; i++) {
        wxString name = wxString::FromUTF8(PQgetvalue(res, i, 0));
        
        // If this is a new patient
        if (name != currentName) {
            if (currentPatient != nullptr) {
                // Add the previous patient to appropriate list
                if (currentPatient->records[0].isNormal) {
                    normalPatients.push_back(*currentPatient);
                } else {
                    abnormalPatients.push_back(*currentPatient);
                }
                delete currentPatient;
            }
            
            currentPatient = new Patient();
            currentPatient->name = name;
            currentPatient->gender = wxString::FromUTF8(PQgetvalue(res, i, 1));
            currentPatient->age = atoi(PQgetvalue(res, i, 2));
            currentPatient->ageGroup = wxString::FromUTF8(PQgetvalue(res, i, 7));
            currentName = name;
        }

        // Add the record
        VitalRecord record;
        record.weekOf = wxString::FromUTF8(PQgetvalue(res, i, 8));
        record.heartRate = atof(PQgetvalue(res, i, 3));
        record.bloodPressure = atof(PQgetvalue(res, i, 4));
        record.temperature = atof(PQgetvalue(res, i, 5));
        record.isNormal = strcmp(PQgetvalue(res, i, 6), "t") == 0;
        
        currentPatient->records.push_back(record);
    }

    // Don't forget the last patient
    if (currentPatient != nullptr) {
        if (currentPatient->records[0].isNormal) {
            normalPatients.push_back(*currentPatient);
        } else {
            abnormalPatients.push_back(*currentPatient);
        }
        delete currentPatient;
    }

    PQclear(res);
}

void MainFrame::OnAnalyzeData(wxCommandEvent& evt)
{
    isAnalyzeMode = true;
    DisplayResults();
}

void MainFrame::OnLoadData(wxCommandEvent& evt)
{
    isAnalyzeMode = false;
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

void MainFrame::DisplayResults()
{
    // Clear existing results
    resultsSizer->Clear(true);
    
    if (isAnalyzeMode) {
        // Display total number of patients
        size_t totalPatients = normalPatients.size() + abnormalPatients.size();
        wxStaticText* header = new wxStaticText(resultsPanel, wxID_ANY, 
            wxString::Format("Patients: %zu", totalPatients));
        wxFont headerFont = header->GetFont();
        headerFont.SetPointSize(16);
        headerFont.SetWeight(wxFONTWEIGHT_BOLD);
        header->SetFont(headerFont);
        header->SetForegroundColour(textColor);
        resultsSizer->Add(header, 0, wxALL, 10);

        // Combine all patients for display
        std::vector<Patient> allPatients;
        allPatients.insert(allPatients.end(), normalPatients.begin(), normalPatients.end());
        allPatients.insert(allPatients.end(), abnormalPatients.begin(), abnormalPatients.end());

        // Display each patient
        for (const auto& patient : allPatients) {
            wxPanel* patientPanel = new wxPanel(resultsPanel);
            patientPanel->SetBackgroundColour(wxColour(44, 52, 64));
            wxBoxSizer* patientSizer = new wxBoxSizer(wxVERTICAL);

            // Patient name and info
            wxString patientInfo = wxString::Format("%s (%s, %s)", 
                patient.name, patient.ageGroup, patient.gender);
            wxStaticText* nameText = new wxStaticText(patientPanel, wxID_ANY, patientInfo);
            nameText->SetForegroundColour(textColor);
            patientSizer->Add(nameText, 0, wxALL, 10);

            // Display records
            for (const auto& record : patient.records) {
                wxPanel* recordPanel = new wxPanel(patientPanel);
                wxBoxSizer* recordSizer = new wxBoxSizer(wxHORIZONTAL);

                wxString recordText = wxString::Format("Week of %s - Heart Rate: %.0f bpm, Temp: %.1f°F", 
                    record.weekOf, record.heartRate, record.temperature);
                wxStaticText* recordText_ctrl = new wxStaticText(recordPanel, wxID_ANY, recordText);
                recordText_ctrl->SetForegroundColour(textColor);
                recordSizer->Add(recordText_ctrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

                if (!record.isNormal) {
                    wxStaticText* alertText = new wxStaticText(recordPanel, wxID_ANY, "⚠ ABNORMAL");
                    alertText->SetForegroundColour(wxColour(244, 67, 54));
                    recordSizer->Add(alertText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
                }

                wxButton* viewButton = new wxButton(recordPanel, wxID_ANY, "View Details");
                viewButton->SetBackgroundColour(buttonColor);
                viewButton->SetForegroundColour(textColor);
                
                viewButton->Bind(wxEVT_BUTTON, [this, patient, record](wxCommandEvent&) {
                    PatientDetailsDialog dialog(this, patient.name, patient.gender, 
                                             patient.ageGroup, patient.age,
                                             record.heartRate, record.bloodPressure, 
                                             record.temperature,
                                             "60-100 bpm", "90-120 / 60-80 mmHg", "97-99°F");
                    dialog.ShowModal();
                });
                
                recordSizer->Add(viewButton, 0, wxALL, 5);

                recordPanel->SetSizer(recordSizer);
                patientSizer->Add(recordPanel, 0, wxEXPAND | wxALL, 5);
            }

            patientPanel->SetSizer(patientSizer);
            resultsSizer->Add(patientPanel, 0, wxEXPAND | wxALL, 5);
        }
    } else {
        // Original display logic for Load Data
        auto displayPatientSection = [this](const std::vector<Patient>& patients, const wxString& headerText) {
            // ... (existing displayPatientSection code remains the same)
        };

        displayPatientSection(normalPatients, "Normal Patients");
        displayPatientSection(abnormalPatients, "Abnormal Patients");
    }

    // Refresh layout
    resultsPanel->Layout();
    scrolledWindow->FitInside();
    scrolledWindow->Refresh();
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
        "SELECT generate_test_data();"  // Assuming you have this function in your database
    );

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
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
    wxMessageBox("Generated new test data successfully!",
                "Success",
                wxOK | wxICON_INFORMATION);
    analyzeButton->Enable(true);
}