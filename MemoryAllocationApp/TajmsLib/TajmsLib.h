#pragma once
#include "iostream"
#include "time.h"
#include <vector>
#include <string>
// Call initTajmslib to start the counter for the whole program and make sure to use ShutdownTajmsLib before you close the program to make sure you get every timer.
class TajmsLib
{
public:
    void InitTajmsLib();
    void ShutdownTajmsLib(std::string &p_fileName);
    void UpdateTimer();
    float Test();
    int StartTimer(std::string p_timerName);// Saves the start time of the timer and returns an id for the timer.
    void StopTimer(int p_id);
    struct TajmsTimer
    {
        unsigned int timerId = 0;
        long timerStartTime = 0;
        long timerEndTime = 0;
        std::string timerName = "";
        // int nrOfThreads = 0; // Detta kanske kan l�sa n�got om flera tr�dar ska st�nga av en timer. fast man kan ocks� bara ge en timer f�r varje tr�d.
        TajmsTimer(long p_timerStartTime, unsigned int p_timerId, std::string p_timerName)
        {
            timerStartTime = p_timerStartTime;
            timerId = p_timerId;
            timerName = p_timerName;
        }
    };
private:
    long m_totalTimeForProgram;
    long m_begin; // Kanske kan g�ra om till unsigned int om det fungerar
    long m_endOfProgram;
    unsigned int nrOfTimers;
    std::vector<TajmsTimer> m_timers;

};