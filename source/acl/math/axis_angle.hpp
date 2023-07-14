#pragma once

#include "quad.hpp"
#include "vec3a.hpp"

namespace acl
{

template <typename scalar_t>
static inline axis_angle_t<scalar_t> make_axis_angle(quat_t<scalar_t> const& q) noexcept
{
  float angle = 2 * std::acos(q.w);
  auto  qf    = std::sqrt(1 - q.w * q.w);
  if (qf < k_const_epsilon_med)
  {
    return axis_angle_t<scalar_t>(1, 0, 0, 0);
  }
  qf = 1 / qf;
  return set_w(q * qf, angle);
}

template <typename scalar_t>
static inline axis_angle_t<scalar_t> make_axis_angle(vec3a_t<scalar_t> const& axis, float angle) noexcept
{
  return set_w(axis, angle);
}

template <typename scalar_t>
static inline vec3a_t<scalar_t> axis(axis_angle_t<scalar_t> const& q) noexcept
{
  return make_vec3a(q);
}

template <typename scalar_t>
static inline float angle(axis_angle_t<scalar_t> const& q) noexcept
{
  return w(q);
}

template <typename scalar_t>
static inline quad_t<scalar_t> vangle(axis_angle_t<scalar_t> const& v) noexcept
{
  if constexpr (has_sse && std::is_same_v<scalar_t, float>)
    return _mm_shuffle_ps(v.v, v.v, _MM_SHUFFLE(0, 0, 0, 3));
  else
    return {w(v), 0, 0, 0};
}

} // namespace acl
