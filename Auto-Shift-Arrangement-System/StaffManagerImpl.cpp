#include "StaffManagerImpl.h"

StaffManagerImpl::StaffManagerImpl(): staffCount(0), dayCount(0), minOffDays(0) {}

// Set up internal arrays for a new schedule
void StaffManagerImpl::initialize(int staffCount_, int dayCount_, int minOffDays_) {
    staffCount  = staffCount_;
    dayCount    = dayCount_;
    minOffDays  = minOffDays_;

    workDays.assign(staffCount, 0);
    offDays.assign(staffCount, 0);
}

bool StaffManagerImpl::inStaffRange(int staffID) const {
    return staffID >= 0 && staffID < staffCount;
}

void StaffManagerImpl::addWorkDay(int staffID) {
    if (inStaffRange(staffID)) {
        ++workDays[staffID];
    }
}

void StaffManagerImpl::addOffDay(int staffID) {
    if (inStaffRange(staffID)) {
        ++offDays[staffID];
    }
}

int StaffManagerImpl::getWorkDays(int staffID) const {
    if (!inStaffRange(staffID)) return 0;
    return workDays[staffID];
}

int StaffManagerImpl::getOffDays(int staffID) const {
    if (!inStaffRange(staffID)) return 0;
    return offDays[staffID];
}
 
bool StaffManagerImpl::canWork(int staffID, int remainingDays) const {
    if (!inStaffRange(staffID)) return false;  // Ensure staffID is valid

    int workedDays = workDays[staffID];  // Get the current number of worked days
    int maxWorkDays = dayCount - minOffDays;  // The maximum number of workdays this staff member can have

    // Ensure that this staff member does not exceed the max work days
    return (workedDays + remainingDays) <= maxWorkDays;
}
