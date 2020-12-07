#pragma once
#include <string>
#include <vector>
#include "Hashy.h"

using Colour = std::string;

class Vial {
public:
  Vial(int maxDepth, const std::vector<Colour>& coloursFromTop);

  bool canMoveTo(const Vial& other) const;

  bool isPointlessMove(const Vial& other) const;

  bool isSolved() const;

  std::size_t hash() const;

  /// @pre canMoveTo(other)
  void moveTo(Vial& other);

  void debug() const;

  bool isEmpty() const;

private:

  struct Lump {
    Colour colour;
    int depth;
  };

  /// @pre !isEmpty()
  const Colour& topColour() const;

  /// @pre !isEmpty()
  /// @post lump.depth > 0 && lump.depth <= max depth
  Lump top() const;

  int spacesRemaining() const;

  bool isAllSameColour() const;

  bool isFull() const;

  /// @pre !isEmpty()
  void popTop();

  /// Add a lump to the top.
  void pushLump(const Lump& lump);

  int m_depth;
  std::vector<Colour> m_coloursFromBottom;
};