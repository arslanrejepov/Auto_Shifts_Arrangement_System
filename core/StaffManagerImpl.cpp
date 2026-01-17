#include "StaffManagerImpl.h"

StaffManagerImpl::StaffManagerImpl()
    : staffCount(0), dayCount(0), minOffDays(0) {}

void StaffManagerImpl::initialize(int staffCount, int dayCount, int minOffDays) {
    this->staffCount = staffCount;
    this->dayCount   = dayCount;
    this->minOffDays = minOffDays;

    workDays.assign(staffCount, 0);
    offDays.assign(staffCount, 0);
}

bool StaffManagerImpl::inStaffRange(int staffID) const {
    return staffID >= 0 && staffID < staffCount;
}

void StaffManagerImpl::addWorkDay(int staffID) {
    if (inStaffRange(staffID))
        ++workDays[staffID];
}

void StaffManagerImpl::addOffDay(int staffID) {
    if (inStaffRange(staffID))
        ++offDays[staffID];
}

void StaffManagerImpl::removeWorkDay(int staffID) {
    if (inStaffRange(staffID) && workDays[staffID] > 0)
        --workDays[staffID];
}

void StaffManagerImpl::removeOffDay(int staffID) {
    if (inStaffRange(staffID) && offDays[staffID] > 0)
        --offDays[staffID];
}

int StaffManagerImpl::getWorkDays(int staffID) const {
    return inStaffRange(staffID) ? workDays[staffID] : 0;
}

int StaffManagerImpl::getOffDays(int staffID) const {
    return inStaffRange(staffID) ? offDays[staffID] : 0;
}

bool StaffManagerImpl::canWork(int staffID) const {
    if (!inStaffRange(staffID)) return false;
    return workDays[staffID] < (dayCount - minOffDays);
}

double StaffManagerImpl::staffSalary(int staffID, double rate) const {
    if (!inStaffRange(staffID)) return 0.0;
    return workDays[staffID] * rate;
}
