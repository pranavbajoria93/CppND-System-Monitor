#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    string elapsed{""};
    int secs, mins, hours;
    secs = seconds%60;
    seconds = seconds/60;
    mins = seconds%60;
    seconds = seconds/60;
    hours = seconds;
    elapsed=to_string(hours)+":"+to_string(mins)+":"+to_string(secs);
    return elapsed; }