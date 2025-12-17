#ifndef ISHIFT_SCHEDULER_H
#define ISHIFT_SCHEDULER_H

#include "IScheduleTable.h"
#include "IStaffManager.h"

class IShiftScheduler {
public:
    virtual ~IShiftScheduler() = default;

    virtual void setStaffCount(int m) = 0;
    virtual void setDayCount(int n) = 0;
    virtual void setMinimumDaysOff(int k) = 0;
    virtual void setDailyRequirements(const int& r) = 0;

    virtual void generateSchedule(
        IScheduleTable& schedule,
        IStaffManager& staffMgr
    ) = 0;

    virtual bool validate(const IScheduleTable& schedule) const = 0;
};

#endif
