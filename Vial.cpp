#include "Vial.h"
#include <assert.h>
#include <algorithm>
#include <iostream>

Vial::Vial(int maxDepth, const std::vector<Colour>& coloursFromTop)
  : m_depth(maxDepth)
{
  assert(m_depth > 0);
  assert(static_cast<int>(coloursFromTop.size()) <= m_depth);

  for (auto back = coloursFromTop.rbegin(); back != coloursFromTop.rend(); ++back) {
    m_coloursFromBottom.emplace_back(*back);
  }
}


bool Vial::canMoveTo(const Vial& other) const
{
  if (isEmpty()) return false;
  if (other.isEmpty()) return true;

  const Lump& myTop = top();
  const Lump& otherTop = other.top();

  if (myTop.colour != otherTop.colour) return false;
  if (myTop.depth > other.spacesRemaining()) return false;
  return true;
}

bool Vial::isPointlessMove(const Vial& other) const
{
  return 
    (this->isAllSameColour() && other.isEmpty()) || 
    (other.isAllSameColour() && this->isEmpty());
}

bool Vial::isAllSameColour() const
{
  if (isEmpty()) return false;

  return std::all_of(
    m_coloursFromBottom.begin(),
    m_coloursFromBottom.end(),
    [this](const Colour& c) { return c == topColour(); }
  );
}

bool Vial::isFull() const
{
  return m_coloursFromBottom.size() == m_depth;
}

std::size_t Vial::hash() const
{
  std::vector<std::size_t> hashes;
  hashes.reserve(m_coloursFromBottom.size());
  for (const auto& colour : m_coloursFromBottom) {
    hashes.push_back(std::hash<std::string>{}(colour));
  }
  return hash_range(hashes);
}

void Vial::moveTo(Vial& other)
{
  assert(canMoveTo(other));
  Lump myTop = top();
  popTop();
  other.pushLump(myTop);
}

void Vial::debug() const
{
  std::cout << "(";
  for (size_t i = 0; i < m_depth; ++i) {
    if (i < m_coloursFromBottom.size()) {
      std::cout << m_coloursFromBottom[i];
    } else {
      std::cout << "  ";
    }
  }
  std::cout << "]\n";
}

bool Vial::isEmpty() const
{
  return m_coloursFromBottom.empty();
}

const Colour& Vial::topColour() const
{
  assert(!isEmpty());
  return *m_coloursFromBottom.rbegin();
}

Vial::Lump Vial::top() const
{
  assert(!isEmpty());
  auto end = m_coloursFromBottom.rbegin();
  int depth = 0;

  while (
    end != m_coloursFromBottom.rend() &&
    *end == topColour()
    ) {
    ++end;
    ++depth;
  }

  assert(depth > 0);
  assert(depth <= m_depth);

  return { topColour(), depth };
}

int Vial::spacesRemaining() const
{
  return m_depth - m_coloursFromBottom.size();
}

bool Vial::isSolved() const
{
  return isEmpty() || (isAllSameColour() && isFull());
}

void Vial::popTop()
{
  assert(!isEmpty());
  int depth = top().depth;
  m_coloursFromBottom.resize(m_coloursFromBottom.size() - depth);
}

void Vial::pushLump(const Lump& lump)
{
  for (int i = 0; i < lump.depth; ++i) {
    m_coloursFromBottom.push_back(lump.colour);
  }
}
