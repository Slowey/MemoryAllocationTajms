#pragma once
/**
Struct to set parameters when creating a window*/
struct WindowParams
{
    int argc;
    char* argv;
    const char* windowName;
    float winSizeX;
    float winSizeY;
    float winPosX;
    float winPosY;
};