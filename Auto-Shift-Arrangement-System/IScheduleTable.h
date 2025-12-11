#ifndef ISCHEDULE_TABLE_H
#define ISCHEDULE_TABLE_H


class IScheduleTable {
public:
    virtual ~IScheduleTable() = default;

    // Initialize table size m staff × n days
    virtual void initialize(int staffCount, int dayCount) = 0;

    // Set or get assignment
    virtual void assign(int staffID, int dayID) = 0;
    virtual void unassign(int staffID, int dayID) = 0;
    virtual bool isAssigned(int staffID, int dayID) const = 0;

    // Query counts
    virtual int countWorkingDays(int staffID) const = 0;
    virtual int countWorkersOnDay(int dayID) const = 0;

    // For printing or exporting
    virtual void print() const = 0;
};


#endif // ISCHEDULE_TABLE_H