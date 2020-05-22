#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

#include "linux_parser.h"

class Processor {
 public:
  Processor();  // constructor to initialize previous stats
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  std::vector<std::string> prevCpuStats;
  unsigned long long int prevIdle, currIdle, prevNonIdle, currNonIdle,
      prevTotal, currTotal, totald, idled;
  float CPU_Percentage;
  void PopulateCpuStats(std::vector<std::string> stats, int tstamp);
};

#endif