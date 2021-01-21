#include <iostream>
#include <string>
#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include "process.h"
#include <vector>
#include <cstdlib>
#include <stdio.h> //TODO: delete when no longer testing and clear printf cmds
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
  //float activeJiffies = ((float)LinuxParser::ActiveJiffies() / (float)totalJiffies) * 100;
  //float idleJiffies = ((float)LinuxParser::IdleJiffies() / (float)totalJiffies) * 100;
  int uptime = LinuxParser::UpTime();
  //cout << "Pct of active jiffies: " << activeJiffies << std::endl;
  //cout << "Pct of idle jiffies: " << idleJiffies<< std::endl;
  cout << "Uptime in seconds: " << uptime << std::endl;
  cout << "Total number of processes: " << LinuxParser::TotalProcesses() << std::endl;
  cout << "Total number of running processes: " << LinuxParser::RunningProcesses() << std::endl; 
  float memoryUtilization = LinuxParser::MemoryUtilization(); 
  cout << "Memory Utilization: " << memoryUtilization << std::endl;
  
  // --- pids ---
  std::vector<int> pids;
  pids = LinuxParser::Pids();
  int index = rand() % pids.size();
  int index2 = index;
  while (index2 == index) {
    index2 = rand() % pids.size();
  }
  std::vector<int> pidsVal{index, index2};
  //Process(int pid, std::string user, std::string cmd, float cpuUtilization, std::string ram, long int uptime)
  for (int i : pidsVal)
  {
    std::string userId = LinuxParser::User(i); 
    std::string cmd = LinuxParser::Command(pids[i]);
    std::string ram = LinuxParser::Ram(pids[i]);
    long uptime = LinuxParser::UpTime(pids[i]);
    Process *process = new Process(i, userId, cmd, 0.f, ram, uptime); 
    printf("Process id: %i, user: %s\n", process->Pid(), process->User().c_str());
  }
  
  //NCursesDisplay::Display(system);
}