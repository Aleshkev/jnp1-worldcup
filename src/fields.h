#ifndef FIELDS_H
#define FIELDS_H

#include <utility>

#include "common.h"
#include "field.h"

// TODO: wszystkie implementacje

// Są następujące typy pól z akcjami:

// początek sezonu – przy przejściu lub zatrzymaniu się na tym polu gracz
// dostaje 50 zdzisławów;
class BeginningOfTheSeasonField : public Field {
 private:
  const zdzislaw_t reward = 50;

 public:
  explicit BeginningOfTheSeasonField(const std::string& name) : Field(name) {
  }

 public:
  void onPlayerPassesThrough(std::shared_ptr<Player> player) override {
    player->giveMoney(reward);
  }
  void onPlayerLands(std::shared_ptr<Player> player) override {
    player->giveMoney(reward);
  }
  bool canBeAStartPosition() override {
    return true;
  }
};

class DayOffField : public Field {
 public:
  explicit DayOffField(const std::string& name) : Field(name) {
  }
};

// gol – przy zatrzymaniu na tym polu gracz dostaje premię za gola;
class GoalField : public Field {
 private:
  const zdzislaw_t bonus;

 public:
  explicit GoalField(std::string name, const zdzislaw_t bonus)
      : Field(std::move(name)), bonus(bonus) {
  }

  void onPlayerLands(std::shared_ptr<Player> player) override {
    player->addMoney(bonus);
  }
};

// rzut karny – przy zatrzymaniu się na tym polu gracz musi zapłacić Szczęsnemu
// za obronę rzutu karnego;
class PenaltyKickField : public Field {
 private:
  const zdzislaw_t penalty;

 public:
  explicit PenaltyKickField(std::string name, const zdzislaw_t penalty)
      : Field(std::move(name)), penalty(penalty) {
  }

  void onPlayerLands(std::shared_ptr<Player> player) override {
    player->takeMoney(penalty);
  }
};

// bukmacher – przy zatrzymaniu się na tym polu co trzeci gracz wygrywa zakład w
// zdzisławach, a pozostali przegrywają; seria zaczyna się od wygranego zakładu
// u bukmachera;
class BookmakerField : public Field {
  const unsigned int modulo = 3;
  const zdzislaw_t winnings;
  const zdzislaw_t losses;
  unsigned int counter;

 public:
  BookmakerField(std::string name, const zdzislaw_t winnings,
                 const zdzislaw_t losses)
      : Field(std::move(name)), winnings(winnings), losses(losses) {
  }

  void onPlayerLands(std::shared_ptr<Player> player) override {
    if (counter == 0) {
      player->giveMoney(winnings);
    } else {
      player->takeMoney(losses);
    }
    counter = (counter + 1) % modulo;
  }
};

// żółta kartka – gracz czeka określoną liczbę kolejek;
class YellowCardField : public Field {
  const size_t nTurnsToWait;

 public:
  explicit YellowCardField(std::string name, size_t n_turns_to_wait)
      : Field(std::move(name)), nTurnsToWait(n_turns_to_wait) {
  }

  void onPlayerLands(std::shared_ptr<Player> player) override {
    Field::onPlayerLands(player);
  }
};

// mecz – przy przejściu przez to pole gracz musi rozegrać mecz i uiścić opłatę
// za rozegranie; gracz, który zatrzyma się na tym polu, zgarnia wszystkie
// pobrane opłaty za rozegrane mecze pomnożone przez wagę meczu wg FIFA.
class MatchField : public Field {
 public:
  enum MatchWeight { FRIENDLY, FOR_POINTS, FINAL };

 private:
  zdiislaw_t currentBank = 0;
  const zdzislaw_t fee;
  const MatchWeight weight;

  [[nodiscard]] constexpr double getMatchWeight() const {
    switch (weight) {
      case FRIENDLY:
        return 1;
      case FOR_POINTS:
        return 2.5;
      case FINAL:
        return 4;
    }
  }

 public:
  explicit MatchField(std::string name, const MatchWeight weight,
                      const zdzislaw_t fee)
      : Field(std::move(name)), fee(fee), weight(weight) {
  }

 public:
  void onPlayerPassesThrough(std::shared_ptr<Player> player) override {
        player->takeMoney(fee);
        currentBank += fee;
  }
  void onPlayerLands(std::shared_ptr<Player> player) override {
        player->addMoney(currentBank * getMatchWeight());
        currentBank = 0;
  }
};

#endif