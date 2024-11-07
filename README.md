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

## Compile with GUI

```bash
g++ -o health_monitor_gui src/gui/App.cpp src/gui/MainFrame.cpp src/gui/CustomDialog.cpp src/func/function.cpp src/male/male.cpp src/female/female.cpp src/child/child.cpp data/data.cpp `wx-config --cxxflags --libs` -std=c++11
```

## Run with GUI

```bash
./health_monitor_gui
```

## Compile without GUI

```bash
g++ -o health_check src/main/main.cpp src/func/function.cpp src/male/male.cpp src/female/female.cpp src/child/child.cpp -std=c++11
```

## Run without GUI

```bash
./health_check
```

## Prerequisites for PostgreSQL

```bash
brew install libpq
```

## Compile with GUI and PostgreSQL

```bash
g++ -o health_monitor_gui src/gui/App.cpp src/gui/MainFrame.cpp src/gui/PatientDetailsDialog.cpp src/func/function.cpp src/male/male.cpp src/female/female.cpp src/child/child.cpp src/database/DatabaseConnection.cpp data/data.cpp `wx-config --cxxflags --libs` -I/opt/homebrew/opt/libpq/include -L/opt/homebrew/opt/libpq/lib -lpq -std=c++11
```
