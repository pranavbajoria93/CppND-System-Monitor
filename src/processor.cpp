#include "processor.h"

#include <unistd.h>

#include <string>
#include <vector>

#include "iostream"
#include "linux_parser.h"

using namespace LinuxParser;

// method to populate private variables used in calculation of CPU utilization
// parameters: tstamp 0 for previous and 1 for current stats
void Processor::PopulateCpuStats(std::vector<std::string> stats, int tstamp) {
  if (tstamp == 1) {
    user = std::stoull(stats[1]);
    nice = std::stoull(stats[2]);
    system = std::stoull(stats[3]);
    idle = std::stoull(stats[4]);
    ioWait = std::stoull(stats[5]);
    irq = std::stoull(stats[6]);
    softIrq = std::stoull(stats[7]);
    steal = std::stoull(stats[8]);
    guest = std::stoull(stats[9]);
    guestNice = std::stoull(stats[10]);
    // as per the htop source code, remove guest time from user time
    user = user - guest;
    nice = nice - guestNice;
  } else {
    prevUser = std::stoull(stats[1]);
    prevNice = std::stoull(stats[2]);
    prevSystem = std::stoull(stats[3]);
    prevIdle = std::stoull(stats[4]);
    prevIoWait = std::stoull(stats[5]);
    prevIrq = std::stoull(stats[6]);
    prevSoftIrq = std::stoull(stats[7]);
    prevSteal = std::stoull(stats[8]);
    prevGuest = std::stoull(stats[9]);
    prevGuestNice = std::stoull(stats[10]);
    // as per the htop source code, remove guest time from user time
    prevUser = prevUser - prevGuest;
    prevNice = prevNice - prevGuestNice;
  }
}

/* Algorithm for calculating CPU utilization referred from
https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
*/
float Processor::Utilization(unsigned int delay) {
  // read the stats from proc/stat twice across the dealy time
  prevCpuStats = LinuxParser::CpuUtilization();
  usleep(delay);
  currCpuStats = LinuxParser::CpuUtilization();

  // populate variables from the stats vector
  PopulateCpuStats(prevCpuStats, 0);
  PopulateCpuStats(currCpuStats, 1);

  prevIdle = prevIdle + prevIoWait;
  idle = idle + ioWait;

  prevNonIdle =
      prevUser + prevNice + prevSystem + prevIrq + prevSoftIrq + prevSteal;
  nonIdle = user + nice + system + irq + softIrq + steal;

  prevTotal = prevIdle + prevNonIdle;
  total = idle + nonIdle;

  totald = total - prevTotal;
  idled = idle - prevIdle;

  CPU_Percentage = float(totald - idled) / float(totald);
  std::cout << totald << ", "<<idled << ", " << CPU_Percentage*100 << "\n";
  return CPU_Percentage;
}