#include<iostream>
#include "ncurses_display.h"
#include "system.h"
// #include "linux_parser.h"

// using namespace LinuxParser;  

int main() {
  System system;
  NCursesDisplay::Display(system);
}