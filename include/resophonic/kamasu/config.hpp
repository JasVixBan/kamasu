#ifndef RESOPHONIC_KAMASU_CONFIG_HPP_INCLUDED
#define RESOPHONIC_KAMASU_CONFIG_HPP_INCLUDED

#define KAMASU_MAX_ARRAY_DIM 6

#ifdef NDEBUG
#define RESOPHONIC_KAMASU_DEBUG 0
#else
#define RESOPHONIC_KAMASU_DEBUG 1
#endif

#if RESOPHONIC_KAMASU_DEBUG
#define RESOPHONIC_KAMASU_THROW(PRED, EX) do { if (PRED) throw EX; } while (false)
#else
#define RESOPHONIC_KAMASU_THROW(PRED, EX)
#endif

#define RESOPHONIC_KAMASU_UNARY_ARRAY_FUNCTIONS \
  (sqrt)(rsqrt)(cbrt)				\
  (exp)(exp2)(exp10)(expm1)			\
  (log)(log2)(log10)(log1p)			\
  (sin)(cos)(tan)				\
  (asin)(acos)(atan)				\
  (sinh)(cosh)(tanh)				\
  (asinh)(acosh)(atanh)				\
  (erf)(erfc)(lgamma)(tgamma)			\
  (logb)(ilogb)					\
  (trunc)(round)(rint)(nearbyint)		\
  (ceil)(floor)(lrint)(lround)(llrint)		\
  (llround)  

#endif

