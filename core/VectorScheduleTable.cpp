#include "VectorScheduleTable.h"

// Initialize the schedule with all zeros
void VectorScheduleTable::initialize(int staffCount, int dayCount) {
    schedule = vector<vector<int>>(staffCount, vector<int>(dayCount, 0));
}

void VectorScheduleTable::assign(int staffID, int dayID) {
    if (staffID >= 0 && staffID < schedule.size() && dayID >= 0 && dayID < schedule[0].size()) {
        schedule[staffID][dayID] = 1;
    }
}

void VectorScheduleTable::unassign(int staffID, int dayID) {
    if (staffID >= 0 && staffID < schedule.size() && dayID >= 0 && dayID < schedule[0].size()) {
        schedule[staffID][dayID] = 0;
    }
}


// Check if a staff member is assigned to work on a specific day
bool VectorScheduleTable::isAssigned(int staffID, int dayID) const {
    return schedule[staffID][dayID] == 1;
}

// Count how many days a staff member is working
int VectorScheduleTable::countWorkingDays(int staffID) const {
    int count = 0;
    for (int i = 0; i < schedule[staffID].size(); ++i)
        if (schedule[staffID][i] == 1) count++;
    return count;
}

// Count how many staff members are working on a specific day
int VectorScheduleTable::countWorkersOnDay(int dayID) const {
    int count = 0;
    for (int i = 0; i < schedule.size(); ++i)
        if (schedule[i][dayID] == 1) count++;
    return count;
}

// Print the schedule matrix
void VectorScheduleTable::print() const {
    cout << "Schedule (rows = staff, columns = days):\n";
    for (const auto& row : schedule) {
        for (int cell : row) cout << cell << " ";
        cout << endl;
    }
}