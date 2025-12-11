#include "GreedyShiftSchedular.h"

void GreedyShiftScheduler::setStaffCount(int m) { staffCount = m; }
void GreedyShiftScheduler::setDayCount(int n) { dayCount = n; }
void GreedyShiftScheduler::setMinimumDaysOff(int k) { minOffDays = k; }
void GreedyShiftScheduler::setDailyRequirements(const vector<int>& requirements) {
    dailyRequirements = requirements;
}

// Greedy automatic scheduling
void GreedyShiftScheduler::generateSchedule(VectorScheduleTable& schedule) {
    vector<int> workDays(staffCount, 0);

    for (int day = 0; day < dayCount; ++day) {
        int workersAssigned = 0;

        // Assign minimum required staff first
        for (int staff = 0; staff < staffCount && workersAssigned < dailyRequirements[day]; ++staff) {
            if (!schedule.isAssigned(staff, day) && workDays[staff] < (dayCount - minOffDays)) {
                schedule.assign(staff, day);
                workDays[staff]++;
                workersAssigned++;
            }
        }

        // Optional: assign extra staff if they still have enough off-days left
        for (int staff = 0; staff < staffCount && workersAssigned < staffCount; ++staff) {
            if (!schedule.isAssigned(staff, day) && workDays[staff] < (dayCount - minOffDays)) {
                schedule.assign(staff, day);
                workDays[staff]++;
                workersAssigned++;
            }
        }
    }
}
