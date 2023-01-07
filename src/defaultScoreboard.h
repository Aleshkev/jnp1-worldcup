#ifndef DEFAULT_SCOREBOARD_H
#define DEFAULT_SCOREBOARD_H

#include "worldcup.h"

// Domyślna tablica, nie robi nic.
class DefaultScoreboard : public ScoreBoard {
  // Wywoływane, aby zasygnalizować początek rundy.
  void onRound(unsigned int roundNo) override {
  }

  // Wywoływane po skończeniu kolejki danego gracza, aby przekazać informacje o
  // aktualnym stanie gracza.
  void onTurn(std::string const &playerName, std::string const &playerStatus,
              std::string const &squareName, unsigned int money) override {
  }

  // Wywoływane, aby zasygnalizować zwycięstwo danego gracza.
  void onWin(std::string const &playerName) override {
  }
};

#endif