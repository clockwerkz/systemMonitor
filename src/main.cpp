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
  
  // --- system ---
  cout << "Operating System" << std::endl;
  cout << "----------------" << std::endl;
  cout << LinuxParser::OperatingSystem() << std::endl;
  cout << LinuxParser::Kernel() << std::endl;
  long totalJiffies = LinuxParser::Jiffies();
  cout << "Total system jiffies: " << std::to_string(totalJiffies) << std::endl;
  float activeJiffies = ((float)LinuxParser::ActiveJiffies() / (float)totalJiffies) * 100;
  float idleJiffies = ((float)LinuxParser::IdleJiffies() / (float)totalJiffies) * 100;
  int uptime = LinuxParser::UpTime();
  cout << "Pct of active jiffies: " << activeJiffies << std::endl;
  cout << "Pct of idle jiffies: " << idleJiffies<< std::endl;
  cout << "Uptime in seconds: " << uptime << std::endl;
  cout << "Total number of processes: " << LinuxParser::TotalProcesses() << std::endl;
  cout << "Total number of running processes: " << LinuxParser::RunningProcesses() << std::endl; 
  float memoryUtilization = LinuxParser::MemoryUtilization(); 
  cout << "Memory Utilization: " << memoryUtilization << std::endl;
  
  // --- pids ---
  std::vector<int> pids;
  pids = LinuxParser::Pids();
  int index = rand() % pids.size();
  int uid = std::stoi(LinuxParser::Uid(pids[index]));
  std::string userId = LinuxParser::User(uid);
  cout << std::endl;
  cout << "Individual PID" << std::endl;
  cout << "--------------" << std::endl;
  cout << "User of random pid (" << uid <<") in list (" << pids[index] << "): " << userId << std::endl;
  cout << "Active jiffies of selected pid: ";
  cout << LinuxParser::ActiveJiffies(pids[index]) << std::endl;
  cout << "uptime for selected pid: " << LinuxParser::UpTime(pids[index]) << std::endl;
  cout << "Memory usage for selected pid: " << LinuxParser::Ram(pids[index]) << std::endl;
  cout << "Command line: " << LinuxParser::Command(pids[index]) << std::endl;
  cout << std::endl;
  //NCursesDisplay::Display(system);
}