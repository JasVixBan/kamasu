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
      }

  ENSURE_EQUAL(a.nd(), 2u);
  ENSURE_EQUAL(a.dim(0), 4u);
  ENSURE_EQUAL(a.dim(1), 5u);
  ENSURE_EQUAL(a.linear_size(), 20u);
 
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
      }
}


array<float> make_1d(unsigned n)
{
  //   0   1   2   3   4   5   ....

  std::vector<std::size_t> shp;
  shp.push_back(n);

  array<float> a(shp);
  ENSURE_EQUAL(a.linear_size(), n);
  ENSURE_EQUAL(a.nd(), 1u);
  ENSURE_EQUAL(a.dim(0), n);

  a.show();

  for (unsigned i=0; i<n; i++)
    a(i) = i;

  for (unsigned i=0; i<n; i++)
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
  ENSURE_EQUAL(a.nd(), 3u);
  ENSURE_EQUAL(a.dim(0), n);
  ENSURE_EQUAL(a.dim(1), n);
  ENSURE_EQUAL(a.dim(2), n);

  a.show();

  unsigned counter = 0;

  for (unsigned k=0; k<n; k++)
    for (unsigned j=0; j<n; j++)
      for (unsigned i=0; i<n; i++)
	a(i,j,k) = counter++;

  return a;
}

void check_3d(const array<float>&a, unsigned n)
{
  ENSURE_EQUAL(a.linear_size(), n * n * n);
  ENSURE_EQUAL(a.nd(), 3u);
  ENSURE_EQUAL(a.dim(0), n);
  ENSURE_EQUAL(a.dim(1), n);
  ENSURE_EQUAL(a.dim(2), n);

  a.show();

  unsigned counter = 0;

  for (unsigned k=0; k<n; k++)
    for (unsigned j=0; j<n; j++)
      for (unsigned i=0; i<n; i++)
	ENSURE_EQUAL(a(i,j,k), counter++);
}

