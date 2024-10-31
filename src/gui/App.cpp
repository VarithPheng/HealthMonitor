#include <wx/wx.h>
#include "MainFrame.h"

class App : public wxApp
{
public:
    bool OnInit()
    {
        MainFrame* mainFrame = new MainFrame("Health Monitor");
        mainFrame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);