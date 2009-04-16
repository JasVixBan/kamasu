#include <komrade/host_vector.h>
#include <komrade/device_vector.h>
#include <komrade/generate.h>
#include <komrade/sort.h>
#include <cstdlib>

int main(void)
{
  unsigned n = 50000000;

  // generate random data on the host
  komrade::host_vector<float> h_vec(n);
  std::cout << "start generate\n";
  komrade::generate(h_vec.begin(), h_vec.end(), rand);
  std::cout << "done generate\n";

  //for (int i=0; i<n; i++)
  //    std::cout << h_vec[i] << "\n";
  // transfer to device
  komrade::device_vector<float> d_vec = h_vec;

  // sort on device
  std::cout << "start sort\n";
  komrade::sort(d_vec.begin(), d_vec.end());
  std::cout << "done sort\n";

  h_vec = d_vec;

  std::cout << "start generate\n";
  komrade::generate(h_vec.begin(), h_vec.end(), rand);
  std::cout << "done generate\n";
  std::cout << "start hostsort\n";
  std::sort(h_vec.begin(), h_vec.end());
  std::cout << "end hostsort\n";

  //  for (int i=0; i<n; i++)
  //    std::cout << sorted[i] << "\n";

  return 0;
}
