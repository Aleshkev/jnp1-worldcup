#ifndef FIELD_H
#define FIELD_H

#include <memory>
#include <utility>

#include "player.h"

// Jedno pole na planszy.
class Field {
 private:
  std::string name;

 public:
  explicit Field(std::string name) : name(std::move(name)) {
  }
  virtual ~Field() = default;

  // Wywoływane kiedy gracz przechodzi przez pole, nie zatrzymując się.
  virtual void onPlayerPassesThrough(std::shared_ptr<Player> player) {
  }

  // Wywoływane kiedy gracz ląduje na polu.
  virtual void onPlayerLands(std::shared_ptr<Player> player) {
  }

  [[nodiscard]] virtual const std::string &getName() const final {
    return name;
  }

  virtual bool canBeAStartPosition() {
    return false;
  }
};

#endif