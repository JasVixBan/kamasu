#ifndef RESOPHONIC_KAMASU_LOGGING_HPP_INCLUDED
#define RESOPHONIC_KAMASU_LOGGING_HPP_INCLUDED

#include <stdexcept>
#include <fstream>
#include <boost/format.hpp>
#include <resophonic/kamasu/config.hpp>

#define LOG_TRACE 0
#define LOG_DEBUG 1
#define LOG_INFO  2
#define LOG_WARN  3
#define LOG_ERROR 4
#define LOG_FATAL 5

#ifndef I3_PRINTF_LOGGING_LEVEL
#if RESOPHONIC_KAMASU_DEBUG
#define I3_PRINTF_LOGGING_LEVEL LOG_TRACE
#else
#define I3_PRINTF_LOGGING_LEVEL LOG_INFO
#endif
#endif

namespace resophonic {
  namespace kamasu {

    std::ofstream& ofs();

  }
}

// implmentation macro of macros visible to user.
#define LOG_IMPL(LEVEL, ufmt, ...)					\
  resophonic::kamasu::ofs() << boost::format("%s:%d " ufmt "\n") % __FILE__ % __LINE__ % __VA_ARGS__, resophonic::kamasu::ofs().flush()
  
#if I3_PRINTF_LOGGING_LEVEL <= LOG_TRACE
#define log_trace(format, ...) LOG_IMPL(LOG_TRACE, format, ##__VA_ARGS__)
#else
#define log_trace(format, ...) 
#endif

#if I3_PRINTF_LOGGING_LEVEL <= LOG_DEBUG
#define log_debug(format, ...) LOG_IMPL(LOG_DEBUG, format, ##__VA_ARGS__)
#else
#define log_debug(format, ...) 
#endif

#if I3_PRINTF_LOGGING_LEVEL <= LOG_INFO
#define log_info(format, ...) LOG_IMPL(LOG_INFO, format, ##__VA_ARGS__)
#else
#define log_info(format, ...) 
#endif

#if I3_PRINTF_LOGGING_LEVEL <= LOG_WARN
#define log_warn(format, ...) LOG_IMPL(LOG_WARN, format, ##__VA_ARGS__)
#else
#define log_warn(format, ...) 
#endif

#if I3_PRINTF_LOGGING_LEVEL <= LOG_ERROR
#define log_error(format, ...) LOG_IMPL(LOG_ERROR, format, ##__VA_ARGS__)
#else
#define log_error(format, ...) 
#endif

#define log_fatal(format, ...) LOG_IMPL(LOG_FATAL, format, ##__VA_ARGS__), throw std::runtime_error("log_fatal")

#endif 
