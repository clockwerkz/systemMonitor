#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <filesystem>
#include "linux_parser.h"

//BEGIN REMOVE --
#include <iostream>
using std::cout;
//END REMOVE --

namespace fs = std::filesystem;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, versionText, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> versionText >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  for (auto & entry : fs::directory_iterator(kProcDirectory)){ 
    string entryPath{entry.path().filename()};
    if (fs::is_directory(entry.path())) {
      if (std::all_of(entryPath.begin(), entryPath.end(), isdigit)) {
        int pid = stoi(entryPath);
        pids.push_back(pid);
      }
    } 
  }
  return pids;
}

//Total Physical Memory - (Memory Free + Memory Buffers + Cache Memory) = Result/Total Physical Memory * 100
// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line; 
  string key;
  float value;
  float memTotal, memFree, buffers, cached, memUtilized;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemFree") memFree = value;
      if (key == "MemTotal") memTotal = value;
      if (key == "Buffers") buffers = value;
      if (key == "Cached") cached = value;}
  }
  memUtilized = (memTotal - memFree + buffers + cached) / memTotal * 100;
  return memUtilized;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  float uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()) {
    string line;
    if (std::getline(file, line)) {
      std::istringstream linestream(line);
      string cpu, normal, nice, system, idle, iowait;
      linestream >> cpu >> normal >> nice >> system >> idle >> iowait;
      if (cpu == "cpu") {
        return (stol(normal) + stol(nice) + stol(system) + stol(idle) + stol(iowait));
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  long utime, stime, cutime, cstime;
  std::ifstream file(kProcDirectory + std::to_string(pid) + "/stat");
  if (file.is_open()) {
    string line;
    if (std::getline(file, line)) {
      std::istringstream linestream(line);
      int count = 1;
      string val;
      while (count < 18) {
        linestream >> val;
        if (count == 14) utime = stol(val);
        if (count == 15) stime = stol(val);
        if (count == 16) cutime = stol(val);
        if (count == 17) cstime = stol(val);
        count++;
      }
    }
  }
  return utime + stime + cutime + cstime;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()) {
    string line;
    if (std::getline(file, line)) {
      std::istringstream linestream(line);
      string cpu, normal, nice, system, idle, iowait;
      linestream >> cpu >> normal >> nice >> system >> idle;
      return (stol(normal) + stol(nice) + stol(system));
    }
  }
  return 0;
}


// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()) {
    string line;
    if (std::getline(file, line)) {
      std::istringstream linestream(line);
      string cpu, normal, nice, system, idle, iowait;
      linestream >> cpu >> normal >> nice >> system >> idle >>iowait;
      return (stol(idle) + stol(iowait));
      
    }
  }
  return 0;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }



// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()) {
    string line;
    while (std::getline(file, line)) {
      string category, value;
      std::istringstream linestream(line);
      linestream >> category >> value;
      if (category == "processes") {
        return std::stoi(value);
      }
    }
  }
  return 0;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream file(kProcDirectory + kStatFilename);
  if (file.is_open()) {
    string line;
    while (std::getline(file, line)) {
      string category, value;
      std::istringstream linestream(line);
      linestream >> category >> value;
      if (category == "procs_running") {
        return std::stoi(value);
      }
    }
  }
  return 0;  
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream pidInfo(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  std::string line;
  if (pidInfo.is_open()) {
    while(std::getline(pidInfo, line)) {
      return line;
    }
  }
  return line; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::ifstream pidInfo(kProcDirectory + std::to_string(pid) + "/status");
  std::string line;
  std::string memoryUsage;
  if (pidInfo.is_open()) {
    while(std::getline(pidInfo, line)) {
      std::istringstream lineStream(line);
      std::string process, val;
      lineStream >> process >> val;
      if (process == "VmSize:") {
        return val;
      }
    }
  }
  return string();
}



// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  std::ifstream pidInfo(kProcDirectory + std::to_string(pid) + "/status");
  std::string line;
  std::string uid;
  if (pidInfo.is_open()) {
    while(std::getline(pidInfo, line)) {
      std::istringstream lineStream(line);
      std::string process;
      std::string val;
      lineStream >> process >> val;
      if (process == "Uid:") {
        uid = val;
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int uid) { 
  std::ifstream userLookup(kPasswordPath);
  std::string line;
  std::string user;
  if (userLookup.is_open()) {
    while (std::getline(userLookup, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineStream(line);
      std::string userName;
      int id;
      char spacer;
      lineStream >> userName >> spacer >> id;
      if (id == uid) {
        user = userName;
        return user;
      }
    }
  }  
  return user; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  std::ifstream file(kProcDirectory + std::to_string(pid) + "/stat");
  long uptime = 0;
    if (file.is_open()) {
      string line;
      if (std::getline(file, line)) {
        std::istringstream linestream(line);
        int count = 1;
        string val;
        while (count < 23) {
          linestream >> val;
          if (count == 22) uptime= stol(val) / 100;
          count++;
        }
      }
  }
  return uptime;
}