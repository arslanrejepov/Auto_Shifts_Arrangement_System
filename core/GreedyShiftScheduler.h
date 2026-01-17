#ifndef GREEDYSHIFTSCHEDULER_H
#define GREEDYSHIFTSCHEDULER_H

#include <queue>
#include <vector>
#include <iostream>
#include "IShiftScheduler.h"

using namespace std;

class GreedyShiftScheduler : public IShiftScheduler {
private:
    int staffCount = 0;
    int dayCount = 0;
    int minOffDays = 0;
    int dailyRequirements = 0;

    struct StaffNode {
        int id;
        int worked;
        int remaining;
    };

    struct StaffCompare {
        bool operator()(const StaffNode& a, const StaffNode& b) const {
            if (a.worked != b.worked)
                return a.worked > b.worked;        // fewer worked first
            if (a.remaining != b.remaining)
                return a.remaining < b.remaining;  // more remaining first
            return a.id > b.id;                    // smaller id first
        }
    };

    void calculateDailyRequirements();

public:
    void setStaffCount(int m) override;
    void setDayCount(int n) override;
    void setMinimumDaysOff(int k) override;
    void setDailyRequirements(const int& r) override;

    void generateSchedule(
        IScheduleTable& schedule,
        IStaffManager& staffMgr
    ) override;

    bool validate(const IScheduleTable& schedule) const override;
};

#endif
