#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "common.h"

class Player {
 private:
  const std::string name;
  bool isBankrupt = false;
  static constexpr zdzislaw_t INITIAL_MONEY = 1000;
  zdzislaw_t money = INITIAL_MONEY;  // Ile zdzisławów.
  size_t position;                   // Pozycja na planszy.
  size_t turnsToWait = 0;            // Ile tur jeszcze musi czekać bez grania.

 public:
  explicit Player(std::string name, size_t position)
      : name(std::move(name)), position(position) {
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

  void giveMoney(zdzislaw_t amount) {
    if (!isBankrupt) {
      money += amount;
    } else {
      // CHECKIT
      throw std::runtime_error("Gracz jest bankrutem.");
    }
  }

  int takeMoney(zdzislaw_t amount) {
    if (money < amount || isBankrupt) {
      zdzislaw_t retVal = money;
      money = 0;
      isBankrupt = true;
      return retVal;
    }
    money -= amount;
    return amount;
  }

 public:
  [[nodiscard]] size_t getPosition() const {
    return position;
  }
  void setPosition(size_t newPosition) {
    position = newPosition;
  }
};

#endif
