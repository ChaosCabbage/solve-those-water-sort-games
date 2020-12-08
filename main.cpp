#include <iostream>
#include <thread>
#include <chrono>
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

void printSolution(const std::vector<Move>& solution)
{
  std::cout << "Solution:\n";
  for (const auto& m : solution) {
    m.print();
  }
}

void animateSolution(const std::vector<Move>& solution, GameState game)
{
  using namespace std::chrono_literals;
  system("CLS");

  for (const auto& m : solution) {
    game.debug();
    game.doMove(m);
    std::cout << std::flush;
    std::this_thread::sleep_for(400ms);
    system("CLS");
  }
  game.debug();

  std::this_thread::sleep_for(5s);

  std::cout << "\n\n";
}

int main(int argc, const char** argv)
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

  Solver solver(startingPosition);
  if (solver.solved()) {
    if (argc > 1 && strcmp(argv[1], "--animate") == 0) {
      animateSolution(solver.solution(), startingPosition);
    }
    printSolution(solver.solution());
    exit(0);
  }

  exit(1);
}
