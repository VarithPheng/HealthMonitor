#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <vector>
#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include "../../data/data.h"
#include "../child/child.h"
#include "../female/female.h"
#include "../male/male.h"
#include "../func/function.h"
#include "../database/DatabaseConnection.h"
#include <wx/spinctrl.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    // GUI Elements
    wxTextCtrl* outputText;
    wxButton* generateButton;
    wxButton* loadButton;
    wxButton* analyzeButton;
    wxStaticText* titleText;
    wxButton* inputButton;
    wxButton* lastWeekButton;
    wxButton* lastTwoWeeksButton;
    wxButton* allTimeButton;
    
    // Health check objects
    Child child;
    Male male;
    Female female;
    
    // Colors
    wxColour bgColor = wxColour(240, 240, 240);  // Light gray background
    wxColour buttonColor = wxColour(52, 152, 219);  // Blue buttons
    wxColour textColor = wxColour(44, 62, 80);  // Dark text
    wxColour normalColor = wxColour(46, 204, 113);  // Green for normal
    wxColour abnormalColor = wxColour(231, 76, 60);  // Red for abnormal
    
    // Data storage
    struct Patient {
        string name;
        int age;
        double heartRate;
        double bloodPressure;
        double temperature;
        bool isNormal;
    };
    vector<Patient> patients;
    vector<Patient> normalPatients;
    vector<Patient> abnormalPatients;
    
    // Event handlers
    void OnGenerateData(wxCommandEvent& evt);
    void OnLoadData(wxCommandEvent& evt);
    void OnAnalyzeData(wxCommandEvent& evt);
    void ProcessData();
    void DisplayResults();
    void ShowAbnormalPopup();
    void OnInputData(wxCommandEvent& evt);
    void OnTimeFilter(wxCommandEvent& evt);
    
    // Helper functions
    void LoadDataFromFile();
    string FormatResults();
    int getAgeChoice(int age);
    void GenerateNewData();
    void StyleButton(wxButton* button);
};

#endif