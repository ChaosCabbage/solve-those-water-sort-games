#include <iostream>
#include "GameState.h"
#include "Vial.h"
#include "Solver.h"
#include "Move.h"

#define fgBlack "\u001b[30m"
#define fgRed "\u001b[31m"
#define fgGreen "\u001b[32m"
#define fgYellow "\u001b[33m"
#define fgBlue "\u001b[34m"
#define fgMagenta "\u001b[35m"
#define fgCyan "\u001b[36m"
#define fgWhite "\u001b[37m"
#define fgBrightBlack "\u001b[30;1m"
#define fgBrightRed "\u001b[31;1m"
#define fgBrightGreen "\u001b[32;1m"
#define fgBrightYellow "\u001b[33;1m"
#define fgBrightBlue "\u001b[34;1m"
#define fgBrightMagenta "\u001b[35;1m"
#define fgBrightCyan "\u001b[36;1m"
#define fgBrightWhite "\u001b[37;1m"
#define colourReset "\u001b[0m"

#define Block(X) (X "\xDB\xDB" colourReset)

void printSolution(const std::vector<Move>& solution, GameState game)
{
  for (const auto& m : solution) {
    game.doMove(m);
    game.debug();
  }

  std::cout << "\n\nSolution:\n";
  for (const auto& m : solution) {
    m.print();
  }
}

int main()
{
  const auto LIME = Block(fgBrightGreen);
  const auto GREEN = Block(fgGreen);
  const auto SKY = Block(fgBrightBlue);
  const auto BROWN = Block(fgCyan);
  const auto YELLOW = Block(fgYellow);
  const auto KHAKI = Block(fgBrightMagenta);
  const auto RED = Block(fgRed);
  const auto ORANGE = Block(fgBrightYellow);
  const auto GREY = Block(fgBrightBlack);
  const auto PURPLE = Block(fgMagenta);
  const auto PINK = Block(fgBrightRed);
  const auto BLUE = Block(fgBlue);

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

  Solver solver(startingPosition);
  if (solver.solved()) {
    printSolution(solver.solution(), startingPosition);
    exit(0);
  }

  exit(1);
}
