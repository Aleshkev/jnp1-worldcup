#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "common.h"

class PlayerBankruptcy : public std::exception {
 public:
  PlayerBankruptcy() = default;
};

class Player {
 private:
  const std::string name;
  zdzislaw_t money;  // Ile zdzisławów.
  bool isBankrupt;
  static constexpr zdzislaw_t INITIAL_MONEY = 1000;
  size_t position;     // Pozycja na planszy.
  size_t turnsToWait;  // Ile tur jeszcze musi czekać bez grania.

 public:
  explicit Player(std::string name, size_t position)
      : name(std::move(name)),
        money(INITIAL_MONEY),
        isBankrupt(false),
        position(position),
        turnsToWait(0) {
  }

  [[nodiscard]] const std::string &getName() const {
    return name;
  }

  [[nodiscard]] std::string getStatus() const {
    if (isBankrupt) {
      return "*** bankrut ***";
    } else if (turnsToWait > 0) {
      return std::string("*** czekanie: ") + std::to_string(turnsToWait) +
             "***";
    }
    return "w grze";
  }

  [[nodiscard]] zdzislaw_t getMoney() const {
    return money;
  }

  void takeMoney(zdzislaw_t amount) {
    if (money < amount) {
      money = 0;
      isBankrupt = true;
      throw PlayerBankruptcy();
    }
    money -= amount;
  }

 public:
  [[nodiscard]] size_t getPosition() const {
    return position;
  }
  void setPosition(size_t newPosition) {
    position = newPosition;
  }
  [[nodiscard]] size_t getTurnsToWait() const {
    return turnsToWait;
  }
  void setTurnsToWait(size_t newTurnsToWait) {
    turnsToWait = newTurnsToWait;
  }
};

#endif
