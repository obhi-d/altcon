#pragma once

#include "detail/utils.hpp"
#include "type_traits.hpp"
#include "default_allocator.hpp"
#include <algorithm>


namespace acl
{ // namespace detail

/// @brief This class stores a list of reusable links, and allows for vector allocating objects
///        on a seperate container based on the links.
/// @tparam Ty 
/// @tparam SizeType 
template <typename Ty = std::void_t<>, typename SizeType = uint32_t>
class basic_link_registry
{
public:
  using size_type = SizeType;
  using link = link<Ty,size_type>;

  inline link emplace()
  {
    if (free_.empty())
      return link(max_size_++);

    auto ret = free_.back();
    free_.pop_back();
    return ret.revise();
  }

  inline void erase(link l)
  {
    free_.emplace_back(l);
  }

  template <typename Lambda>
  inline void for_each(Lambda&& l)
  {
    std::ranges::sort(free_);
    for (uint32_t i = 0, fi = 0; i < max_size_; ++i)
    {
      if (fi < free_.size() && free_[fi].as_index() == i)
        fi++;
      else
        l(i);
    }
  }
  
  template <typename Lambda>
  inline void for_each(Lambda&& l) const
  {
    auto copy = free_;
    std::ranges::sort(copy);
    for (uint32_t i = 0, fi = 0; i < max_size_; ++i)
    {
      if (fi < copy.size() && copy[fi].as_index() == i)
        fi++;
      else
        l(i);
    }
  }

  inline uint32_t max_size() const
  {
    return max_size_;
  }

private:

  vector<link> free_;
  uint32_t max_size_ = 1;
};

template <typename Ty = std::void_t<>>
using link_registry = basic_link_registry<Ty>;
}