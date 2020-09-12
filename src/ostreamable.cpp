#include "ostreamable.h"

ostreamable_impl_base::~ostreamable_impl_base() = default;

// ostreamable::

ostreamable::ostreamable() = default;

ostreamable::ostreamable(ostreamable const& other) :
  impl_{ other.impl_->clone() }
{}

ostreamable::ostreamable(ostreamable&&) = default;

ostreamable& ostreamable::operator=(ostreamable const& other)
{
  if (&other != this)
  {
    impl_ = other.impl_->clone();
  }

  return *this;
}

ostreamable& ostreamable::operator=(ostreamable&&) = default;

void ostreamable::to_stream(std::ostream &s) const
{
  if (impl_)
  {
    impl_->to_stream(s);
  }
}

std::ostream& operator<<(std::ostream &s, ostreamable const& x)
{
  x.to_stream(s);
  return s;
}

