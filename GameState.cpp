#include "GameState.h"
#include <iostream>
#include <assert.h>
#include "Vial.h"
#include "Move.h"

void Move::print() const {
  std::cout << "{ " << source + 1 << " -> " << destination + 1 << " }\n";
}

GameState::GameState(const std::vector<Vial>& vials)
  : m_vials(vials)
{
}

void GameState::doMove(const Move& move)
{
  assert(move.source < m_vials.size());
  assert(move.destination < m_vials.size());

  Vial& source = m_vials[move.source];
  Vial& dest = m_vials[move.destination];

  assert(source.canMoveTo(dest));
  source.moveTo(dest);
}

std::vector<Move> GameState::allValidMoves() const
{
  std::vector<Move> allMoves;

  for (std::size_t i = 0; i < m_vials.size(); ++i) {
    for (std::size_t j = 0; j < m_vials.size(); ++j) {
      if (i == j) continue;

      const Vial& vi = m_vials[i];
      const Vial& vj = m_vials[j];

      if (vi.canMoveTo(vj) && !vi.isPointlessMove(vj)) {
        allMoves.push_back({ i, j });
      }
    }
  }

  return allMoves;
}

bool GameState::isSolved() const
{
  for (const auto& vial : m_vials) {
    if (!vial.isSolved()) {
      return false;
    }
  }
  return true;
}

void GameState::debug() const
{
  std::cout << "{\n";
  for (std::size_t i = 0; i < m_vials.size(); ++i) {
    printf("%6d:", i + 1);
    m_vials[i].debug();
  }

  if (isSolved()) {
    std::cout << "  --- SOLVED! ---\n";
  } else {
    std::cout << "  -- UNSOLVED --\n";
  }
  std::cout << "  State #" << hash() << "\n";
  std::cout << "}\n";
}

std::size_t GameState::hash() const
{
  std::vector<std::size_t> hashes;
  hashes.reserve(m_vials.size());
  for (const auto& vial : m_vials) {
    hashes.push_back(vial.hash());
  }
  return hash_range(hashes);
}
