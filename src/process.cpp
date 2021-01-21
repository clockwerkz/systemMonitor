#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() 
{ 
    return _pid; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const 
{ 
    return _cpuUtilization; 
}

string Process::Command() const
{ 
    return _cmd; 
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
    return _ram; 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{ 
    return _user; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{ 
    return _uptime; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{ 
    return _cpuUtilization > a.CpuUtilization();
}