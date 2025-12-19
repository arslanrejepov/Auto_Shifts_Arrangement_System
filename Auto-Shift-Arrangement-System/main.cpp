#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#include "VectorScheduleTable.h"
#include "GreedyShiftScheduler.h"
#include "StaffManagerImpl.h"

using namespace std;

/* ---------- INPUT VALIDATION HELPERS ---------- */

int readPositiveInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x > 0) return x;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int readIntLessThan(const string& prompt, int upperExclusive) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= 0 && x < upperExclusive) return x;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/* ---------- PRINT HELPERS ---------- */

void printSummary(const IStaffManager& mgr, int staffCount) {
    cout << "\nStaff Summary (work/off):\n";
    for (int s = 0; s < staffCount; ++s)
        cout << "Staff " << s + 1
             << ": work=" << mgr.getWorkDays(s)
             << ", off=" << mgr.getOffDays(s) << "\n";
}

int autoAssignExtra(
    IScheduleTable& schedule,
    IStaffManager& mgr,
    int staffCount,
    int dayID
) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    for (int s = 0; s < staffCount; ++s)
        if (!schedule.isAssigned(s, dayID) && mgr.canWork(s))
            pq.push({mgr.getWorkDays(s), s});

    if (pq.empty()) return -1;

    int s = pq.top().second;
    schedule.assign(s, dayID);
    mgr.addWorkDay(s);
    mgr.removeOffDay(s);
    return s;
}

/* ---------- MAIN ---------- */

int main() {
    int staffCount = readPositiveInt(
        "Input the number of working staff (positive integer): "
    );

    int dayCount = readPositiveInt(
        "Input the number of days (positive integer): "
    );

    int minOffDays = readIntLessThan(
        "Input the number of leave days per each staff member (must be less than total days): ",
        dayCount
    );

    VectorScheduleTable schedule;
    StaffManagerImpl staffMgr;
    staffMgr.initialize(staffCount, dayCount, minOffDays);

    GreedyShiftScheduler scheduler;
    scheduler.setStaffCount(staffCount);
    scheduler.setDayCount(dayCount);
    scheduler.setMinimumDaysOff(minOffDays);

    scheduler.generateSchedule(schedule, staffMgr);

    schedule.print();
    printSummary(staffMgr, staffCount);

    while (true) {
        int day;
        cout << "\nDay (1.." << dayCount << ", 0=exit): ";
        cin >> day;

        if (!cin || day < 0 || day > dayCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (day == 0) break;
        int d = day - 1;

        cout << "1) Auto assign extra\n2) Emergency unassign\nChoose: ";
        int op;
        cin >> op;

        if (!cin || (op != 1 && op != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (op == 1) {
            int s = autoAssignExtra(schedule, staffMgr, staffCount, d);
            if (s == -1) cout << "No available staff.\n";
            else cout << "Auto-assigned Staff " << s + 1 << "\n";
        }
        else {
            vector<int> working;
            cout << "Working staff:\n";
            for (int s = 0; s < staffCount; ++s)
                if (schedule.isAssigned(s, d)) {
                    cout << s + 1 << " ";
                    working.push_back(s);
                }

            cout << "\nPick staff: ";
            int pick;
            cin >> pick;
            pick--;

            if (cin && find(working.begin(), working.end(), pick) != working.end()) {
                schedule.unassign(pick, d);
                staffMgr.removeWorkDay(pick);
                staffMgr.addOffDay(pick);
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        schedule.print();
        printSummary(staffMgr, staffCount);
    }

    double rate;
    cout << "\nEnter daily salary rate: ";
    while (!(cin >> rate) || rate < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter daily salary rate: ";
    }

    cout << "\nStaff Salaries:\n";
    for (int s = 0; s < staffCount; ++s)
        cout << "Staff " << s + 1
             << ": $" << staffMgr.staffSalary(s, rate) << "\n";

    return 0;
}
