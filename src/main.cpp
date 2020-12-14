#include <iostream>
#include <string>
#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <vector>
#include <cstdlib>
#include "format.h"
using std::cout;

int main() {
  System system;
  //Testing Parsing of files:
  srand((unsigned) time(0));
  cout << "Operating System" << std::endl;
  cout << "----------------" << std::endl;
  cout << LinuxParser::OperatingSystem() << std::endl;
  cout << LinuxParser::Kernel() << std::endl;
  long totalJiffies = LinuxParser::Jiffies();
  cout << "Number of jiffies for the system: " << std::to_string(totalJiffies) << std::endl;
  LinuxParser::MemoryUtilization(); 
  std::vector<int> pids;
  pids = LinuxParser::Pids();
  int index = rand() % pids.size();
  int uid = std::stoi(LinuxParser::Uid(pids[index]));
  std::string userId = LinuxParser::User(uid);
  cout << std::endl;
  cout << "Individual PID" << std::endl;
  cout << "--------------" << std::endl;
  cout << "User of random pid (" << uid <<") in list (" << pids[index] << "): " << userId << std::endl;
  cout << "Command line: " << LinuxParser::Command(pids[index]) << std::endl;
  cout << "Uptime in seconds: " << LinuxParser::UpTime() << std::endl;
  cout << std::endl;
  cout << "Format Time" << std::endl;
  cout << "-----------" << std::endl;
  cout << "Time format test for 22:30:45- " << Format::ElapsedTime(81045) << std::endl;
  cout << "Time format test for 05:09:30- " << Format::ElapsedTime(18570) << std::endl;
  cout << "Time format test for 00:00:30- " << Format::ElapsedTime(30) << std::endl;
  //NCursesDisplay::Display(system);
}