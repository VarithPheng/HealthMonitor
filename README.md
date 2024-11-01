# HealthMonitor

A C++ GUI application for monitoring patient vital signs and detecting abnormal health conditions.

## Features

- Generate random patient data with realistic vital signs
- Load and analyze patient health data
- Detect abnormal vital signs based on age and gender
- Visual alerts for patients requiring attention
- User-friendly GUI interface
- Detailed health status reports

## Prerequisites

Before you begin, ensure you have the following installed:

- C++ compiler (supporting C++11 or later)
- wxWidgets library (for GUI)
- Make or similar build system

## Compile

```bash
g++ -o health_monitor_gui \
src/gui/App.cpp \
src/gui/MainFrame.cpp \
src/gui/CustomDialog.cpp \
src/child/child.cpp \
src/female/female.cpp \
src/male/male.cpp \
src/func/function.cpp \
data/data.cpp \
wx-config --cxxflags --libs \
-std=c++11
```

## Run the program

```bash
./health_monitor_gui
```
