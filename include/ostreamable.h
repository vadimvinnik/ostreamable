#include <memory>
#include <ostream>
#include <utility>

struct ostreamable_impl_base;
using ostreamable_impl_base_ptr = std::unique_ptr<ostreamable_impl_base>;

struct ostreamable_impl_base
{
  virtual ostreamable_impl_base_ptr clone() const = 0;
  virtual void to_stream(std::ostream &s) const = 0;

  virtual ~ostreamable_impl_base();
};

template <typename T>
class ostreamable_impl : public ostreamable_impl_base
{
public:
  template <typename U>
  explicit ostreamable_impl(U&& value) :
    value_{ std::forward<U>(value) }
  {}

  ostreamable_impl_base_ptr clone() const override
  {
    return std::make_unique<ostreamable_impl<T>>(value_);
  }

  void to_stream(std::ostream &s) const override
  {
    s << value_;
  }

private:
  T value_;
};

#define OSTREAMABLE_MAKE_IMPL(arg_)      \
  std::make_unique<ostreamable_impl<T>>( \
    std::forward<T>(arg_))

class ostreamable
{
public:
  ostreamable();

  template <typename T>
  ostreamable(T&& value) :
    impl_{ OSTREAMABLE_MAKE_IMPL(value) }
  {}

  ostreamable(ostreamable const& other);

  ostreamable(ostreamable&&);

  ostreamable& operator=(ostreamable const& other);

  ostreamable& operator=(ostreamable&&);

  template <typename T>
  ostreamable& operator=(T&& value)
  {
    impl_ = OSTREAMABLE_MAKE_IMPL(value);
    return *this;
  }

  void to_stream(std::ostream &s) const;

private:
  ostreamable_impl_base_ptr clone() const;

  ostreamable_impl_base_ptr impl_;
};

#undef OSTREAMABLE_MAKE_IMPL

std::ostream& operator<<(std::ostream &s, ostreamable const& x);

