#ifndef STAFFMANAGERIMPL_H
#define STAFFMANAGERIMPL_H

#include "IStaffManager.h"
#include <vector>
using namespace std;

class StaffManagerImpl : public IStaffManager {
private:
    int staffCount;          
    int dayCount;            
    int minOffDays;         

    vector <int> workDays;    
    vector <int> offDays;   

    bool inStaffRange(int staffID) const;  

public:
    StaffManagerImpl();

    void initialize(int staffCount, int dayCount, int minOffDays) override;
    void addWorkDay(int staffID) override;
    void addOffDay(int staffID) override;
    int getWorkDays(int staffID) const override;
    int getOffDays(int staffID) const override;
    bool canWork(int staffID, int remainingDays) const override;
};

#endif // STAFFMANAGERIMPL_H
