#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include <vector>

#include "board.h"
#include "defaultScoreboard.h"
#include "player.h"
#include "worldcup.h"

// Wyjątki powinny dziedziczyć po std::exception.
class TooManyDiceException : public std::exception {};
class TooFewDiceException : public std::exception {};
class TooManyPlayersException : public std::exception {};
class TooFewPlayersException : public std::exception {};

class WorldCup2022 : public WorldCup {
 private:
  class GameEnds : public std::exception {};

  std::shared_ptr<ScoreBoard> currentScoreboard;

  std::shared_ptr<Board> board;

  std::vector<std::shared_ptr<Die>> dies;
  static constexpr size_t MIN_N_DICE = 2;
  static constexpr size_t MAX_N_DICE = 2;

  std::vector<std::shared_ptr<Player>> activePlayers;
  static constexpr size_t MIN_N_PLAYERS = 2;
  static constexpr size_t MAX_N_PLAYERS = 11;

 public:
  // WorldCup2022 ma mieć konstruktor bezparametrowy.
  WorldCup2022()
      : currentScoreboard(std::make_shared<DefaultScoreboard>()),
        board(std::make_shared<DefaultBoard>()) {
  }

  ~WorldCup2022() override = default;

  // Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji
  // (ale nie ma błędu).
  void addDie(std::shared_ptr<Die> die) override {
    if (die == nullptr) {
      return;
    }
    dies.push_back(die);
  }

  // Dodaje nowego gracza o podanej nazwie.
  void addPlayer(std::string const &name) override {
    activePlayers.push_back(std::make_shared<Player>(name));
    playerPositions.push_back(board->getStartPosition());
  }

  // Konfiguruje tablicę wyników. Domyślnie jest skonfigurowana tablica
  // wyników, która nic nie robi.
  void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) override {
    if (scoreboard == nullptr) {
      // TODO: tak powinno być??
      currentScoreboard = std::make_shared<DefaultScoreboard>();
    }
    currentScoreboard = scoreboard;
  }

  // Przeprowadza rozgrywkę co najwyżej podanej liczby rund (rozgrywka może
  // skończyć się wcześniej).
  // Jedna runda obejmuje po jednym ruchu każdego gracza.
  // Gracze ruszają się w kolejności, w której zostali dodani.
  // Na początku każdej rundy przekazywana jest informacja do tablicy wyników
  // o początku rundy (onRound), a na zakończenie tury gracza informacje
  // podsumowujące dla każdego gracza (onTurn).
  void play(unsigned int rounds) override {
    // Rzuca TooManyDiceException, jeśli jest zbyt dużo kostek.
    if (dies.size() > MAX_N_DICE) {
      throw TooManyDiceException();
    }
    // Rzuca TooFewDiceException, jeśli nie ma wystarczającej liczby kostek.
    if (dies.size() < MIN_N_DICE) {
      throw TooFewDiceException();
    }
    // Rzuca TooManyPlayersException, jeśli jest zbyt dużo graczy.
    if (activePlayers.size() > MAX_N_PLAYERS) {
      throw TooManyPlayersException();
    }
    // Rzuca TooFewPlayersException, jeśli liczba graczy nie pozwala na
    // rozpoczęcie gry.
    if (activePlayers.size() < MIN_N_PLAYERS) {
      throw TooFewPlayersException();
    }

    try {
      for (unsigned int i = 0; i < rounds; ++i) {
        doRound(i);
      }
    } catch (GameEnds &exception) {
      return;
    }
  }

 private:
  std::vector<size_t> playerPositions;

  void doRound(unsigned int roundNo) {
    currentScoreboard->onRound(roundNo);
    for (size_t playerID = 0; playerID < activePlayers.size(); ++playerID) {
      auto &player = activePlayers[playerID];
      if (player->getIsBancrupt()) {
        continue;
      }
      if (player->getTurnsToWait() > 0) {
        player->wait();
        continue;
      }
      size_t move = 0;
      for (auto &die : dies) {
        move += die->roll();
      }
      size_t targetPosition =
          (playerPositions[playerID] + move) % board->getNFields();

      while (!player->getIsBancrupt() && playerPositions[playerID] != targetPosition) {
      playerPositions[playerID] = (playerPositions[playerID]+ 1) % board->getNFields(); 
      if (playerPositions[playerID] != targetPosition) {
        board->getField(playerPositions[playerID]) ->onPlayerPassesThrough(player); }
      }
      if(!player->getIsBancrupt()) {
        board->getField(playerPositions[playerID])->onPlayerLands(player);
      }
    }

    // TODO

    for (size_t playerID = 0; playerID < activePlayers.size(); ++playerID) {
      auto &player = activePlayers[playerID];
      currentScoreboard->onTurn(player->getName(), player->getStatus(),
                                board->getField(playerPositions[playerID])->getName(),
                                player->getMoney());
    }
  }
};

#endif