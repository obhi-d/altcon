#pragma once

namespace acl::cfg
{
struct mutate_enums
{
  using mutate_enums_type = void;
};

#ifdef ACL_USE_LARGE_SIZE_TYPE
using container_size_type = uint64_t;
#else
using container_size_type = uint32_t;
#endif

} // namespace acl::cfg