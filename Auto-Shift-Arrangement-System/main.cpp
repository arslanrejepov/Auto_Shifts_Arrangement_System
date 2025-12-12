#include <iostream>
#include "VectorScheduleTable.h"
#include "GreedyShiftScheduler.h"

using namespace std;

int main() {
    int staffCount, dayCount, minOffDays;

    cout << "Enter number of staff: ";
    cin >> staffCount;

    cout << "Enter number of days: ";
    cin >> dayCount;

    cout << "Enter minimum days off per staff: ";
    cin >> minOffDays;

    if (staffCount <= 0 || dayCount <= 0) {
        cout << "Error: staffCount and dayCount must be positive.\n";
        return 0;
    }
    if (minOffDays < 0 || minOffDays > dayCount) {
        cout << "Error: minOffDays must be between 0 and dayCount.\n";
        return 0;
    }

    VectorScheduleTable schedule;
    schedule.initialize(staffCount, dayCount);

    GreedyShiftScheduler scheduler;
    scheduler.setStaffCount(staffCount);
    scheduler.setDayCount(dayCount);
    scheduler.setMinimumDaysOff(minOffDays);

    // Do NOT setDailyRequirements — scheduler will compute it automatically
    scheduler.generateSchedule(schedule);

    if (!scheduler.validate(schedule)) {
        cout << "\nGenerated schedule is INVALID.\n";
        return 0;
    }

    cout << "\nAutomatically generated schedule:\n";
    schedule.print();

    return 0;
}
