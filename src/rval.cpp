#include <resophonic/kamasu/rval.hpp>
#include <resophonic/kamasu/holder.hpp>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    rval<T>::rval(boost::shared_ptr<holder<T> > hldr, unsigned index)
      : hldr_(hldr), index_(index)
    { }

    template <typename T>
    rval<T>&
    rval<T>::operator=(T value)
    {
      hldr_->set(index_, value);
      return *this;
    }

    template <typename T>
    rval<T>::operator T() const
    {
      return hldr_->get(index_);
    }
    
    template class rval<float>;
  }
}
