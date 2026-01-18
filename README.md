  # Auto-Shift Arrangement System
### Developed by Team UsefulData

![Project Status](https://img.shields.io/badge/Status-Active-success)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%7C%20Python%20%7C%20HTML-blue)

## 📖 Overview
The **Auto-Shift Arrangement System** is a hybrid software solution designed to solve complex staff scheduling problems efficiently. It utilizes a **Greedy Algorithm** written in high-performance C++ to calculate optimal shift distributions, ensuring fair workload balance and meeting daily staffing requirements.

To make the system accessible, we built a modern web interface using **Python (Flask)**, allowing managers to input constraints and view generated schedules in a dashboard without touching the command line.

## 🚀 Key Features
* **Algorithmic Core:** Custom C++ greedy strategy to prioritize staff with the fewest hours.
* **Web Interface:** Clean HTML/CSS frontend connected via Python Flask.
* **Smart Constraints:** Handles minimum staff per day, maximum working days, and mandatory off-days.
* **Salary Calculation:** Automatically computes total payout based on daily rates.

## 📂 Project Structure
Ensure your project files are organized exactly like this:

```text
ShiftSchedulerWeb/
│
├── core/                  # C++ Backend Logic
│   ├── main.cpp           # Entry point (JSON output version)
│   ├── GreedyShiftScheduler.cpp
│   ├── GreedyShiftScheduler.h
│   ├── StaffManagerImpl.cpp
│   ├── StaffManagerImpl.h
│   ├── VectorScheduleTable.cpp
│   └── prog.exe           # (Generated after compilation)
│
├── static/                # Frontend Assets
│   └── style.css
│
├── templates/             # HTML Views
│   └── index.html
│
├── app.py                 # Python Web Server (The Bridge)
├── .gitignore             # Git configuration
└── README.md              # Project Documentation
