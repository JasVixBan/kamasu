#ifndef RESOPHONIC_KAMSU_BENCHMARKS_HPP_INCLUDED
#define RESOPHONIC_KAMSU_BENCHMARKS_HPP_INCLUDED

#include <boost/format.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <boost/random.hpp>
#include <test/I3Test.h>

template <typename Derived>
struct benchmark
{
  timespec starttime, endtime, fullstarttime, fullendtime;
  rusage start_rusage, stop_rusage;

  Derived& derived() { return *(static_cast<Derived*>(this)); }

  boost::mt19937 rng;
  boost::uniform_real<float> uniform_distribution;
  boost::variate_generator<boost::mt19937, boost::uniform_real<float> > rand;

  benchmark() : uniform_distribution(-10, 10), rand(rng, uniform_distribution) { }

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

  int run()
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


template <typename Derived>
struct suite
{
  Derived& derived() { return *(static_cast<Derived*>(this)); }
  
  int main(int argc, const char** argv)
  {
    if (argc < 2)
      {
	std::cout << "usage:\n" << argv[0] << " ";
	Derived::usage();
	return 1;
      }

    unsigned i = boost::lexical_cast<unsigned>(argv[1]);
    unsigned j = boost::lexical_cast<unsigned>(argv[2]);

    std::cout << "kamasu ";
    for (int i=1; i<argc; i++)
      std::cout << argv[i] << " ";
    typename Derived::kamasu k(i,j);
    k.run();

    std::cout << "cpu ";
    for (int i=1; i<argc; i++)
      std::cout << argv[i] << " ";
    typename Derived::cpu c(i,j);
    c.run();
    
    try {
      k.verify(c.result);
    } catch (const I3Test::test_failure& failure) {

      std::cout << failure.to_string("FAIL");
      
    }
    return 0;
  }

};

#define MAIN(N)							\
  int main(int argc, const char** argv)				\
  {								\
    suite<NAME> s;  return s.main(argc, argv);			\
  }



#endif
