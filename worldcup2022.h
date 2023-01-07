#ifndef WORLDCUP2022_H
#define WORLDCUP2022_H

#include "worldcup.h"

class WorldCup2022 : public WorldCup {
 public:
  // WorldCup2022 ma mieć konstruktor bezparametrowy.
  WorldCup2022() {}

  ~WorldCup2022() override {}

  // Jeżeli argumentem jest pusty wskaźnik, to nie wykonuje żadnej operacji
  // (ale nie ma błędu).
  void addDie(std::shared_ptr<Die> die) override {
  }

  // Dodaje nowego gracza o podanej nazwie.
  void addPlayer(std::string const &name) override {
  }

  // Konfiguruje tablicę wyników. Domyślnie jest skonfigurowana tablica
  // wyników, która nic nie robi.
  void setScoreBoard(std::shared_ptr<ScoreBoard> scoreboard) override {
  }

  // Przeprowadza rozgrywkę co najwyżej podanej liczby rund (rozgrywka może
  // skończyć się wcześniej).
  // Jedna runda obejmuje po jednym ruchu każdego gracza.
  // Gracze ruszają się w kolejności, w której zostali dodani.
  // Na początku każdej rundy przekazywana jest informacja do tablicy wyników
  // o początku rundy (onRound), a na zakończenie tury gracza informacje
  // podsumowujące dla każdego gracza (onTurn).
  // Rzuca TooManyDiceException, jeśli jest zbyt dużo kostek.
  // Rzuca TooFewDiceException, jeśli nie ma wystarczającej liczby kostek.
  // Rzuca TooManyPlayersException, jeśli jest zbyt dużo graczy.
  // Rzuca TooFewPlayersException, jeśli liczba graczy nie pozwala na
  // rozpoczęcie gry.
  // Wyjątki powinny dziedziczyć po std::exception.
  void play(unsigned int rounds) override {
  }
};

#endif