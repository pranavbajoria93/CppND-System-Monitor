#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using namespace LinuxParser;

// constructor
Process::Process(int pid):pid_(pid){
    procUpTime = LinuxParser::UpTime(pid_);
    ram = std::stoi(LinuxParser::Ram(pid_));
    cpuUtilization = CpuUtilization();
}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    long sysUpTime = LinuxParser::UpTime();
    // get active jiffies and divide by sys frequency to get time in secs
    long totalActiveTime = LinuxParser::ActiveJiffies(pid_)/ sysconf(_SC_CLK_TCK);
    long time_elapsed = sysUpTime - procUpTime;
    return float(totalActiveTime)/float(time_elapsed);
    }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return to_string(ram); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return procUpTime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return cpuUtilization>a.cpuUtilization; }