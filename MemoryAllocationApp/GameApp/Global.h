#pragma once
#include <thread>

extern std::thread::id g_mainThread;

static bool IsMainThread()
{
    return g_mainThread == std::this_thread::get_id();
}