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

  uint64_t kamasu_wall_ms, cpu_wall_ms; 

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

  void run()
  {
    start();
    derived().main();
    stop();
    double user = (stop_rusage.ru_utime.tv_sec - start_rusage.ru_utime.tv_sec);
    user += double(stop_rusage.ru_utime.tv_usec - start_rusage.ru_utime.tv_usec) / 10e+06;

    double sys = (stop_rusage.ru_stime.tv_sec - start_rusage.ru_stime.tv_sec);
    sys += double(stop_rusage.ru_stime.tv_usec - start_rusage.ru_stime.tv_usec) / 10e+06;

    double wall = (endtime.tv_sec - starttime.tv_sec);
    wall += double (endtime.tv_nsec - starttime.tv_nsec) / 10e+09;

    double full = (fullendtime.tv_sec - fullstarttime.tv_sec);
    full += double (fullendtime.tv_nsec - fullstarttime.tv_nsec) / 10e+09;

    std::cerr << boost::format("%10s %10s %10s %10s\n") % "user" % "sys" % "wall" % "full";
    std::cout << boost::format("%10f %10f %10f %10f\n") % user % sys % wall % full;
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
int main_impl1(int argc, char** argv)
{
  if (argc < 1)
    {
      std::cout << "usage:\n" << argv[0] << " ";
      Test::usage();
    }
  unsigned i = boost::lexical_cast<unsigned>(argv[1]);
  std::cout << "Args: " << i << "\n";
  typename Selector::template impl<Test>::type mark(i);
  mark.run();
}

template <typename Test, typename Selector>
int main_impl2(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "usage:\n" << argv[0] << " ";
      Test::usage();
    }

  unsigned i = boost::lexical_cast<unsigned>(argv[1]);
  unsigned j = boost::lexical_cast<unsigned>(argv[2]);
  std::cout << "Args: " << i << " " << j << "\n";
  typename Selector::template impl<Test>::type mark(i,j);
  mark.run();
}

#define MAIN(N)							\
  int main(int argc, char** argv)				\
  {								\
    main_impl ## N <NAME, TYPE>(argc, argv);			\
  }




#endif
