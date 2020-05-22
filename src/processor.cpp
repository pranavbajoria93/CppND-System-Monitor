#include <unistd.h>
#include <string>
#include <vector>

#include "processor.h"
#include "linux_parser.h"

using namespace LinuxParser;

// processor constructor to fill in CPU prevstats as a reference to the first CPU.utilization() call
Processor::Processor(){
  prevCpuStats = LinuxParser::CpuUtilization();
}

/* Algorithm for calculating CPU utilization referred from
https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

The CPU utilization is for the 1 sec time used when refreshing the system monitor display. 
PrevStats are update everytime utilization is called.
*/
float Processor::Utilization() {
  // read the stats from proc/stat twice across the dealy time
  std::vector<std::string> currCpuStats = LinuxParser::CpuUtilization();

  // Idle = Idle + IoWait;
  prevIdle = std::stoull(prevCpuStats[LinuxParser::CPUStates::kIdle_]) +
             std::stoull(prevCpuStats[LinuxParser::CPUStates::kIOwait_]);
  
  currIdle = std::stoull(currCpuStats[LinuxParser::CPUStates::kIdle_]) +
             std::stoull(currCpuStats[LinuxParser::CPUStates::kIOwait_]);

  // nonIdle = user + nice + system + irq + softIrq + steal
  prevNonIdle = std::stoull(prevCpuStats[LinuxParser::CPUStates::kUser_]) +
                std::stoull(prevCpuStats[LinuxParser::CPUStates::kNice_]) +
                std::stoull(prevCpuStats[LinuxParser::CPUStates::kSystem_]) +
                std::stoull(prevCpuStats[LinuxParser::CPUStates::kIRQ_]) +
                std::stoull(prevCpuStats[LinuxParser::CPUStates::kSoftIRQ_]) +
                std::stoull(prevCpuStats[LinuxParser::CPUStates::kSteal_]);

  currNonIdle = std::stoull(currCpuStats[LinuxParser::CPUStates::kUser_]) +
                std::stoull(currCpuStats[LinuxParser::CPUStates::kNice_]) +
                std::stoull(currCpuStats[LinuxParser::CPUStates::kSystem_]) +
                std::stoull(currCpuStats[LinuxParser::CPUStates::kIRQ_]) +
                std::stoull(currCpuStats[LinuxParser::CPUStates::kSoftIRQ_]) +
                std::stoull(currCpuStats[LinuxParser::CPUStates::kSteal_]);

  prevTotal = prevIdle + prevNonIdle;
  currTotal = currIdle + currNonIdle;

  totald = currTotal - prevTotal;
  idled = currIdle - prevIdle;

  //sanity check to avoid xero denominator
  if(totald==0) totald=1;

  CPU_Percentage = float(totald - idled) / float(totald);
  prevCpuStats = currCpuStats;
  return CPU_Percentage;
}