#include <iostream>
#include <string>
#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"

using std::cout;

int main() {
  System system;
  //Testing Parsing of files:
  cout << LinuxParser::OperatingSystem() << std::endl;
  cout << LinuxParser::Kernel() << std::endl;
  LinuxParser::MemoryUtilization(); 
  //NCursesDisplay::Display(system);
}