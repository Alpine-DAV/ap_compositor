#ifndef APCOMP_DATA_LOGGER_HPP
#define APCOMP_DATA_LOGGER_HPP

#include <apcomp/utils/yaml_writer.hpp>
#include <apcomp/utils/timer.hpp>

#include <fstream>
#include <map>
#include <stack>

namespace apcomp 
{

class DataLogger
{
public:
  struct Block
  {
    int Indent;
    bool IsList;
    bool AtListItemStart;

    Block(int indent)
      : Indent(indent), IsList(false), AtListItemStart(false)
    {  }
  };

  ~DataLogger();
  static DataLogger *get_instance();
  void open(const std::string &entryName);
  void close();

  template<typename T>
  void add_entry(const std::string key, const T &value)
  {
    write_indent();
    this->m_stream << key << ": " << value <<"\n";
    m_at_block_start = false;
  }

  void write_log();
  void set_rank(const int &rank);
  std::stringstream& get_stream() { return m_stream; }
protected:
  DataLogger();
  DataLogger(DataLogger const &);

  void write_indent();
  DataLogger::Block& current_block();
  std::stringstream m_stream;
  static class DataLogger m_instance;
  std::stack<Block> m_blocks;
  std::stack<Timer> m_timers;
  std::stack<std::map<std::string,int>> m_key_counters;
  bool m_at_block_start;
  int m_rank;
};

} // namspace apcomp

#ifdef APCOMP_ENABLE_LOGGING

#define APCOMP_LOG_OPEN(name) ::apcomp::DataLogger::get_instance()->open(name);
#define APCOMP_LOG_CLOSE() ::apcomp::DataLogger::get_instance()->close();
#define APCOMP_LOG_ENTRY(key,value) ::apcomp::DataLogger::get_instance()->add_entry(key,value);
#define APCOMP_LOG_VALUE(value) ::apcomp::DataLogger::get_instance()->add_value(value);
#define APCOMP_LOG_WRITE() ::apcomp::DataLogger::get_instance()->write_log();

#else

#define APCOMP_LOG_OPEN(name)
#define APCOMP_LOG_CLOSE()
#define APCOMP_LOG_ENTRY(key,value)
#define APCOMP_LOG_VALUE(value)
#define APCOMP_LOG_WRITE()
#endif

#endif
