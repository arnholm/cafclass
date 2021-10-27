#include <iostream>
using namespace std;

#include "cmdparser.hpp"
#include "cafclass.h"

int main(int argc, char **argv)
{
   // https://github.com/FlorianRappl/CmdParser

   cli::Parser parser(argc, argv);
   parser.set_general_help_text("cafclass V1.0, c++ class generator");
   parser.set_required<std::string>("c", "classname","class name");
   parser.set_optional<std::vector<std::string>>("n", "namespace",std::vector<std::string>(),"namespace name list, e.g. caf core components");
   parser.run_and_exit_if_error();

   auto classname = parser.get<std::string>("c");
   auto nsvec     = parser.get<std::vector<std::string>>("n");

   for(auto ns : nsvec) {
      cout << "namespace: " << ns << std::endl;
   }
   cout << "C++ class: " << classname << std::endl;

   try {
      cafclass cls(nsvec,classname);
      if(cls.success()) {
         cout << "C++ header        : " << cls.h_name() << std::endl;
         cout << "C++ implementation: " << cls.cpp_name() << std::endl;
      }
   }
   catch(std::exception& ex) {
      std::cout << "*** ERROR: " << ex.what() << std::endl;
      return 1;
   }

   return 0;
}


