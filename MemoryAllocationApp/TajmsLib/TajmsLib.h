#pragma once
#include "iostream"
#include "time.h"
#include <vector>
#include <string>
#include <chrono>
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
        std::chrono::time_point<std::chrono::high_resolution_clock> timerStartTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> timerEndTime;
        std::string timerName = "";
        // int nrOfThreads = 0; // Detta kanske kan lösa något om flera trådar ska stänga av en timer. fast man kan också bara ge en timer för varje tråd.
        TajmsTimer(unsigned int p_timerId, std::string p_timerName)
        {
            timerId = p_timerId;
            timerName = p_timerName;
            timerStartTime = std::chrono::high_resolution_clock::now();
        }
    };
private:
    long m_totalTimeForProgram;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin; // Kanske kan göra om till unsigned int om det fungerar
    std::chrono::time_point<std::chrono::high_resolution_clock> m_endOfProgram;
    unsigned int nrOfTimers;
    std::vector<TajmsTimer> m_timers;

};