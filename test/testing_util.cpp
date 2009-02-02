/**
 *  $Id$
 *  
 *  Copyright (C) 2009
 *  Troy D. Straszheim  <troy@icecube.umd.edu>
 *  
 *  This file is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *  
 */

#include "testing_util.hpp"
#include "I3Test.h"

using resophonic::kamasu::array;

array<float> make_4x5()
{
  //
  //  4x5 matrix:
  //

  //   1   5   9  13  17
  //   2   6  10  14  18
  //   3   7  11  15  19
  //   4   8  12  16  20

  std::vector<std::size_t> shp;
  shp.push_back(4);
  shp.push_back(5);

  array<float> a(shp);

  unsigned counter = 0;
  for (int j=0; j<5; j++)
    for (int i=0; i<4; i++)
      {
	a(i,j) = ++counter;
	log_trace("a(%u, %u) == %f") % i % j % counter;
      }

  ENSURE_EQUAL(a.n_dims(), 2);
  ENSURE_EQUAL(a.dim(0), 4);
  ENSURE_EQUAL(a.dim(1), 5);
  ENSURE_EQUAL(a.linear_size(), 20);
 
  check_unchanged_4x5(a);

  return a;
}

void check_unchanged_4x5(const array<float>& a)
{
  unsigned counter = 0;
  for (int j=0; j<5; j++)
    for (int i=0; i<4; i++)
      {
	ENSURE_EQUAL(a(i,j), ++counter);
	log_trace("a(%u, %u) == %f") % i % j % counter;
      }
}


array<float> make_1d(unsigned n)
{
  //   0   1   2   3   4   5   ....

  std::vector<std::size_t> shp;
  shp.push_back(n);

  array<float> a(shp);
  ENSURE_EQUAL(a.linear_size(), n);
  ENSURE_EQUAL(a.n_dims(), 1);
  ENSURE_EQUAL(a.dim(0), n);

  a.show();

  for (int i=0; i<n; i++)
    a(i) = i;

  for (int i=0; i<n; i++)
    ENSURE_EQUAL(a(i), i);

  return a;
}


array<float> make_3d(unsigned n)
{
  std::vector<std::size_t> shp;
  shp.push_back(n);
  shp.push_back(n);
  shp.push_back(n);

  array<float> a(shp);
  ENSURE_EQUAL(a.linear_size(), n * n * n);
  ENSURE_EQUAL(a.n_dims(), 3);
  ENSURE_EQUAL(a.dim(0), n);
  ENSURE_EQUAL(a.dim(1), n);
  ENSURE_EQUAL(a.dim(2), n);

  a.show();

  unsigned counter = 0;

  for (int k=0; k<n; k++)
    for (int j=0; j<n; j++)
      for (int i=0; i<n; i++)
	a(i,j,k) = counter++;

  return a;
}

void check_3d(const array<float>&a, unsigned n)
{
  ENSURE_EQUAL(a.linear_size(), n * n * n);
  ENSURE_EQUAL(a.n_dims(), 3);
  ENSURE_EQUAL(a.dim(0), n);
  ENSURE_EQUAL(a.dim(1), n);
  ENSURE_EQUAL(a.dim(2), n);

  a.show();

  unsigned counter = 0;

  for (int k=0; k<n; k++)
    for (int j=0; j<n; j++)
      for (int i=0; i<n; i++)
	ENSURE_EQUAL(a(i,j,k), counter++);
}

array<float> linspace(float start, float end, unsigned n_steps)
{
  array<float> a(n_steps);
  for (unsigned n = 0; n < n_steps; n++)
    {
      float value = start + ((end-start)/(n_steps-1.0)) * (float)n;
      log_trace("linspace %u == %f") % n %  value;
      a(n) = value;
    }
  return a;
}

