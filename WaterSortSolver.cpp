/// Solver for those Water Sort puzzles
///
/// Algorithm:
///  - Depth first search of every single possible move
///  - Omit obviously stupid moves (i.e. moving a full vial to an empty vial)
///  - Keep a (hashed) history of all game states we've already seen
///  - Don't search game states we've already seen

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <functional>
#include <algorithm>
#include <set>

#include "Vial.h"
#include "GameState.h"

void printSolution(const std::vector<Move>& previousMoves)
{
  for (const auto& m : previousMoves) {
    m.debug();
  }
}

void solveIt(const std::vector<Move>& previousMoves, std::set<std::size_t>& historyHashes, const GameState& game)
{
  assert(!game.isSolved());

  auto hash = game.hash();
  historyHashes.insert(hash);

  std::vector<Move> nextMoves = game.allValidMoves();
  if (nextMoves.size() == 0) {
//    std::cout << "State " << hash << " has no valid moves\n";
    return;
  }

//  std::cout << previousMoves.size() << " moves deep. Assessing " << nextMoves.size() << " moves\n";



  for (const Move& move : nextMoves) {
//    std::cout << "From state " << hash << ", trying\n  ";
//    move.debug();

    GameState branch = game;
    branch.doMove(move);
//    branch.debug();

    if (historyHashes.count(branch.hash())) {
//      std::cout << "Already seen this\n";
      continue;
    }

    std::vector<Move> movesSoFar = previousMoves;
    movesSoFar.push_back(move);

    if (branch.isSolved()) {
      std::cout << "SOLVED!\n";
      printSolution(movesSoFar);
      exit(0);
    } else {
      solveIt(movesSoFar, historyHashes, branch);
    }
  }

//  std::cout << "<<Backtrack\n\n";
}


int main()
{
  const auto LIME = "lime";
  const auto GREEN = "green";
  const auto SKY = "skyblue";
  const auto BROWN = "brown";
  const auto YELLOW = "yellow";
  const auto KHAKI = "kak";
  const auto RED = "red";
  const auto ORANGE = "orange";
  const auto GREY = "grey";
  const auto PURPLE = "purple";
  const auto PINK = "pink";
  const auto BLUE = "blue";


  GameState startingPosition({
    Vial(4, { LIME, GREY, ORANGE, YELLOW }),
    Vial(4, { RED, PURPLE, KHAKI, SKY }),
    Vial(4, { KHAKI, PINK, LIME, PURPLE }),
    Vial(4, { YELLOW, PINK, RED, BROWN }),
    Vial(4, { KHAKI, BLUE, BROWN, PURPLE }),
    Vial(4, { KHAKI, GREY, PURPLE, YELLOW }),
    Vial(4, { ORANGE, GREY, SKY, GREEN }),
    Vial(4, { RED, GREEN, SKY, PINK }),
    Vial(4, { BLUE, BLUE, SKY, LIME }),
    Vial(4, { GREEN, BROWN, PINK, ORANGE }),
    Vial(4, { GREY, LIME, YELLOW, ORANGE }),
    Vial(4, { RED, BROWN, GREEN, BLUE }),
    Vial(4, { }),
    Vial(4, { })
  });

  startingPosition.debug();

  std::cout << "\n";

  std::set<std::size_t> history;
  solveIt({}, history, startingPosition);

}
