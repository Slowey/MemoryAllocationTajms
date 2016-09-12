#include "TajmsLib.h"
#include <ctime>

//http://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
// kolla chrono grejen längre ner för clock kollade cpu clocken o inte actual time tydligen.


// prova denna också http://stackoverflow.com/questions/2962785/c-using-clock-to-measure-time-in-multi-threaded-programs/2962914#2962914


//Testar om jag är användaren!

// Denna ska tydligen vara trådssäker http://codereview.stackexchange.com/questions/40915/simple-multithread-timer

void TajmsLib::InitTajmsLib()
{
    //start the program timer.
    unsigned int begin = clock();

    unsigned int end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
}
void TajmsLib::ShutdownTajmsLib()
{
    // Stop the timer and write to textfiles.
    unsigned int end = clock();
}
void TajmsLib::UpdateTimer()
{

}
int TajmsLib::Test()
{
    return 31;
}
int TajmsLib::StartTimer()
{
    return 0;
}
void TajmsLib::StopTimer(int p_id)
{

}

