#ifndef RESOPHONIC_KAMASU_CONFIG_HPP_INCLUDED
#define RESOPHONIC_KAMASU_CONFIG_HPP_INCLUDED

#define KAMASU_MAX_ARRAY_DIM 6

#if RESOPHONIC_KAMASU_DEBUG
#define RESOPHONIC_KAMASU_THROW(PRED, EX) do { if (PRED) throw EX; } while (false)
#define RESOPHONIC_CUDAMALLOC_DEBUG(X) X
#else
#define RESOPHONIC_KAMASU_THROW(PRED, EX)
#define RESOPHONIC_CUDAMALLOC_DEBUG(X) 
#endif

#endif

