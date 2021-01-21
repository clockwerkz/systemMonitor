#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, std::string user, std::string cmd, float cpuUtilization, std::string ram, long int uptime)
  :_pid(pid), _user(user), _cmd(cmd), _cpuUtilization(cpuUtilization), _ram(ram), _uptime(uptime){}
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command() const;             // TODO: See src/process.cpp
  float CpuUtilization() const;            // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
    int _pid=0;
    std::string _user="";
    std::string _cmd="";
    float _cpuUtilization=0.f;
    std::string _ram="";
    long int _uptime=0;
};

#endif