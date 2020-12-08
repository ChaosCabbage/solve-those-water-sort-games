#include "Solver.h"

#include <assert.h>
#include "GameState.h"
#include "Move.h"

Solver::Solver(const GameState& startingPosition)
{
  std::set<std::size_t> history{ startingPosition.hash() };
  solveIt({}, history, startingPosition);
}

bool Solver::solved() const
{
  return m_solved;
}

const std::vector<Move>& Solver::solution() const
{
  assert(solved());
  return m_solution;
}

void Solver::solveIt(
  const std::vector<Move>& previousMoves, 
  std::set<std::size_t>& historyHashes, 
  const GameState& game
)
{
  assert(!game.isSolved());
  
  for (const Move& move : game.allValidMoves()) {
    if (m_solved) {
      return;
    }

    GameState branch = game;
    branch.doMove(move);

    auto branchHash = branch.hash();
    if (historyHashes.count(branchHash)) {
      continue;
    }
    historyHashes.insert(branchHash);

    std::vector<Move> movesSoFar = previousMoves;
    movesSoFar.push_back(move);

    if (branch.isSolved()) {
      m_solved = true;
      m_solution = movesSoFar;
      return;
    } 

    solveIt(movesSoFar, historyHashes, branch);
  }
}
