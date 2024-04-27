#pragma once

#include <includes.hpp>

namespace PNT
{
    struct timeData
    {
        std::string second, minute, hour, day, month, year;
    };

    // Fills a structure with time data.
    void calculateTime(timeData *inputTime)
    {
        time_t currentTime = std::time(0);
        std::tm* now = std::localtime(&currentTime);
        inputTime->second = std::to_string(now->tm_sec);
        inputTime->minute = std::to_string(now->tm_min);
        inputTime->hour = std::to_string(now->tm_hour);
        inputTime->day = std::to_string(now->tm_mday);
        inputTime->month = std::to_string(now->tm_mon + 1);
        inputTime->year = std::to_string(now->tm_year + 1900);
    }
}
