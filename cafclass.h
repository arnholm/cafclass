#ifndef CAFCLASS_H
#define CAFCLASS_H

#include <vector>
#include <string>
#include <fstream>

class cafclass {
public:
   cafclass(const std::vector<std::string>& namespaces
          , const std::string class_name
           );
   virtual ~cafclass();

   bool success() const { return m_success; }
   std::string  h_name() const { return m_h_name; }
   std::string  cpp_name() const { return m_cpp_name; }

protected:
   void write_copright_text(std::ofstream& out);
   void write_include_protection(std::ofstream& out);
   void write_decl(std::ofstream& out);
   void write_impl(std::ofstream& out);

private:
   bool                     m_success;
   std::vector<std::string> m_namespaces;
   std::string              m_class_name;
   std::string              m_h_name;
   std::ofstream            m_h;
   std::string              m_inc_prot;
   std::ofstream            m_cpp;
   std::string              m_cpp_name;
};

#endif // CAFCLASS_H
