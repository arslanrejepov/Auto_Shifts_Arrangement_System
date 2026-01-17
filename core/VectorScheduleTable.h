#ifndef VECTORSCHEDULETABLE_H
#define VECTORSCHEDULETABLE_H

#include "IScheduleTable.h"
#include <vector>
#include <iostream>

using namespace std;

class VectorScheduleTable : public IScheduleTable {
private:
    vector<vector<int>> schedule; // rows = staff, columns = days

public:
    void initialize(int staffCount, int dayCount) override;
    void assign(int staffID, int dayID) override;
    void unassign(int staffID, int dayID) override;
    bool isAssigned(int staffID, int dayID) const override;
    int countWorkingDays(int staffID) const override;
    int countWorkersOnDay(int dayID) const override;
    void print() const override;
};

#endif // VECTORSCHEDULETABLE_H
