#include "GreedyShiftScheduler.h"
#include <iostream>
#include <numeric>
#include <algorithm>

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

    // Total capacity of work assignments available
    int totalCapacity = staffCount * maxWorkDays;

    // Distribute capacity fairly across days
    int base = (dayCount == 0) ? 0 : (totalCapacity / dayCount);
    int rem  = (dayCount == 0) ? 0 : (totalCapacity % dayCount);

    for (int d = 0; d < dayCount; ++d) {
        dailyRequirements[d] = base + (d < rem ? 1 : 0);
    }

    // Safety: a day cannot require more than staffCount
    for (int d = 0; d < dayCount; ++d) {
        if (dailyRequirements[d] > staffCount) dailyRequirements[d] = staffCount;
        if (dailyRequirements[d] < 0) dailyRequirements[d] = 0;
    }
}


void GreedyShiftScheduler::generateSchedule(VectorScheduleTable& schedule) {
    calculateDailyRequirements();

    // Basic parameter checks
    if (staffCount <= 0 || dayCount <= 0) {
        cout << "Invalid staff/day count.\n";
        return;
    }
    if ((int)dailyRequirements.size() != dayCount) {
        cout << "dailyRequirements size must equal dayCount.\n";
        return;
    }

    int maxWorkDays = dayCount - minOffDays;
    if (maxWorkDays < 0) {
        cout << "Invalid minOffDays (cannot exceed dayCount).\n";
        return;
    }

    // Feasibility check: total required assignments must fit total capacity
    int totalRequired = 0;
    for (int d = 0; d < dayCount; ++d) {
        if (dailyRequirements[d] < 0) {
            cout << "Invalid requirement on day " << (d + 1) << ".\n";
            return;
        }
        if (dailyRequirements[d] > staffCount) {
            cout << "Impossible: day " << (d + 1) << " requires more than staffCount.\n";
            return;
        }
        totalRequired += dailyRequirements[d];
    }

    int totalCapacity = staffCount * maxWorkDays;
    if (totalRequired > totalCapacity) {
        cout << "Impossible: total required shifts (" << totalRequired
             << ") > total capacity (" << totalCapacity << ").\n";
        return;
    }

    // Target work distribution (fair): everyone gets base, first 'rem' get +1
    vector<int> target(staffCount, 0);
    int base = totalRequired / staffCount;
    int rem  = totalRequired % staffCount;

    for (int s = 0; s < staffCount; ++s) {
        target[s] = base + (s < rem ? 1 : 0);
        target[s] = min(target[s], maxWorkDays);
    }

    // In rare cases (because of maxWorkDays cap), we may still need to redistribute
    // but feasibility already guaranteed, so we can fill remaining by giving to those with room.
    int targetSum = accumulate(target.begin(), target.end(), 0);
    int stillNeed = totalRequired - targetSum;
    if (stillNeed > 0) {
        for (int s = 0; s < staffCount && stillNeed > 0; ++s) {
            while (stillNeed > 0 && target[s] < maxWorkDays) {
                target[s]++;
                stillNeed--;
            }
        }
    }

    // Track actual work assigned
    vector<int> worked(staffCount, 0);

    // Assign day by day
    for (int day = 0; day < dayCount; ++day) {
        int need = dailyRequirements[day];

        // Build candidate list of staff who can still work (worked < target and worked < maxWorkDays)
        vector<int> candidates;
        candidates.reserve(staffCount);
        for (int s = 0; s < staffCount; ++s) {
            if (worked[s] < target[s] && worked[s] < maxWorkDays) {
                candidates.push_back(s);
            }
        }

        // Sort for fairness:
        // 1) staff with LESS worked days first
        // 2) if tie, staff with MORE remaining target first (so we don't get stuck later)
        sort(candidates.begin(), candidates.end(), [&](int a, int b) {
            if (worked[a] != worked[b]) return worked[a] < worked[b];
            int ra = target[a] - worked[a];
            int rb = target[b] - worked[b];
            return ra > rb;
        });

        int assigned = 0;

        // First pass: assign from best candidates
        for (int idx = 0; idx < (int)candidates.size() && assigned < need; ++idx) {
            int s = candidates[idx];
            if (!schedule.isAssigned(s, day) && worked[s] < maxWorkDays) {
                schedule.assign(s, day);
                worked[s]++;
                assigned++;
            }
        }

        // If still not enough, relax to ANYONE with remaining capacity (still respecting maxWorkDays)
        if (assigned < need) {
            vector<int> fallback;
            fallback.reserve(staffCount);
            for (int s = 0; s < staffCount; ++s) {
                if (worked[s] < maxWorkDays) fallback.push_back(s);
            }

            sort(fallback.begin(), fallback.end(), [&](int a, int b) {
                if (worked[a] != worked[b]) return worked[a] < worked[b];
                return a < b;
            });

            for (int idx = 0; idx < (int)fallback.size() && assigned < need; ++idx) {
                int s = fallback[idx];
                if (!schedule.isAssigned(s, day) && worked[s] < maxWorkDays) {
                    schedule.assign(s, day);
                    worked[s]++;
                    assigned++;
                }
            }
        }

        if (assigned < need) {
            cout << "Failed to meet requirement on day " << (day + 1)
                 << " (needed " << need << ", assigned " << assigned << ").\n";
            return;
        }
    }

    // Debug: show daily requirements
    cout << "Daily Requirements: ";
    for (int d = 0; d < dayCount; ++d) cout << dailyRequirements[d] << " ";
    cout << "\n";

    // Debug: show staff worked/off summary (fairness check)
    cout << "Staff summary (work/off):\n";
    for (int s = 0; s < staffCount; ++s) {
        int off = dayCount - worked[s];
        cout << "Staff " << s + 1 << ": work=" << worked[s] << ", off=" << off << "\n";
    }
}

bool GreedyShiftScheduler::validate(const VectorScheduleTable& schedule) const {
    if ((int)dailyRequirements.size() != dayCount) return false;

    int maxWorkDays = dayCount - minOffDays;

    // Each staff must have at least k off => work <= n-k
    for (int s = 0; s < staffCount; ++s) {
        int w = schedule.countWorkingDays(s);
        if (w > maxWorkDays) return false;
    }

    // Each day must meet requirement
    for (int d = 0; d < dayCount; ++d) {
        int w = schedule.countWorkersOnDay(d);
        if (w < dailyRequirements[d]) return false;
    }

    return true;
}
