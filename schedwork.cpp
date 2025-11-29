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
bool fill_spot(
    AvailabilityMatrix& avail, 
    const size_t dailyNeed, 
    const size_t maxShifts,
    DailySchedule& sched,
    size_t row,
    size_t col,
    vector<size_t>& workerDayCount);

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

    AvailabilityMatrix availability = avail;

    //Helps us keep track of how many days each workers has been assigned to 
    vector<size_t> workerDayCount(avail[0].size(), 0);

    //Setting up sched matrix, filling it up with INVALID_ID
    for(size_t i = 0; i < avail.size(); i++){
        vector<Worker_T> row(dailyNeed, INVALID_ID);
        sched.push_back(row);
    }
    
    bool result = fill_spot(availability, dailyNeed, maxShifts, sched, 0, 0, workerDayCount);

    if(!result){
        return false;
    }
    else{
        return true;
    }
}

bool fill_spot(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    size_t day_n,
    size_t worker,
    vector<size_t>& workerDayCount){

    if(day_n == avail.size()){
    //Hit the end of the recursion: all matrix should be filled up
        return true;
    }

    else{
        for(size_t i = 0; i < avail[day_n].size(); i++){
        //Loop through the list of available workers
            if(avail[day_n][i]){
                avail[day_n][i] = 0;
                sched[day_n][worker] = i;
                workerDayCount[i]++;

                //Calculate values for the next recursive call
                size_t nextDay = day_n;
                size_t nextWorker = worker + 1;
                if(nextWorker == dailyNeed){
                    nextDay += 1;
                    nextWorker = 0;
                }

                //Recursive call is the current matrix is valid
                if(workerDayCount[i] <= maxShifts){
                    if(fill_spot(avail, dailyNeed, maxShifts, sched, nextDay, nextWorker, workerDayCount)){
                        return true;
                    }
                }

                //Backtrack to the original state: next option
                avail[day_n][i] = 1;
                sched[day_n][worker] = INVALID_ID;
                workerDayCount[i]--;
            }
        }
        return false;
    }
}

