#include "Hashy.h"

/// A bit like boost::hash_combine
void hash_combine(std::size_t& seed, std::size_t value)
{
  seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

/// A bit like boost::hash_range
std::size_t hash_range(const std::vector<std::size_t>& hashes)
{
  std::size_t seed = 0;

  for (const std::size_t& hash : hashes) {
    hash_combine(seed, hash);
  }

  return seed;
}