#pragma once

#include <vector>
#include <set>

class GameState;
struct Move;

/// Solver for those Water Sort puzzles
///
/// Algorithm:
///  - Depth first search of every single possible move
///  - Omit obviously stupid moves (i.e. moving a full vial to an empty vial)
///  - Keep a (hashed) history of all game states we've already seen
///  - Don't search game states we've already seen
class Solver {
public:
  Solver(const GameState& startingPosition);
  
  bool solved() const;

  /// @pre solved()
  const std::vector<Move>& solution() const;

private:
  void solveIt(
    const std::vector<Move>& previousMoves,
    std::set<std::size_t>& historyHashes,
    const GameState& game
  );

  bool m_solved;
  std::vector<Move> m_solution;
};