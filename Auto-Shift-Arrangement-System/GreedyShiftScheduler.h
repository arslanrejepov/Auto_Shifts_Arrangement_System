#ifndef GREEDYSHIFTSCHEDULER_H
#define GREEDYSHIFTSCHEDULER_H

#include <vector>
#include "VectorScheduleTable.h"

class GreedyShiftScheduler {
private:
    int staffCount = 0;
    int dayCount = 0;
    int minOffDays = 0;
    std::vector<int> dailyRequirements;

public:
    // Set constraints
    void setStaffCount(int m);
    void setDayCount(int n);
    void setMinimumDaysOff(int k);

    // Generate schedule
    void generateSchedule(VectorScheduleTable& schedule);

    // Validation
    bool validate(const VectorScheduleTable& schedule) const;

private:
    // If user doesn't provide requirements, make a default
    void calculateDailyRequirements();
};

#endif // GREEDYSHIFTSCHEDULER_H
