#include "cafclass.h"
#include <sstream>
#include <algorithm>
#include <filesystem>
namespace fs = std::filesystem;

cafclass::cafclass(const std::vector<std::string>& namespaces
                 , const std::string class_name
                  )
: m_success(false)
, m_namespaces(namespaces)
, m_class_name(class_name)
{
   m_h_name   = class_name+".h";
   m_cpp_name = class_name+".cpp";

   if(std::filesystem::exists(m_h_name)) throw std::runtime_error("File already exists: " + m_h_name);
   if(std::filesystem::exists(m_cpp_name)) throw std::runtime_error("File already exists: " + m_cpp_name);


   m_h.open(m_h_name);
   if(!m_h.is_open()) throw std::runtime_error("File could not be opened: " + m_h_name);

   m_cpp.open(m_cpp_name);
   if(!m_cpp.is_open()) throw std::runtime_error("File could not be opened: " + m_cpp_name);

   write_copright_text(m_h);
   write_include_protection(m_h);
   write_decl(m_h);

   write_copright_text(m_cpp);
   write_impl(m_cpp);

   m_success = true;
}

void cafclass::write_copright_text(std::ofstream& out)
{
   out << "// KONGSBERG PROPRIETARY: This document and its accompanying elements," << std::endl;
   out << "// contain KONGSBERG information which is proprietary and confidential." << std::endl;
   out << "// Any disclosure, copying, distribution or use is prohibited if not otherwise explicitly agreed with KONGSBERG in writing." << std::endl;
   out << "// Any authorized reproduction, in whole or in part, must include this legend." << std::endl;
   out << "// (c) 2021 KONGSBERG - All rights reserved" << std::endl;
}

void cafclass::write_include_protection(std::ofstream& out)
{
   std::stringstream sout;

   sout << "_";
   for(auto ns : m_namespaces) sout << '_' << ns;
   sout << '_' << m_class_name;
   sout << "_H_";

   m_inc_prot = sout.str();
   std::transform(m_inc_prot.begin(),m_inc_prot.end(),m_inc_prot.begin(),::toupper);

   out << std::endl;
   out << "#ifndef " << m_inc_prot << std::endl;
   out << "#define " << m_inc_prot << std::endl;
}

void cafclass::write_decl(std::ofstream& out)
{
   out << std::endl;

   for(auto ns : m_namespaces){
      out << "namespace " << ns << std::endl;
      out << "{ "               << std::endl;
   }

   out << std::endl;
   out << "class " << m_class_name << std::endl;
   out << "{ "       << std::endl;
   out << "public: " << std::endl;
   out << "    " << m_class_name << "();" << std::endl;
   out << "}; "      << std::endl;

   out << std::endl;
   for(auto i=m_namespaces.rbegin(); i!=m_namespaces.rend(); i++) {
      out << "} // namespace " << *i   << std::endl;
   }

}

void cafclass::write_impl(std::ofstream& out)
{
   out << std::endl;
   out << "#include \"" << m_class_name << ".h\"" << std::endl;

   out << std::endl;
   for(auto ns : m_namespaces){
      out << "namespace " << ns << std::endl;
      out << "{ "               << std::endl;
   }

   out << std::endl;
   out << m_class_name<< "::" << m_class_name << "()" << std::endl;
   out << "{ "       << std::endl;
   out << "} "      << std::endl;

   out << std::endl;
   for(auto i=m_namespaces.rbegin(); i!=m_namespaces.rend(); i++) {
      out << "} // namespace " << *i   << std::endl;
   }

}

cafclass::~cafclass()
{
   m_h << std::endl;
   m_h << "#endif // "<< m_inc_prot << std::endl;
   m_h.close();

   m_cpp.close();
}
