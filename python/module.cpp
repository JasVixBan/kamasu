#include <boost/python.hpp>
#include <boost/optional.hpp>
#include <boost/python/slice.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/index_range.hpp>
#include <iostream>

using namespace boost::python;
namespace ks = resophonic::kamasu;

// typedef ks::array<float> array_t;

namespace {

  bool is_none(const boost::python::object& obj)
  {
    return obj.ptr() == Py_None;
  }

  bool contains_slice(const tuple& t)
  {
    for (unsigned i=0; i<len(t); i++)
      {
	object obj = t[i];
	if (PySlice_Check(obj.ptr()))
	  return true;
      }
    return false;
  }

#define KS_REPEAT(MACRO, DATA) BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, MACRO, DATA)

  // #define KS_REPEAT(MACRO, DATA) MACRO(~, 3, DATA)

#define VA_GETITEM(Z,N,DATA)					\
  template <typename Array, typename T>				\
  object							\
  getitem_impl_##N(Array& arr,					\
		   BOOST_PP_ENUM_PARAMS(N, std::size_t Arg))	\
  {								\
    return object((T) arr(BOOST_PP_ENUM_PARAMS(N,Arg)));	\
  }

#define VA_SETITEM(Z, N, DATA)					\
  template <typename Array, typename T>				\
  void								\
  setitem_impl_##N(Array& arr,					\
		   BOOST_PP_ENUM_PARAMS(N, std::size_t Arg),	\
		   T value)					\
  {								\
    arr(BOOST_PP_ENUM_PARAMS(N, Arg)) = value;			\
  }

  KS_REPEAT(VA_GETITEM, ~);
  KS_REPEAT(VA_SETITEM, ~);

#define EXTRACT(Z, N, DATA) extract<int>(DATA[N])
#define GETITEM_CLAUSE(Z, N, DATA) case N: return getitem_impl_##N<Array,T>(arr, BOOST_PP_ENUM(N, EXTRACT, DATA)); break;
#define SETITEM_CLAUSE(Z, N, DATA) case N: setitem_impl_##N<Array,T>(arr, BOOST_PP_ENUM(N, EXTRACT, DATA), value); break;

  template <typename T>
  boost::optional<T> maybe_get(object o)
  {
    if (extract<T>(o).check())
      return boost::make_optional((T) extract<T>(o));
    else
      return boost::optional<T>();
  }

  resophonic::kamasu::index_range 
  make_indexrange(const slice& s)
  {
    typedef resophonic::kamasu::index_range ir_t;
    ir_t ir;

    bool none_start = is_none(s.start()), 
      none_stop = is_none(s.stop());

    boost::optional<int> optstep = maybe_get<int>(s.step());
    if (optstep)
      {
	log_trace("set stride %d",  *optstep);
	if (none_start && none_stop)
	  return ir_t(ks::_, ks::_, *optstep);
	else
	  ir.stride(*optstep);
      }

    boost::optional<int> start = maybe_get<int>(s.start());

    if (start)
      {
	log_trace("set start %d",  *start);
	ir.start(*start);
      }
    boost::optional<int> stop = maybe_get<int>(s.stop());
    if (stop)
      {
	log_trace("set stop %d",  *stop);
	ir.finish(*stop);
      }
    return ir;
  }

  template <typename Array>
  object
  slice_impl(Array& arr, tuple& t)
  {
    log_trace("%s",  __PRETTY_FUNCTION__);
    std::vector<resophonic::kamasu::index_range> irv;
    for (unsigned i=0; i<len(t); i++)
      {
	boost::python::object obj = t[i];
	boost::optional<boost::python::slice> sl = maybe_get<boost::python::slice>(obj);
	if (sl)
	  irv.push_back(make_indexrange(*sl));
	boost::optional<int> slint = maybe_get<int>(obj);
	if (slint)
	  irv.push_back(ks::index_range(*slint));

	if (!slint && !sl)
	  log_error("%s", "eh, neither slice nor int");
	BOOST_ASSERT(slint || sl);
	BOOST_ASSERT(!(slint && sl));
      }
    return object(arr.slice(irv));
  }

  template <typename Array, typename T>
  object 
  get_item(Array& arr, tuple& t)
  {
    log_trace("%s",  __PRETTY_FUNCTION__);
    if (contains_slice(t))
      return slice_impl(arr, t);
    switch(len(t)) {
      KS_REPEAT(GETITEM_CLAUSE, t);
    }
  };

  template <typename Array, typename T>
  object 
  get_slice(Array& arr, slice& s)
  {
    log_trace("%s",  __PRETTY_FUNCTION__);
    std::vector<resophonic::kamasu::index_range> irv;
    irv.push_back(make_indexrange(s));
    return object(arr.slice(irv));
  };

  template <typename Array, typename T>
  void 
  set_item(Array& arr, const tuple& t, T value)
  {
    //log_trace("%s") % __PRETTY_FUNCTION__;
    switch(len(t)) {
      KS_REPEAT(SETITEM_CLAUSE, t);
    }
  };


  template <typename Array, typename T>
  ks::array<T>
  op_mul(Array& arr, float value)
  {
    ks::array<T> res;
    res = arr * value;
    return res;
  }
}

#define SIZE_T(Z, N, DATA) std::size_t
#define INIT_DEF(Z, N, DATA) .def(init<BOOST_PP_ENUM(N, SIZE_T, ~)>())
  
template <typename RVal>
void
register_array(const char* name)
{
  typedef ks::array<float, RVal> array_t;

  class_<array_t>(name)
    .def("n_dims", &array_t::n_dims)
    .def("dim", &array_t::dim)
    .def("stride", &array_t::stride)
    .def("linear_size", &array_t::linear_size)
    KS_REPEAT(INIT_DEF, ~)

    .def("__getitem__", &get_slice<array_t, float>)
    .def("__getitem__", &get_item<array_t,float>)
    .def("__getitem__", &getitem_impl_1<array_t,float>)

    .def("__setitem__", &set_item<array_t,float>)
    .def("__setitem__", &setitem_impl_1<array_t,float>)
    .def("__mul__", &op_mul<array_t,float>)
    ;

}

BOOST_PYTHON_MODULE(kamasu)
{

  /*
    class_<array_t>("array")
    .def("n_dims", &array_t::n_dims)
    .def("dim", &array_t::dim)
    .def("stride", &array_t::stride)
    .def("linear_size", &array_t::linear_size)
    KS_REPEAT(INIT_DEF, ~)

    .def("__getitem__", &get_slice<float>)
    .def("__getitem__", &get_item<float>)
    .def("__getitem__", &getitem_impl_1<float>)

    .def("__setitem__", &set_item<float>)
    .def("__setitem__", &setitem_impl_1<float>)
    ;
  */
  register_array<boost::mpl::false_>("array");
  //  register_array<boost::mpl::true_>("array_rvalue");
}

// .def(init<std::size_t>())
// .def("__getitem__", (float (*)(array_t&, unsigned))&getitem<float>)
//    .def("__setitem__", (void  (*)(array_t&, unsigned, float))&setitem<float>)
