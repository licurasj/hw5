#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    AvailabilityMatrix& avail,
    DailySchedule& sched,
    size_t numDays, 
    size_t numWorker,
    size_t numMaxShift,
    size_t numNeeded,
    size_t row,size_t col,
    vector<size_t>& vM
);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t numDays = avail.size();
    size_t numWorker = avail[0].size();
    vector<size_t> vM(numWorker,0);
    AvailabilityMatrix availCpy = avail;

    for(size_t i =0; i<numDays;i++){
        vector<Worker_T> temp;
        sched.push_back(temp);
    }
    return scheduleHelper(
        availCpy, sched,
        numDays, numWorker, maxShifts, dailyNeed,
        0, 0, vM
    );


}

bool scheduleHelper(
    AvailabilityMatrix& avail,
    DailySchedule& sched,
    size_t numDays, 
    size_t numWorker,
    size_t numMaxShift,
    size_t numNeeded,
    size_t row,size_t col,
    vector<size_t>& vM
)
{
    if(row==numDays){
        return true;
    }
    if(col==numNeeded){
        return scheduleHelper(
            avail, sched,
            numDays, numWorker, numMaxShift, numNeeded,
            row+1, 0, vM
        );
    }
    

    for(size_t i=0; i<numWorker;i++){ //iterate through all workers
        if (avail[row][i]==1) // if worker available
        {   
            
            if( vM[i]<numMaxShift){
                vM[i]++;
                avail[row][i]=0;
                sched[row].push_back(i);

                if( scheduleHelper(
                    avail, sched,
                    numDays, numWorker, numMaxShift, numNeeded,
                    row, col+1, vM))
                {
                    return true;
                }
                avail[row][i]=1;
                vM[i]--;
                sched[row].pop_back();
            }
            
        }   
    }
    
    return false;
}