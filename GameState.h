#pragma once
#include <vector>
#include "Vial.h"

struct Move;

class GameState {
public:
  GameState(const std::vector<Vial>&);

  void doMove(const Move& move);
  
  std::vector<Move> allValidMoves() const;
  bool isSolved() const;
  void debug() const;
  std::size_t hash() const;

private:
  std::vector<Vial> m_vials;
};
