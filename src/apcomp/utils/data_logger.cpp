#include <apcomp/utils/data_logger.hpp>
#include <apcomp/apcomp.hpp>

#include <fstream>
#include <iostream>

namespace apcomp 
{

DataLogger DataLogger::m_instance;

DataLogger::DataLogger()
  : m_at_block_start(true),
    m_rank(0)
{
  m_blocks.push(Block(0));
  m_key_counters.push(std::map<std::string,int>());
}

DataLogger::~DataLogger()
{
#ifdef APCOMP_ENABLE_LOGGING
  write_log();
#endif
  m_stream.str("");
}

DataLogger*
DataLogger::get_instance()
{
  return &DataLogger::m_instance;
}

DataLogger::Block&
DataLogger::current_block()
{
  return m_blocks.top();
}

void
DataLogger::set_rank(const int &rank)
{
  m_rank = rank;
}

void
DataLogger::write_indent()
{
  int indent = current_block().Indent;
  bool listStart = current_block().AtListItemStart;

  if (listStart)
  {
    --indent;
  }

  for (int i = 0; i < indent; ++i)
  {
    m_stream << "  ";
  }

  if (listStart)
  {
    m_stream << "- ";
    current_block().AtListItemStart = false;
  }
}

void
DataLogger::write_log()
{
  std::stringstream log_name;
  std::string log_prefix = "apcomp_data";
  if(const char* log_p = std::getenv("APCOMP_LOG_PREFIX"))
  {
    log_prefix = std::string(log_p);
  }
  log_name<<log_prefix<<"_"<<m_rank;
  log_name<<".yaml";

  std::ofstream stream;
  stream.open(log_name.str().c_str(), std::ofstream::app);
  if(!stream.is_open())
  {
    std::cerr<<"Warning: could not open the apcomp data log file\n";
    return;
  }
  stream<<m_stream.str();
  stream.close();
  m_stream.str("");
}

void
DataLogger::open(const std::string &entryName)
{
    write_indent();
    // ensure that we have unique keys for valid yaml
    int key_count = m_key_counters.top()[entryName]++;
    if(key_count != 0)
    {
      m_stream<<entryName<<"_"<<key_count<<":"<<"\n";
    }
    else
    {
      m_stream<<entryName<<":"<<"\n";
    }

    int indent = this->current_block().Indent;
    m_blocks.push(Block(indent+1));
    m_key_counters.push(std::map<std::string,int>());

    m_timers.push(Timer());
    m_at_block_start = true;

}

void
DataLogger::close()
{
  write_indent();
  this->m_stream<<"time: "<<m_timers.top().elapsed()<<"\n";
  m_timers.pop();
  m_blocks.pop();
  m_key_counters.pop();
  m_at_block_start = false;
}

} // namespace apcomp 
