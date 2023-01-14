#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "common.h"


class Player {
 private:
  static constexpr zdzislaw_t INITIAL_MONEY = 1000;
  const std::string name;
  zdzislaw_t money;  // Ile zdzisławów.
  bool isBancrupt;
  size_t turnsToWait;  // Ile tur jeszcze musi czekać bez grania.

 public:
  explicit Player(std::string name)
      : name(std::move(name)),
        money(INITIAL_MONEY),
        isBancrupt(false),
        turnsToWait(0) {
  }

  [[nodiscard]] const std::string &getName() const {
    return name;
  }

  [[nodiscard]] std::string getStatus() const {
    if (isBancrupt) {
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
    if(!isBancrupt) {
      money += amount;
    }
  }

  zdzislaw_t takeMoney(zdzislaw_t amount) {
    if (money < amount) {
      zdzislaw_t ret = money;
      money = 0;
      isBancrupt = true;
      return ret;
    }
    money -= amount;
    return amount;
  }

  [[nodiscard]] bool getIsBancrupt() const {
    return isBancrupt;
  }

  [[nodiscard]] size_t getTurnsToWait() const {
    return turnsToWait;
  }

  void setTurnsToWait(size_t newTurnsToWait) {
    turnsToWait = newTurnsToWait;
  }

  void wait() {
    turnsToWait--;
  }
};

#endif
