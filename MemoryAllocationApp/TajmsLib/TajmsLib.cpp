#include "TajmsLib.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

//http://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
// kolla chrono grejen längre ner för clock kollade cpu clocken o inte actual time tydligen.


// prova denna också http://stackoverflow.com/questions/2962785/c-using-clock-to-measure-time-in-multi-threaded-programs/2962914#2962914


//Testar om jag är användaren!

// Denna ska tydligen vara trådssäker http://codereview.stackexchange.com/questions/40915/simple-multithread-timer

void TajmsLib::InitTajmsLib()
{
    //start the program timer.
    m_begin = clock();
    _mkdir("Test timers");

}
void TajmsLib::ShutdownTajmsLib(std::string &p_fileName)
{
    // Stop the timer and write to textfiles.
    // unsigned int end = clock();
    m_totalTimeForProgram = clock() - m_begin;
    time_t  timev = time(0);
    time(&timev);
    struct tm now;
    localtime_s(&now, &timev);
    int timeYear = now.tm_year + 1900;
    std::string yearString = std::to_string(timeYear);

    std::ofstream myfile;
    myfile.open("Test timers/" + p_fileName + ".txt", std::ios::app);

    if (myfile.is_open())
    {
        if (m_timers.size())
        {
            double tempForOutput = (double)(m_timers[0].timerEndTime - m_timers[0].timerStartTime) / (double)CLOCKS_PER_SEC;
            myfile << tempForOutput << std::endl;
        }
    }

    myfile.close();
}
void TajmsLib::UpdateTimer()
{

}
float TajmsLib::Test()
{
    //float end = clock();
    //float elapsed_secs = double(end - m_begin) / CLOCKS_PER_SEC;
    //return elapsed_secs;
    return 0;
}
int TajmsLib::StartTimer(std::string p_timerName)
{
    m_timers.push_back(TajmsTimer(clock(), nrOfTimers, p_timerName));
    ++nrOfTimers;
    return nrOfTimers - 1;
}
void TajmsLib::StopTimer(int p_id)
{
    m_timers[p_id].timerEndTime = clock();
}

