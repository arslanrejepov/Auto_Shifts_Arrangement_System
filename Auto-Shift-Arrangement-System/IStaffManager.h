#ifndef ISTAFF_MANAGER_H
#define ISTAFF_MANAGER_H

class IStaffManager {
public:
    virtual ~IStaffManager() = default;

    virtual void initialize(int staffCount, int dayCount, int minOffDays) = 0;

    virtual void addWorkDay(int staffID) = 0;
    virtual void addOffDay(int staffID) = 0;

    virtual int getWorkDays(int staffID) const = 0;
    virtual int getOffDays(int staffID) const = 0;

    virtual bool canWork(int staffID, int remainingDays) const = 0;
};

#endif 