#ifndef GREEDYSHIFTSCHEDULER_H
#define GREEDYSHIFTSCHEDULER_H

#include "IScheduleTable.h"
#include "VectorScheduleTable.h"
#include <vector>
#include <iostream>

using namespace std;

class GreedyShiftScheduler {
private:
    int staffCount;
    int dayCount;
    int minOffDays;
    vector<int> dailyRequirements;

public:
    void setStaffCount(int m);
    void setDayCount(int n);
    void setMinimumDaysOff(int k);
    void setDailyRequirements(const vector<int>& requirements);

    void generateSchedule(VectorScheduleTable& schedule);
};

#endif // GREEDYSHIFTSCHEDULER_H
