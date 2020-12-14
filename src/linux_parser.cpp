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
  cout << "Memory Utilization: " << memUtilized << std::endl;
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
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

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
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

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
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }