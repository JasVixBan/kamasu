#ifndef RESOPHONIC_KAMASU_VIEW_PARAMS_HPP_INCLUDED
#define RESOPHONIC_KAMASU_VIEW_PARAMS_HPP_INCLUDED

namespace resophonic {
  namespace kamasu {
      struct view_params {
	typedef std::size_t offset_t;

	std::size_t dims[KAMASU_MAX_ARRAY_DIM];
	std::size_t factors[KAMASU_MAX_ARRAY_DIM];
	int strides[KAMASU_MAX_ARRAY_DIM];

	std::size_t linear_size;
	offset_t offset;
	unsigned nd;
      };
  }
}
#endif
