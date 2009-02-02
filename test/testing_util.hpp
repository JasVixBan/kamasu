#ifndef RESOPHONIC_KAMASU_TESTING_UTIL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_TESTING_UTIL_HPP_INCLUDED

#include <resophonic/kamasu/array.hpp>

resophonic::kamasu::array<float> make_4x5();

void check_unchanged_4x5(const resophonic::kamasu::array<float>& a);


resophonic::kamasu::array<float> make_1d(unsigned n);
resophonic::kamasu::array<float> make_3d(unsigned n);
void check_3d(const resophonic::kamasu::array<float>& a, unsigned n);
resophonic::kamasu::array<float> linspace(float start, float end, unsigned n_steps);

#endif
