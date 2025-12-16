#include "GreedyShiftScheduler.h"
#include <iostream>
#include <queue>  // for priority_queue

using namespace std;

void GreedyShiftScheduler::setStaffCount(int m) {
    staffCount = m;
}

void GreedyShiftScheduler::setDayCount(int n) {
    dayCount = n;
}

void GreedyShiftScheduler::setMinimumDaysOff(int k) {
    minOffDays = k;
}

void GreedyShiftScheduler::calculateDailyRequirements() {
    dailyRequirements.assign(dayCount, 0);

    int maxWorkDays = dayCount - minOffDays;
    if (maxWorkDays < 0) maxWorkDays = 0;

    int totalCapacity = staffCount * maxWorkDays;

    int base = (dayCount == 0) ? 0 : totalCapacity / dayCount;
    int rem  = (dayCount == 0) ? 0 : totalCapacity % dayCount;

    for (int d = 0; d < dayCount; ++d) {
        dailyRequirements[d] = base + (d < rem ? 1 : 0);
    }

}

void GreedyShiftScheduler::generateSchedule(VectorScheduleTable& schedule) {
    calculateDailyRequirements();

    if (staffCount <= 0 || dayCount <= 0) {
        cout << "Invalid staff/day count.\n";
        return;
    }

    int maxWorkDays = dayCount - minOffDays;
    if (maxWorkDays < 0) {
        cout << "Invalid minOffDays.\n";
        return;
    }

    int totalRequired = 0;
    for (int d = 0; d < dayCount; ++d) {
        if (dailyRequirements[d] < 0 || dailyRequirements[d] > staffCount) {
            cout << "Invalid requirement on day " << d + 1 << ".\n";
            return;
        }
        totalRequired += dailyRequirements[d];
    }

    vector<int> target(staffCount, 0);
    int base = totalRequired / staffCount;
    int rem  = totalRequired % staffCount;

    for (int s = 0; s < staffCount; ++s) {
        target[s] = min(base + (s < rem ? 1 : 0), maxWorkDays);
    }
   

    vector<int> worked(staffCount, 0);

    for (int day = 0; day < dayCount; ++day) {
        int need = dailyRequirements[day];
        int assigned = 0;

        priority_queue<StaffNode, vector<StaffNode>, StaffCompare> pq;

        for (int s = 0; s < staffCount; ++s) {
            if (worked[s] < target[s] && worked[s] < maxWorkDays) {
                pq.push({s, worked[s], target[s] - worked[s]});
            }
        }

        while (!pq.empty() && assigned < need) {
            StaffNode cur = pq.top();
            pq.pop();

            int s = cur.id;
            if (!schedule.isAssigned(s, day) && worked[s] < maxWorkDays) {
                schedule.assign(s, day);
                worked[s]++;
                assigned++;
            }
        }


    }

    cout << "Daily Requirements: ";
    for (int d = 0; d < dayCount; ++d)
        cout << dailyRequirements[d] << " ";
    cout << "\n";

    cout << "Staff summary (work/off):\n";
    for (int s = 0; s < staffCount; ++s) {
        cout << "Staff " << s + 1
             << ": work=" << worked[s]
             << ", off=" << (dayCount - worked[s]) << "\n";
    }
}

bool GreedyShiftScheduler::validate(const VectorScheduleTable& schedule) const {
    if ((int)dailyRequirements.size() != dayCount)
        return false;

    int maxWorkDays = dayCount - minOffDays;

    for (int s = 0; s < staffCount; ++s) {
        if (schedule.countWorkingDays(s) > maxWorkDays)
            return false;
    }

    for (int d = 0; d < dayCount; ++d) {
        if (schedule.countWorkersOnDay(d) < dailyRequirements[d])
            return false;
    }

    return true;
}
