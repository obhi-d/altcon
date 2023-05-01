
#pragma once
#include <compare>
#include <string>
#include <acl/type_traits.hpp>

template <typename IntTy>
inline IntTy range_rand(IntTy iBeg, IntTy iEnd)
{
  return static_cast<IntTy>(iBeg + (((double)rand() / (double)RAND_MAX) * (iEnd - iBeg)));
}

struct pod
{
  int a;
  int b;
  constexpr auto operator<=>(pod const&) const noexcept = default;
};


namespace acl
{
template <>
struct traits<std::string> : traits<>
{
  static constexpr std::uint32_t pool_size       = 2;
  static constexpr std::uint32_t index_pool_size = 2;
};

} // namespace acl


namespace helper
{
template <typename Cont>
static void insert(Cont& cont, std::uint32_t offset, std::uint32_t count)
{
  for (std::uint32_t i = 0; i < count; ++i)
  {
    cont.emplace(std::to_string(i + offset) + ".o");
  }
}

} // namespace helper


struct tracker
{
  int tracking = 0;
  char name     = 0;

  tracker() noexcept = default;
  tracker(char c) : name(c){}
};

struct destroy_tracker
{
  tracker* ref = nullptr;

  destroy_tracker() noexcept = default;
  destroy_tracker(tracker& r) : ref(&r)
  {
    r.tracking++;
  }

  destroy_tracker(destroy_tracker&& other) noexcept : ref(other.ref)
  {
    other.ref = nullptr;
  }
  destroy_tracker(destroy_tracker const& other) noexcept : ref(other.ref)
  {
    if (ref)
      ref->tracking++;
  }
  ~destroy_tracker()
  {
    if (ref)
    {
      ref->tracking--;
      ref = nullptr;
    }
  }
  destroy_tracker& operator=(destroy_tracker&& other) noexcept 
  {
    if (ref)
      ref->tracking--;
    ref       = other.ref;
    other.ref = nullptr;
    return *this;
  }
  destroy_tracker& operator=(destroy_tracker const& other) noexcept 
  {
    if (ref)
      ref->tracking--;
    ref = other.ref;
    if (ref)
      ref->tracking++;
    return *this;
  }

  constexpr auto operator<=>(destroy_tracker const&) const noexcept = default;
};

template <typename I>
std::string to_lstring(I i)
{
  return "a_very_long_string_to_avoid_soo" + std::to_string(i);
}