#ifndef RESOPHONIC_KAMSU_BENCHMARKS_HPP_INCLUDED
#define RESOPHONIC_KAMSU_BENCHMARKS_HPP_INCLUDED

#include <boost/format.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

template <typename Derived>
struct benchmark
{
  timespec starttime, endtime, fullstarttime, fullendtime;
  rusage start_rusage, stop_rusage;

  Derived& derived() { return *(static_cast<Derived*>(this)); }

  void start()
  {
    clock_gettime(CLOCK_REALTIME, &fullstarttime);
    derived().start();
    clock_gettime(CLOCK_REALTIME, &starttime);
    getrusage(RUSAGE_SELF, &start_rusage);
  }

  void stop()
  {
    clock_gettime(CLOCK_REALTIME, &endtime);
    getrusage(RUSAGE_SELF, &stop_rusage);
    derived().stop();
    clock_gettime(CLOCK_REALTIME, &fullendtime);
  }

  int run(int argc, const char** argv)
  {
    start();
    derived().main();
    stop();
    double user = (stop_rusage.ru_utime.tv_sec - start_rusage.ru_utime.tv_sec);
    user += (double(stop_rusage.ru_utime.tv_usec) - double(start_rusage.ru_utime.tv_usec)) * 1.0e-06;

    double sys = (stop_rusage.ru_stime.tv_sec - start_rusage.ru_stime.tv_sec);
    sys += (double(stop_rusage.ru_stime.tv_usec) - double(start_rusage.ru_stime.tv_usec)) * 1.0e-06;

    double wall = (endtime.tv_sec - starttime.tv_sec);
    wall += double (endtime.tv_nsec - starttime.tv_nsec) * 1.0e-09;

    double full = fullendtime.tv_sec - fullstarttime.tv_sec;
    double full_ns = (fullendtime.tv_nsec - fullstarttime.tv_nsec) * 1.0e-09;
    full += full_ns;

    //    std::cout << "full: " << fullstarttime.tv_sec << " " << fullstarttime.tv_nsec << " ... " 
    //	      << fullendtime.tv_sec << " " << fullendtime.tv_nsec << "\n"
    //	      << "full_ns:" << full_ns << "\n";

    //std::cerr << boost::format("%10s %10s %10s %10s\n") % "user" % "sys" % "wall" % "full";
    for (int i=0; i<argc; i++)
      std::cout << argv[i] << " ";
    std::cout << boost::format("%10f %10f %10f %10f\n") % user % sys % wall % full;
    return 0;
  }
};

struct cpu 
{
  template <typename T>
  struct impl {
    typedef typename T::cpu type;
  };
};

struct kamasu 
{
  template <typename T>
  struct impl {
    typedef typename T::kamasu type;
  };
};

template <typename Test, typename Selector>
int main_impl1(int argc, const char** argv)
{
  if (argc < 1)
    {
      std::cout << "usage:\n" << argv[0] << " ";
      Test::usage();
      return 1;
    }
  unsigned i = boost::lexical_cast<unsigned>(argv[1]);
  typename Selector::template impl<Test>::type mark(i);
  return mark.run(argc, argv);
}

template <typename Test, typename Selector>
int main_impl2(int argc, const char** argv)
{
  if (argc < 2)
    {
      std::cout << "usage:\n" << argv[0] << " ";
      Test::usage();
      return 1;
    }

  unsigned i = boost::lexical_cast<unsigned>(argv[1]);
  unsigned j = boost::lexical_cast<unsigned>(argv[2]);
  typename Selector::template impl<Test>::type mark(i,j);
  return mark.run(argc, argv);
}

#define MAIN(N)							\
  int main(int argc, const char** argv)				\
  {								\
    return main_impl ## N <NAME, TYPE>(argc, argv);		\
  }


#endif
