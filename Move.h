#pragma once

#include <cstddef>

using VialID = std::size_t;

struct Move {
  VialID source;
  VialID destination;

  void print() const;
};
