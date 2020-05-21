#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

#include "linux_parser.h"

class Processor {
 public:
  float Utilization(unsigned int delay);  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  std::vector<std::string> prevCpuStats;
  std::vector<std::string> currCpuStats;
  unsigned long long int prevUser, prevNice, prevSystem, prevIdle;
  unsigned long long int prevIoWait, prevIrq, prevSoftIrq, prevSteal, prevGuest, prevGuestNice;
  unsigned long long int user, nice, system, idle;
  unsigned long long int ioWait, irq, softIrq, steal, guest, guestNice;
  unsigned long long int systemalltime, idlealltime, totaltime, virtalltime;
  unsigned long long int prevNonIdle, nonIdle, prevTotal, total, totald, idled;
  float CPU_Percentage;
  void PopulateCpuStats(std::vector<std::string> stats, int tstamp);
};

#endif