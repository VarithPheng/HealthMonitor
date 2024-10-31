#include "MainFrame.h"
#include <fstream>
#include <sstream>
#include <random>
#include <wx/font.h>
#include "CustomDialog.h"

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
    analyzeButton = new wxButton(panel, wxID_ANY, "Analyze");
    
    // Style buttons
    StyleButton(generateButton);
    StyleButton(loadButton);
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
    mainSizer->Add(analyzeButton, 0, wxALL | wxEXPAND | wxLEFT | wxRIGHT, 20);
    mainSizer->Add(outputText, 1, wxALL | wxEXPAND, 20);
    
    // Set sizer for panel
    panel->SetSizer(mainSizer);
    
    // Bind events
    generateButton->Bind(wxEVT_BUTTON, &MainFrame::OnGenerateData, this);
    loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadData, this);
    analyzeButton->Bind(wxEVT_BUTTON, &MainFrame::OnAnalyzeData, this);
    
    // Initially disable analyze button
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

void MainFrame::ShowAbnormalPopup()
{
    if (abnormalPatients.empty()) {
        return;
    }

    // Convert abnormal patients to PatientAlert format
    std::vector<PatientAlert> alerts;
    for (const auto& p : abnormalPatients) {
        PatientAlert alert;
        alert.name = p.name;
        alert.age = p.age;
        alert.heartRate = p.heartRate;
        alert.bloodPressure = p.bloodPressure;
        alert.temperature = p.temperature;

        // Check which vitals are abnormal
        int ageChoice = getAgeChoice(p.age);
        string ageGroup = assignAgeGroup(ageChoice);
        
        if (ageChoice <= 6) {
            child.heartRate(ageGroup, p.heartRate);
            child.bloodPressure(ageGroup, p.bloodPressure, p.bloodPressure * 0.6);
            child.temperature(ageGroup, p.temperature);
            
            alert.isHeartRateAbnormal = !child.getHeartRateNormal();
            alert.isBloodPressureAbnormal = !child.getBloodPressureNormal();
            alert.isTemperatureAbnormal = !child.getTemperatureNormal();
        } else {
            bool isMalePatient = (p.name == "Pain" || p.name == "Nagato" || 
                                p.name == "Itachi" || p.name == "Tobi" || 
                                p.name == "Madara" || p.name == "Naruto" || 
                                p.name == "Kakashi");
            
            if (isMalePatient) {
                male.heartRate(p.age, p.heartRate);
                male.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                male.temperature(p.age, p.temperature);
                
                alert.isHeartRateAbnormal = !male.getHeartRateNormal();
                alert.isBloodPressureAbnormal = !male.getBloodPressureNormal();
                alert.isTemperatureAbnormal = !male.getTemperatureNormal();
            } else {
                female.heartRate(p.age, p.heartRate);
                female.bloodPressure(p.age, p.bloodPressure, p.bloodPressure * 0.6);
                female.temperature(p.age, p.temperature);
                
                alert.isHeartRateAbnormal = !female.getHeartRateNormal();
                alert.isBloodPressureAbnormal = !female.getBloodPressureNormal();
                alert.isTemperatureAbnormal = !female.getTemperatureNormal();
            }
        }
        
        alerts.push_back(alert);
    }

    CustomDialog dialog(this, alerts);
    dialog.ShowModal();
}

void MainFrame::OnGenerateData(wxCommandEvent& evt)
{
    GenerateNewData();
    outputText->SetValue("New data generated successfully!\n");
    analyzeButton->Enable(true);
}

void MainFrame::GenerateNewData()
{
    // Constants from wrapper.cpp
    const double heart_mean = 65.9;
    const double heart_std = 9.7;
    const double systolic_bp_mean = 110.1;
    const double systolic_bp_std = 9.9;
    const double body_temp_mean = 98.25;
    const double body_temp_std = 0.73;
    const int NUM_RECORDS = 10;

    // Character names
    const vector<string> character_names = {
        "Minato", "Pain", "Konan", "Nagato", "Itachi",
        "Tobi", "Madara", "Naruto", "Boruto", "Kakashi"
    };

    // Initialize data vectors
    vector<string> name_data;
    vector<int> age_data;
    
    // Generate random data
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> name_dis(0, character_names.size() - 1);
    uniform_int_distribution<> age_dis(1, 69);
    
    for(int i = 0; i < NUM_RECORDS; i++) {
        name_data.push_back(character_names[name_dis(gen)]);
        age_data.push_back(age_dis(gen));
    }
    
    vector<double> heart_data = generate_data(heart_mean, heart_std, NUM_RECORDS);
    vector<double> systolic_bp_data = generate_data(systolic_bp_mean, systolic_bp_std, NUM_RECORDS);
    vector<double> body_temp_data = generate_data(body_temp_mean, body_temp_std, NUM_RECORDS);

    // Clear and write to file
    clear_table("data/my_data.txt");
    write_data("data/my_data.txt", 
               name_data, 
               age_data, 
               heart_data, 
               systolic_bp_data, 
               body_temp_data);
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
    
    ifstream inFile("data/my_data.txt");
    if (!inFile) {
        wxMessageBox("Error: Unable to open data file", "Error",
                    wxOK | wxICON_ERROR);
        return;
    }
    
    string line;
    getline(inFile, line); // Skip header
    
    while (getline(inFile, line)) {
        stringstream ss(line);
        Patient p;
        ss >> p.name >> p.age >> p.heartRate >> p.bloodPressure >> p.temperature;
        patients.push_back(p);
    }
    
    outputText->SetValue(wxString::Format("Data loaded successfully! Found %zu records.\n", patients.size()));
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
    
    Child child;
    Male male;
    Female female;
    
    for (auto& p : patients) {
        int ageChoice = getAgeChoice(p.age);
        string ageGroup = assignAgeGroup(ageChoice);
        bool isNormal = true;
        
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
    
    // Show popup for abnormal patients
    ShowAbnormalPopup();
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