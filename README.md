# Auto-Shift Arrangement System
### Developed by Team UsefulData

![Project Status](https://img.shields.io/badge/Status-Active-success)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%7C%20Python%20%7C%20HTML-blue)

## 📖 Overview
The **Auto-Shift Arrangement System** was designed and built as a final project for our **Data Structure Course**. 

It demonstrates the practical application of advanced data structures (Heaps, Priority Queues, Vectors) to solve real-world scheduling problems. The system utilizes a **Greedy Algorithm** in C++ to calculate optimal shift distributions, ensuring fair workload balance and meeting daily staffing requirements.

To make the system accessible, we built a modern web interface using **Python (Flask)**, allowing managers to input constraints and view generated schedules in a dashboard without touching the command line.

## 🚀 Key Features
* **Algorithmic Core:** Custom C++ greedy strategy to prioritize staff with the fewest hours.
* **Web Interface:** Clean HTML/CSS frontend connected via Python Flask.
* **Smart Constraints:** Handles minimum staff per day, maximum working days, and mandatory off-days.
* **Salary Calculation:** Automatically computes total payout based on daily rates.

## 📂 Project Structure
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
```
---

# Install 

```
pip install requirements.txt

```

---

## ▶️ How to Run

```
g++ core/main.cpp core/GreedyShiftScheduler.cpp core/StaffManagerImpl.cpp core VectorScheduleTable.cpp -o core/prog.exe

uvicorn app:app --reload

```


## 👥 Collaborators
---
A huge thanks to the UsefulData team for bringing this project to life:
* **[Abdulmajeed Tawfik](https://github.com/Abdulmajeed-Tawfik)**
* **[ASMAA BEQUI](https://github.com/Asmaabe01)**
* **[Guncha REJEPOVA](https://github.com/guncha3110)**
* **[Muhammetgylyjov Baygeldi](https://github.com/BaygeldiAza)**
