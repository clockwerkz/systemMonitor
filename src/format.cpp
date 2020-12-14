#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    std::string timeFormat;
    int sec = seconds % 60;
    int minutes = seconds / 60;
    int min = minutes % 60;
    int hours = minutes / 60;
    timeFormat +=  (hours < 10) ? "0" + std::to_string(hours) : std::to_string(hours);
    timeFormat += ":";
    timeFormat += (min < 10) ? "0" + std::to_string(min) : std::to_string(min);
    timeFormat += ":";
    timeFormat += (sec < 10) ? "0" + std::to_string(sec) : std::to_string(sec);
    return timeFormat;
}