#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<Process> localProcesses = vector<Process>{};
    std::vector<int> pids;
    pids = LinuxParser::Pids();
    for (int i : pids)
    {
        std::string userId = LinuxParser::User(i); 
        std::string cmd = LinuxParser::Command(pids[i]);
        std::string ram = LinuxParser::Ram(pids[i]);
        long uptime = LinuxParser::UpTime(pids[i]);
        Process process = Process(i, userId, cmd, 0.f, ram, uptime); 
        localProcesses.push_back(process);
    }
    return localProcesses;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return string(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
 }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses();
 }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    //uptime_ = LinuxParser::UpTime();
    //return uptime_;
    return LinuxParser::UpTime();
 }