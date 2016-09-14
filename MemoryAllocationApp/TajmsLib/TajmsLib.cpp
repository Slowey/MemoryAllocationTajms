#include "TajmsLib.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

//http://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
// kolla chrono grejen längre ner för clock kollade cpu clocken o inte actual time tydligen.


// prova denna också http://stackoverflow.com/questions/2962785/c-using-clock-to-measure-time-in-multi-threaded-programs/2962914#2962914


//Testar om jag är användaren!

// Denna ska tydligen vara trådssäker http://codereview.stackexchange.com/questions/40915/simple-multithread-timer

void TajmsLib::InitTajmsLib()
{
    //start the program timer.
    m_begin = clock();
}
void TajmsLib::ShutdownTajmsLib()
{
    // Stop the timer and write to textfiles.
    // unsigned int end = clock();
    time_t  timev = time(0);
    time(&timev);
    struct tm now;
    localtime_s(&now, &timev);
    int timeYear = now.tm_year + 1900;
    std::string yearString = std::to_string(timeYear);

    int timeMonth = now.tm_mon + 1;
    std::string monthString = std::to_string(timeMonth);

    int timeDay = now.tm_mday;
    std::string dayString = std::to_string(timeDay);

    int timeHour = now.tm_hour;
    std::string hourString = std::to_string(timeHour);

    int timeMinute = now.tm_min;
    std::string minuteString = std::to_string(timeMinute);

    int timeSecond = now.tm_sec;
    std::string secondString = std::to_string(timeSecond);

    std::ofstream myfile;
    myfile.open(secondString + "_" + minuteString + "_" + hourString + "_" + dayString + "_" + monthString + "_" + yearString + ".txt");
    myfile << timeSecond + timeMinute + timeHour + timeDay + timeMonth + timeYear;

    myfile.close();
}
void TajmsLib::UpdateTimer()
{

}
float TajmsLib::Test()
{
    float end = clock();
    float elapsed_secs = double(end - m_begin) / CLOCKS_PER_SEC;
    return elapsed_secs;
}
int TajmsLib::StartTimer(std::string p_timerName)
{
    int timerId = 0; // Ändra tvåan till en funktion som fixar detta
    m_timers.push_back(TajmsTimer(clock(), timerId, p_timerName));

    return timerId;
}
void TajmsLib::StopTimer(int p_id)
{
    m_timers[p_id].timerEndTime = clock();
}

