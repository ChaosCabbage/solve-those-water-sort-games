#pragma once
#include <vector>

/// A bit like boost::hash_combine
void hash_combine(std::size_t& seed, std::size_t value);

/// A bit like boost::hash_range
std::size_t hash_range(const std::vector<std::size_t>& hashes);