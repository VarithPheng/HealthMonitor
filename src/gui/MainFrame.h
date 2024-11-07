#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <vector>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <libpq-fe.h>
#include "PatientDetailsDialog.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
    ~MainFrame();

private:
    // GUI Elements
    wxButton* generateButton;
    wxButton* loadButton;
    wxButton* analyzeButton;
    wxStaticText* titleText;
    wxChoice* timeFilter;
    wxScrolledWindow* scrolledWindow;
    wxPanel* resultsPanel;
    wxBoxSizer* resultsSizer;
    
    // Colors
    wxColour bgColor = wxColour(26, 32, 44);
    wxColour buttonColor = wxColour(66, 153, 225);
    wxColour textColor = wxColour(237, 242, 247);
    
    // Database connection
    PGconn* dbConn = nullptr;
    
    // Data structures
    struct Patient {
        wxString name;
        wxString gender;
        wxString ageGroup;
        int age;
        double heartRate;
        double bloodPressure;
        double temperature;
        bool isNormal;
        wxString recordedAt;
    };

    std::vector<Patient> normalPatients;
    std::vector<Patient> abnormalPatients;
    
    // Event handlers
    void OnGenerateData(wxCommandEvent& evt);
    void OnLoadData(wxCommandEvent& evt);
    void OnAnalyzeData(wxCommandEvent& evt);
    void OnTimeFilterChange(wxCommandEvent& evt);
    
    // Helper functions
    bool ConnectToDatabase();
    void LoadDataFromDB();
    void ProcessData();
    void DisplayResults();
    void CreatePatientPanel(wxPanel* parent, const Patient& patient, bool isNormal);
    wxString GetTimeFilterCondition();
};

#endif