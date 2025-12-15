#ifndef GREEDYSHIFTSCHEDULER_H
#define GREEDYSHIFTSCHEDULER_H

#include <vector>
#include <queue>                 // for priority_queue
#include "VectorScheduleTable.h"

class GreedyShiftScheduler {
private:
    // ---------------- Core parameters ----------------
    int staffCount = 0;
    int dayCount = 0;
    int minOffDays = 0;
    std::vector<int> dailyRequirements;

    // ---------------- Heap helper structures ----------------
    // These MUST be visible to the whole class (not just cpp)
    struct StaffNode {
        int id;
        int worked;
        int remaining;
    };

    struct StaffCompare {
        bool operator()(const StaffNode& a, const StaffNode& b) const {
            if (a.worked != b.worked)
                return a.worked > b.worked;      // fewer worked first
            return a.remaining < b.remaining;    // more remaining first
        }
    };

    // ---------------- Internal helpers ----------------
    void calculateDailyRequirements();

public:
    // ---------------- Configuration ----------------
    void setStaffCount(int m);
    void setDayCount(int n);
    void setMinimumDaysOff(int k);

    // ---------------- Core functionality ----------------
    void generateSchedule(VectorScheduleTable& schedule);

    // ---------------- Validation ----------------
    bool validate(const VectorScheduleTable& schedule) const;
};

#endif // GREEDYSHIFTSCHEDULER_H
