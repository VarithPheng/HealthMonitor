#include "MainFrame.h"
#include <fstream>
#include <sstream>
#include <random>
#include <wx/font.h>
#include <set>

MainFrame::MainFrame(const wxString& title) 
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800))
{
    // Create main panel
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(bgColor);
    
    // Create vertical box sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Add title
    titleText = new wxStaticText(panel, wxID_ANY, "Health Monitoring System");
    wxFont titleFont = titleText->GetFont();
    titleFont.SetPointSize(20);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    titleText->SetFont(titleFont);
    titleText->SetForegroundColour(textColor);
    
    // Create buttons
    generateButton = new wxButton(panel, wxID_ANY, "Generate New Data");
    loadButton = new wxButton(panel, wxID_ANY, "Load Data");
    inputButton = new wxButton(panel, wxID_ANY, "Input Patient Data");
    lastWeekButton = new wxButton(panel, wxID_ANY, "Last Week");
    lastTwoWeeksButton = new wxButton(panel, wxID_ANY, "Last 2 Weeks");
    allTimeButton = new wxButton(panel, wxID_ANY, "All Time");
    analyzeButton = new wxButton(panel, wxID_ANY, "Analyze");
    
    // Style all buttons
    StyleButton(generateButton);
    StyleButton(loadButton);
    StyleButton(inputButton);
    StyleButton(lastWeekButton);
    StyleButton(lastTwoWeeksButton);
    StyleButton(allTimeButton);
    StyleButton(analyzeButton);
    
    // Create text control for output with styled font
    outputText = new wxTextCtrl(panel, wxID_ANY, "", 
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxTE_READONLY);
    wxFont outputFont(12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    outputText->SetFont(outputFont);
    
    // Add controls to sizer with spacing
    mainSizer->Add(titleText, 0, wxALL | wxALIGN_CENTER, 20);
    mainSizer->Add(generateButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(loadButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(inputButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(lastWeekButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(lastTwoWeeksButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(allTimeButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(analyzeButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(outputText, 1, wxALL | wxEXPAND, 20);
    
    // Set sizer for panel
    panel->SetSizer(mainSizer);
    
    // Bind events
    generateButton->Bind(wxEVT_BUTTON, &MainFrame::OnGenerateData, this);
    loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadData, this);
    inputButton->Bind(wxEVT_BUTTON, &MainFrame::OnInputData, this);
    lastWeekButton->Bind(wxEVT_BUTTON, &MainFrame::OnTimeFilter, this);
    lastTwoWeeksButton->Bind(wxEVT_BUTTON, &MainFrame::OnTimeFilter, this);
    allTimeButton->Bind(wxEVT_BUTTON, &MainFrame::OnTimeFilter, this);
    analyzeButton->Bind(wxEVT_BUTTON, &MainFrame::OnAnalyzeData, this);
    
    // Initially disable analyze button until data is loaded
    analyzeButton->Enable(false);
    
    // Center window
    Centre();
}

void MainFrame::StyleButton(wxButton* button)
{
    button->SetBackgroundColour(buttonColor);
    button->SetForegroundColour(*wxWHITE);
    wxFont buttonFont = button->GetFont();
    buttonFont.SetPointSize(12);
    button->SetFont(buttonFont);
}

void MainFrame::OnGenerateData(wxCommandEvent& evt)
{
    GenerateNewData();
    outputText->SetValue("New data generated successfully!\n");
    analyzeButton->Enable(true);
}

void MainFrame::GenerateNewData()
{
    try {
        generate_db_data(10);  // Generate 10 new records
        outputText->SetValue("New data generated successfully!\n");
        analyzeButton->Enable(true);
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Database Error", wxOK | wxICON_ERROR);
    }
}

void MainFrame::OnLoadData(wxCommandEvent& evt)
{
    LoadDataFromFile();
    analyzeButton->Enable(true);
}

void MainFrame::LoadDataFromFile()
{
    patients.clear();
    normalPatients.clear();
    abnormalPatients.clear();
    
    try {
        auto db = DatabaseConnection::getInstance();
        PGresult* res = db->executeQuery(
            "SELECT p.name, p.age, v.heart_rate, v.blood_pressure, v.temperature "
            "FROM patients p "
            "JOIN vital_signs v ON p.patient_id = v.patient_id "
            "WHERE p.age > 0 AND v.heart_rate > 0 AND v.blood_pressure > 0 AND v.temperature > 0 "
            "ORDER BY v.recorded_at DESC;"
        );
        
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            Patient p;
            p.name = PQgetvalue(res, i, 0);
            p.age = atoi(PQgetvalue(res, i, 1));
            p.heartRate = atof(PQgetvalue(res, i, 2));
            p.bloodPressure = atof(PQgetvalue(res, i, 3));
            p.temperature = atof(PQgetvalue(res, i, 4));
            
            // Additional validation
            if (p.age > 0 && p.heartRate > 0 && p.bloodPressure > 0 && p.temperature > 0) {
                patients.push_back(p);
            }
        }
        
        PQclear(res);
        outputText->SetValue(wxString::Format("Data loaded successfully! Found %zu valid records.\n", patients.size()));
        
    } catch (const exception& e) {
        wxMessageBox(e.what(), "Database Error", wxOK | wxICON_ERROR);
    }
}

void MainFrame::OnAnalyzeData(wxCommandEvent& evt)
{
    ProcessData();
    DisplayResults();
}

void MainFrame::ProcessData()
{
    normalPatients.clear();
    abnormalPatients.clear();
    
    for (auto& p : patients) {
        // Validate data
        if (p.age <= 0 || p.heartRate <= 0 || p.bloodPressure <= 0 || p.temperature <= 0) {
            continue;  // Skip invalid records
        }
        
        bool isNormal = true;
        int ageChoice = getAgeChoice(p.age);
        string ageGroup = assignAgeGroup(ageChoice);
        
        Child child;
        Male male;
        Female female;
        
        if (ageChoice <= 6) {
            child.heartRate(ageGroup, p.heartRate);
            child.bloodPressure(ageGroup, p.bloodPressure, p.bloodPressure * 0.6);
            child.temperature(ageGroup, p.temperature);
            isNormal = child.getHeartRateNormal() && 
                      child.getBloodPressureNormal() && 
                      child.getTemperatureNormal();
        } else {
            bool isMalePatient = (p.name == "Pain" || p.name == "Nagato" || 
                                p.name == "Itachi" || p.name == "Tobi" || 
                                p.name == "Madara" || p.name == "Naruto" || 
                                p.name == "Kakashi");
            
            if (isMalePatient) {
                male.heartRate(p.age, p.heartRate);
                male.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                male.temperature(p.age, p.temperature);
                isNormal = male.getHeartRateNormal() && 
                          male.getBloodPressureNormal() && 
                          male.getTemperatureNormal();
            } else {
                female.heartRate(p.age, p.heartRate);
                female.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                female.temperature(p.age, p.temperature);
                isNormal = female.getHeartRateNormal() && 
                          female.getBloodPressureNormal() && 
                          female.getTemperatureNormal();
            }
        }
        
        p.isNormal = isNormal;
        if (isNormal) {
            normalPatients.push_back(p);
        } else {
            abnormalPatients.push_back(p);
        }
    }
    
    // After processing, update abnormal_readings table
    try {
        auto db = DatabaseConnection::getInstance();
        
        for (const auto& p : abnormalPatients) {
            // Get patient_id and record_id
            string query = "SELECT p.patient_id, v.record_id FROM patients p "
                         "JOIN vital_signs v ON p.patient_id = v.patient_id "
                         "WHERE p.name = '" + p.name + "' "
                         "ORDER BY v.recorded_at DESC LIMIT 1;";
                         
            PGresult* res = db->executeQuery(query.c_str());
            string patient_id = PQgetvalue(res, 0, 0);
            string record_id = PQgetvalue(res, 0, 1);
            PQclear(res);
            
            // Insert abnormal readings
            if (!child.getHeartRateNormal() || !male.getHeartRateNormal() || !female.getHeartRateNormal()) {
                string abnormal_query = "INSERT INTO abnormal_readings (patient_id, record_id, abnormal_type, abnormal_value) "
                                      "VALUES (" + patient_id + ", " + record_id + ", 'Heart Rate', " + std::to_string(p.heartRate) + ");";
                db->executeQuery(abnormal_query.c_str());
            }
            
            // Similar checks for blood pressure and temperature
            // ... (add similar INSERT statements for other vital signs) ...
        }
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Database Error", wxOK | wxICON_ERROR);
    }
}

void MainFrame::DisplayResults()
{
    wxString output;
    
    output.Append("All Patients:\n");
    output.Append("-------------------------------------------------\n");
    for (const auto& p : patients) {
        wxString status = p.isNormal ? "Normal" : "Abnormal";
        wxString colorCode = p.isNormal ? "\033[32m" : "\033[31m";  // Green or Red
        output.Append(wxString::Format("%s (Age %d): %s%s\033[0m\n", 
                     p.name, p.age, colorCode, status));
    }
    
    output.Append("\nNormal Patients:\n");
    output.Append("-------------------------------------------------\n");
    for (const auto& p : normalPatients) {
        output.Append(wxString::Format("%s (Age %d)\n", p.name, p.age));
    }
    
    output.Append("\nAbnormal Patients:\n");
    output.Append("-------------------------------------------------\n");
    for (const auto& p : abnormalPatients) {
        output.Append(wxString::Format("%s (Age %d)\n", p.name, p.age));
        
        // Process vital signs again to show which ones are abnormal
        int ageChoice = getAgeChoice(p.age);
        string ageGroup = assignAgeGroup(ageChoice);
        
        if (ageChoice <= 6) {
            child.heartRate(ageGroup, p.heartRate);
            child.bloodPressure(ageGroup, p.bloodPressure, p.bloodPressure * 0.6);
            child.temperature(ageGroup, p.temperature);
            
            output.Append(wxString::Format("    Heart Rate: %.2f%s\n", 
                         p.heartRate, !child.getHeartRateNormal() ? " (Abnormal)" : ""));
            output.Append(wxString::Format("    Blood Pressure: %.2f%s\n", 
                         p.bloodPressure, !child.getBloodPressureNormal() ? " (Abnormal)" : ""));
            output.Append(wxString::Format("    Temperature: %.2f%s\n", 
                         p.temperature, !child.getTemperatureNormal() ? " (Abnormal)" : ""));
        } else {
            bool isMalePatient = (p.name == "Pain" || p.name == "Nagato" || 
                                p.name == "Itachi" || p.name == "Tobi" || 
                                p.name == "Madara" || p.name == "Naruto" || 
                                p.name == "Kakashi");
            
            if (isMalePatient) {
                male.heartRate(p.age, p.heartRate);
                male.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                male.temperature(p.age, p.temperature);
                
                output.Append(wxString::Format("    Heart Rate: %.2f%s\n", 
                             p.heartRate, !male.getHeartRateNormal() ? " (Abnormal)" : ""));
                output.Append(wxString::Format("    Blood Pressure: %.2f%s\n", 
                             p.bloodPressure, !male.getBloodPressureNormal() ? " (Abnormal)" : ""));
                output.Append(wxString::Format("    Temperature: %.2f%s\n", 
                             p.temperature, !male.getTemperatureNormal() ? " (Abnormal)" : ""));
            } else {
                female.heartRate(p.age, p.heartRate);
                female.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                female.temperature(p.age, p.temperature);
                
                output.Append(wxString::Format("    Heart Rate: %.2f%s\n", 
                             p.heartRate, !female.getHeartRateNormal() ? " (Abnormal)" : ""));
                output.Append(wxString::Format("    Blood Pressure: %.2f%s\n", 
                             p.bloodPressure, !female.getBloodPressureNormal() ? " (Abnormal)" : ""));
                output.Append(wxString::Format("    Temperature: %.2f%s\n", 
                             p.temperature, !female.getTemperatureNormal() ? " (Abnormal)" : ""));
            }
        }
        output.Append("\n");
    }
    
    outputText->SetValue(output);
}

int MainFrame::getAgeChoice(int age) {
    if (age < 1) return 1;  // Newborn
    else if (age == 1) return 2;  // Infant
    else if (age >= 1 && age <= 3) return 3;  // Toddler
    else if (age >= 3 && age <= 5) return 4;  // Preschooler
    else if (age >= 5 && age <= 12) return 5;  // School-aged
    else if (age >= 12 && age <= 18) return 6;  // Teenager
    else if (age >= 18 && age <= 65) return 7;  // Adult
    else return 8;  // Older adult
}

void MainFrame::OnInputData(wxCommandEvent& evt)
{
    wxDialog dialog(this, wxID_ANY, "Input Patient Data", wxDefaultPosition, wxSize(300, 300));
    wxPanel* panel = new wxPanel(&dialog);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create input fields
    wxTextCtrl* nameCtrl = new wxTextCtrl(panel, wxID_ANY);
    wxSpinCtrl* ageCtrl = new wxSpinCtrl(panel, wxID_ANY, "", wxDefaultPosition, 
                                        wxDefaultSize, wxSP_ARROW_KEYS, 0, 120, 30);
    wxTextCtrl* heartRateCtrl = new wxTextCtrl(panel, wxID_ANY);
    wxTextCtrl* bpCtrl = new wxTextCtrl(panel, wxID_ANY);
    wxTextCtrl* tempCtrl = new wxTextCtrl(panel, wxID_ANY);

    // Add labels and controls to sizer
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Name:"), 0, wxALL, 5);
    sizer->Add(nameCtrl, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Age:"), 0, wxALL, 5);
    sizer->Add(ageCtrl, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Heart Rate:"), 0, wxALL, 5);
    sizer->Add(heartRateCtrl, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Blood Pressure:"), 0, wxALL, 5);
    sizer->Add(bpCtrl, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Temperature:"), 0, wxALL, 5);
    sizer->Add(tempCtrl, 0, wxEXPAND | wxALL, 5);

    wxButton* okButton = new wxButton(panel, wxID_OK, "OK");
    wxButton* cancelButton = new wxButton(panel, wxID_CANCEL, "Cancel");
    
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(okButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);
    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(sizer);
    dialog.Fit();

    if (dialog.ShowModal() == wxID_OK) {
        try {
            Patient p;
            p.name = nameCtrl->GetValue().ToStdString();
            p.age = ageCtrl->GetValue();
            p.heartRate = std::stod(heartRateCtrl->GetValue().ToStdString());
            p.bloodPressure = std::stod(bpCtrl->GetValue().ToStdString());
            p.temperature = std::stod(tempCtrl->GetValue().ToStdString());
            
            patients.push_back(p);
            outputText->SetValue("Patient data added successfully!\n");
            analyzeButton->Enable(true);
        } catch (const std::exception& e) {
            wxMessageBox("Invalid input. Please check your values.", "Error", 
                        wxOK | wxICON_ERROR);
        }
    }
}

void MainFrame::OnTimeFilter(wxCommandEvent& evt)
{
    wxButton* button = wxDynamicCast(evt.GetEventObject(), wxButton);
    string timeFilter;
    
    if (button == lastWeekButton) {
        timeFilter = "AND v.recorded_at >= NOW() - INTERVAL '1 week'";
    } else if (button == lastTwoWeeksButton) {
        timeFilter = "AND v.recorded_at >= NOW() - INTERVAL '2 weeks'";
    } else {
        timeFilter = "";  // All time
    }
    
    try {
        patients.clear();  // Clear existing data
        normalPatients.clear();
        abnormalPatients.clear();
        
        auto db = DatabaseConnection::getInstance();
        string query = "SELECT p.name, p.age, p.gender, v.heart_rate, v.blood_pressure, "
                      "v.temperature, v.age_group "
                      "FROM patients p "
                      "JOIN vital_signs v ON p.patient_id = v.patient_id "
                      "WHERE p.age > 0 AND v.heart_rate > 0 "
                      "AND v.blood_pressure > 0 AND v.temperature > 0 " +
                      timeFilter + " "
                      "ORDER BY v.recorded_at DESC;";
        
        PGresult* res = db->executeQuery(query.c_str());
        int rows = PQntuples(res);
        
        for (int i = 0; i < rows; i++) {
            Patient p;
            p.name = PQgetvalue(res, i, 0);
            p.age = atoi(PQgetvalue(res, i, 1));
            p.heartRate = atof(PQgetvalue(res, i, 3));
            p.bloodPressure = atof(PQgetvalue(res, i, 4));
            p.temperature = atof(PQgetvalue(res, i, 5));
            patients.push_back(p);
        }
        
        PQclear(res);
        outputText->SetValue(wxString::Format("Data loaded successfully! Found %zu records.\n", patients.size()));
        analyzeButton->Enable(true);  // Enable analyze button after loading data
        
    } catch (const std::exception& e) {
        wxMessageBox(e.what(), "Database Error", wxOK | wxICON_ERROR);
    }
}

string MainFrame::FormatResults()
{
    stringstream ss;
    ss << "All Patients: " << patients.size() << "\n";
    ss << "-------------------------------------------------\n\n";

    ss << "Normal Patients:\n";
    ss << "-------------------------------------------------\n";
    for (const auto& p : normalPatients) {
        ss << p.name << " (Age " << p.age << "): Normal\n";
    }
    ss << "\n";

    ss << "Abnormal Patients:\n";
    ss << "-------------------------------------------------\n";
    // Remove duplicates from abnormalPatients if needed
    set<string> processedPatients;  // To track unique patients
    for (const auto& p : abnormalPatients) {
        // Create a unique identifier for each patient
        string patientId = p.name + to_string(p.age);
        
        // Only process if we haven't seen this patient before
        if (processedPatients.find(patientId) == processedPatients.end()) {
            processedPatients.insert(patientId);
            
            ss << p.name << " (Age " << p.age << ")\n";
            ss << "    Heart Rate: " << fixed << setprecision(2) << p.heartRate;
            if (!child.getHeartRateNormal() || !male.getHeartRateNormal() || !female.getHeartRateNormal()) {
                ss << " (Abnormal)";
            }
            ss << "\n";
            
            ss << "    Blood Pressure: " << p.bloodPressure;
            if (!child.getBloodPressureNormal() || !male.getBloodPressureNormal() || !female.getBloodPressureNormal()) {
                ss << " (Abnormal)";
            }
            ss << "\n";
            
            ss << "    Temperature: " << p.temperature;
            if (!child.getTemperatureNormal() || !male.getTemperatureNormal() || !female.getTemperatureNormal()) {
                ss << " (Abnormal)";
            }
            ss << "\n\n";
        }
    }

    return ss.str();
}