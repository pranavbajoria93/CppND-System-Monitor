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

// constructor populates feilds that can be used to compare processes while sorting
Process::Process(int pid):pid_(pid){
    procUpTime = LinuxParser::UpTime(pid_);
    cpuUtilization = CpuUtilization();
}

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() { 
    long sysUpTime = LinuxParser::UpTime();
    // get active jiffies and divide by sys frequency to get time in secs
    long totalActiveTime = LinuxParser::ActiveJiffies(pid_)/ sysconf(_SC_CLK_TCK);
    long time_elapsed = sysUpTime - procUpTime;
    return float(totalActiveTime)/float(time_elapsed);
    }

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(pid_); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return procUpTime; }

// Overload the "less than" comparison operator for Process objects
// based on highest CPU utilization first
bool Process::operator<(Process const& a) const { 
    return cpuUtilization>a.cpuUtilization; }