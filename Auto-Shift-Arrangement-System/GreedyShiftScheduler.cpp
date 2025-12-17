#include "GreedyShiftScheduler.h"

void GreedyShiftScheduler::setStaffCount(int m) { staffCount = m; }
void GreedyShiftScheduler::setDayCount(int n) { dayCount = n; }
void GreedyShiftScheduler::setMinimumDaysOff(int k) { minOffDays = k; }
void GreedyShiftScheduler::setDailyRequirements(const int& r) { dailyRequirements = r; }

void GreedyShiftScheduler::calculateDailyRequirements() {
    if (dailyRequirements > 0) return;

    int maxWorkDays = dayCount - minOffDays;
    if (maxWorkDays < 0) maxWorkDays = 0;

    int totalCapacity = staffCount * maxWorkDays;
    dailyRequirements = (dayCount == 0) ? 0 : totalCapacity / dayCount;
}

void GreedyShiftScheduler::generateSchedule(
    IScheduleTable& schedule,
    IStaffManager& staffMgr
) {
    calculateDailyRequirements();
    schedule.initialize(staffCount, dayCount);

    int maxWorkDays = dayCount - minOffDays;

    for (int day = 0; day < dayCount; ++day) {
        priority_queue<StaffNode, vector<StaffNode>, StaffCompare> pq;

        // 🔹 build heap using ORIGINAL logic
        for (int s = 0; s < staffCount; ++s) {
            int worked = staffMgr.getWorkDays(s);
            int remaining = maxWorkDays - worked;

            if (remaining > 0) {
                pq.push({ s, worked, remaining });
            }
        }

        int assigned = 0;

        while (!pq.empty() && assigned < dailyRequirements) {
            StaffNode cur = pq.top();
            pq.pop();

            if (!schedule.isAssigned(cur.id, day) && staffMgr.canWork(cur.id)) {
                schedule.assign(cur.id, day);
                staffMgr.addWorkDay(cur.id);
                assigned++;
            }
        }

        // count off-days
        for (int s = 0; s < staffCount; ++s) {
            if (!schedule.isAssigned(s, day)) {
                staffMgr.addOffDay(s);
            }
        }
    }

    cout << "\nDaily Requirements (each day): "
         << dailyRequirements << endl;
}

bool GreedyShiftScheduler::validate(const IScheduleTable& schedule) const {
    int maxWorkDays = dayCount - minOffDays;

    for (int s = 0; s < staffCount; ++s)
        if (schedule.countWorkingDays(s) > maxWorkDays)
            return false;

    for (int d = 0; d < dayCount; ++d)
        if (schedule.countWorkersOnDay(d) < dailyRequirements)
            return false;

    return true;
}
