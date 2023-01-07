#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "common.h"

class Player {
 private:
  const std::string name;
  zdzislaw_t money;  // Ile zdzisławów.
  static constexpr zdzislaw_t INITIAL_MONEY = 1000;
  size_t position;     // Pozycja na planszy.
  size_t turnsToWait;  // Ile tur jeszcze musi czekać bez grania.

 public:
  explicit Player(std::string name, size_t position)
      : name(std::move(name)),
        money(INITIAL_MONEY),
        position(position),
        turnsToWait(0) {
  }

  [[nodiscard]] const std::string &getName() const {
    return name;
  }

  [[nodiscard]] std::string getStatus() const {
    if (money < 0) {
      return "*** bankrut ***";  // TODO: to tak nie działa >:c
    } else if (turnsToWait > 0) {
      return std::string("*** czekanie: ") + std::to_string(turnsToWait) +
             "***";
    }
    return "w grze";
  }

  [[nodiscard]] zdzislaw_t getMoney() const {
    return money;
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
