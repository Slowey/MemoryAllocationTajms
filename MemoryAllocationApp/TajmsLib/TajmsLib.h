#pragma once
#include "iostream"
#include "time.h"

class TajmsLib
{
public:
    void InitTajmsLib();
    void ShutdownTajmsLib();
    void UpdateTimer();
    int Test();
    int StartTimer();
    void StopTimer(int p_id);
    struct TajmsTimer
    {
        float timerTime = 0;
        unsigned int timerId = 0;
        std::string timerName = "";
    };
private:
    float totalTimeForProgram;

};