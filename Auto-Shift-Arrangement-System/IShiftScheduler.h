#ifndef ISHIFT_SCHEDULER_H
#define ISHIFT_SCHEDULER_H

#include <vector>
#include "IScheduleTable.h"
using namespace std;


class IShiftScheduler {
public:
    virtual ~IShiftScheduler() = default;

    // Load constraints
    virtual void setStaffCount(int m) = 0;
    virtual void setDayCount(int n) = 0;
    virtual void setMinimumDaysOff(int k) = 0;
    virtual void setDailyRequirements(const vector<int>& requirements) = 0;

    // Generate the schedule
    virtual void generateSchedule(IScheduleTable& schedule) = 0;

    // Validation
    virtual bool validate(const IScheduleTable& schedule) const = 0;
};

#endif // ISHIFT_SCHEDULER_H