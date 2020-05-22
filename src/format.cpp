#include <string>

#include "format.h"

using std::string;
using std::to_string;

// helper function for converting seconds to HH:MM:SS format
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
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