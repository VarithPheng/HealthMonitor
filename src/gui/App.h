#ifndef APP_H
#define APP_H

#include <wx/wx.h>
#include "MainFrame.h"

class App : public wxApp {
public:
    virtual bool OnInit();
private:
    MainFrame* mainFrame{nullptr};  // Main window of the application
};

#endif 