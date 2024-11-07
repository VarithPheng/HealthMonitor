#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <vector>
#include <wx/stattext.h>
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
    wxPanel* resultsPanel;
    wxBoxSizer* resultsSizer;
    wxScrolledWindow* scrolledWindow;
    
    // Colors
    wxColour bgColor = wxColour(26, 32, 44);
    wxColour buttonColor = wxColour(66, 153, 225);
    wxColour textColor = wxColour(237, 242, 247);
    
    // Database connection
    PGconn* dbConn;
    
    // Analysis mode flag
    bool isAnalyzeMode = false;
    
    // Data structures
    struct VitalRecord {
        wxString weekOf;
        double heartRate;
        double bloodPressure;
        double temperature;
        bool isNormal;
    };

    struct Patient {
        wxString name;
        wxString gender;
        wxString ageGroup;
        int age;
        std::vector<VitalRecord> records;
    };

    std::vector<Patient> normalPatients;
    std::vector<Patient> abnormalPatients;
    
    // Event handlers
    void OnGenerateData(wxCommandEvent& evt);
    void OnLoadData(wxCommandEvent& evt);
    void OnAnalyzeData(wxCommandEvent& evt);
    
    // Helper functions
    bool ConnectToDatabase();
    void LoadDataFromDB();
    void DisplayResults();
};

#endif