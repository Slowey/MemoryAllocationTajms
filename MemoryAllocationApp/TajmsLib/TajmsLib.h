#pragma once
#include "iostream"
#include "time.h"
#include <vector>
// Call initTajmslib to start the counter for the whole program and make sure to use ShutdownTajmsLib before you close the program to make sure you get every timer.
class TajmsLib
{
public:
    void InitTajmsLib();
    void ShutdownTajmsLib();
    void UpdateTimer();
    float Test();
    int StartTimer(std::string p_timerName);// Saves the start time of the timer and returns an id for the timer.
    void StopTimer(int p_id);
    struct TajmsTimer
    {
        unsigned int timerId = 0;
        float timerStartTime = 0;
        float timerEndTime = 0;
        std::string timerName = "";
        // int nrOfThreads = 0; // Detta kanske kan lösa något om flera trådar ska stänga av en timer. fast man kan också bara ge en timer för varje tråd.
        TajmsTimer(float p_timerStartTime, unsigned int p_timerId, std::string p_timerName)
        {
            timerStartTime = p_timerStartTime;
            timerId = p_timerId;
            timerName = p_timerName;
        }
    };
private:
    float m_totalTimeForProgram;
    float m_begin; // Kanske kan göra om till unsigned int om det fungerar
    float m_endOfProgram;
    std::vector<TajmsTimer> m_timers;

};