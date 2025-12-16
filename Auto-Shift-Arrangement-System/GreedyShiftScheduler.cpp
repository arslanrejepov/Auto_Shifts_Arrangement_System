#include "GreedyShiftScheduler.h"

using namespace std;

void GreedyShiftScheduler::setStaffCount(int m) {staffCount = m;}
void GreedyShiftScheduler::setDayCount(int n) {dayCount = n;}
void GreedyShiftScheduler::setMinimumDaysOff(int k) {minOffDays = k;}
void GreedyShiftScheduler::setDailyRequirements(const int& requirements) {dailyRequirements = requirements; }

// Auto-calc only when user didn't provide dailyRequirements
void GreedyShiftScheduler::calculateDailyRequirements() {
    if (staffCount <= 0 || dayCount <= 0) {
        dailyRequirements = 0;
        return;
    }

    int maxWorkDays = dayCount - minOffDays;
    if (maxWorkDays < 0) maxWorkDays = 0;

    int totalCapacity = staffCount * maxWorkDays;
    dailyRequirements = (dayCount == 0) ? 0 : (totalCapacity / dayCount);
}

void GreedyShiftScheduler::generateSchedule(IScheduleTable& schedule) {
    // Reset “query after generation” state
    schedulePtr = nullptr;

    calculateDailyRequirements();

    if (staffCount <= 0 || dayCount <= 0) {
        cout << "Error: Invalid staff/day count.\n";
        return;
    }
    if (minOffDays < 0 || minOffDays > dayCount) {
        cout << "Error: Invalid minOffDays.\n";
        return;
    }
    if (dailyRequirements < 0) {
        cout << "Error: Invalid dailyRequirements.\n";
        return;
    }

    int maxWorkDays = dayCount - minOffDays;

    // Compute a fair target of total work-days per staff (used only as a guide)
    int totalRequired = dayCount * dailyRequirements;
    vector<int> target(staffCount, 0);
    int base = (staffCount == 0) ? 0 : totalRequired / staffCount;
    int rem  = (staffCount == 0) ? 0 : totalRequired % staffCount;

    for (int s = 0; s < staffCount; ++s) {
        target[s] = min(base + (s < rem ? 1 : 0), maxWorkDays);
    }

    // Initialize schedule + internal manager
    schedule.initialize(staffCount, dayCount);
    staffMgr.initialize(staffCount, dayCount, minOffDays);
    schedulePtr = &schedule; // remember for extraStaff(dayID)

    // Generate schedule day by day
    for (int day = 0; day < dayCount; ++day) {
        int need = dailyRequirements;
        int assigned = 0;

        // Build PQ: fewest worked first, then more remaining capacity
        priority_queue<StaffNode, vector<StaffNode>, StaffCompare> pq;
        for (int s = 0; s < staffCount; ++s) {
            int worked = staffMgr.getWorkDays(s);
            if (worked < maxWorkDays && worked < target[s]) {
                pq.push({s, worked, target[s] - worked});
            }
        }

        // If PQ doesn't have enough (targets too tight), allow anyone with capacity
        if ((int)pq.size() < need) {
            for (int s = 0; s < staffCount; ++s) {
                int worked = staffMgr.getWorkDays(s);
                if (worked < maxWorkDays) {
                    pq.push({s, worked, maxWorkDays - worked});
                }
            }
        }

        while (!pq.empty() && assigned < need) {
            StaffNode cur = pq.top();
            pq.pop();

            int s = cur.id;
            if (!schedule.isAssigned(s, day) && staffMgr.getWorkDays(s) < maxWorkDays) {
                schedule.assign(s, day);
                staffMgr.addWorkDay(s);
                assigned++;
            }
        }

        // Count off-days for those NOT assigned
        for (int s = 0; s < staffCount; ++s) {
            if (!schedule.isAssigned(s, day)) {
                staffMgr.addOffDay(s);
            }
        }
    }

    // Print summary
    cout << "\nDaily Requirements (each day): " << dailyRequirements << "\n\n";
    cout << "Staff Summary (work/off):\n";
    for (int s = 0; s < staffCount; ++s) {
        cout << "Staff " << (s + 1)
             << ": work=" << staffMgr.getWorkDays(s)
             << ", off=" << staffMgr.getOffDays(s) << "\n";
    }
    cout << "\n";
}

vector<int> GreedyShiftScheduler::extraStaff(int dayID) const {
    vector<int> result;

    if (!schedulePtr) return result; // generateSchedule() not called yet
    if (dayID < 0 || dayID >= dayCount) return result;
    if (staffCount <= 0 || dayCount <= 0) return result;

    int maxWorkDays = dayCount - minOffDays;
    if (maxWorkDays < 0) maxWorkDays = 0;

    priority_queue<StaffNode, vector<StaffNode>, StaffCompare> pq;
    for (int s = 0; s < staffCount; ++s) {
        if (schedulePtr->isAssigned(s, dayID)) continue; // already working today

        int worked = staffMgr.getWorkDays(s);
        if (worked >= maxWorkDays) continue; // no capacity left

        pq.push({s, worked, maxWorkDays - worked});
    }

    while (!pq.empty()) {
        result.push_back(pq.top().id);
        pq.pop();
    }
    return result;
}

bool GreedyShiftScheduler::hasExtraStaff(int dayID) const {
    return !extraStaff(dayID).empty();
}

bool GreedyShiftScheduler::validate(const IScheduleTable& schedule) const {
    int maxWorkDays = dayCount - minOffDays;
    if (maxWorkDays < 0) return false;

    for (int s = 0; s < staffCount; ++s) {
        if (schedule.countWorkingDays(s) > maxWorkDays) return false;
    }

    for (int d = 0; d < dayCount; ++d) {
        if (schedule.countWorkersOnDay(d) < dailyRequirements) return false;
    }

    return true;
}
