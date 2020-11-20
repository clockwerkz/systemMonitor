#include <iostream>
#include <string>
#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <vector>
using std::cout;

int main() {
  System system;
  //Testing Parsing of files:
  cout << LinuxParser::OperatingSystem() << std::endl;
  cout << LinuxParser::Kernel() << std::endl;
  LinuxParser::MemoryUtilization(); 
  std::vector<int> pids;
  pids = LinuxParser::Pids();
  cout << "Total Processes: " << pids.size() << std::endl;
  cout << "Uptime in seconds: " << LinuxParser::UpTime() << std::endl;
  //NCursesDisplay::Display(system);
}