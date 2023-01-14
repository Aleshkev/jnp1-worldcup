#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "field.h"
#include "fields.h"

// Plansza, czyli cyklicznie ustawione pola.
class Board {
 private:
  std::vector<std::shared_ptr<Field>> fields;
  size_t startPosition;  // Gdzie każdy gracz rozpoczyna grę.


  explicit Board(const std::vector<std::shared_ptr<Field>>& fields)
      : fields(fields) {
      : fields(fields) {
    startPosition = 0;
    for (size_t i = 0; i < fields.size(); ++i) {
      if (fields.at(i)->canBeAStartPosition()) {
        startPosition = i;
        break;
      }
    }
  }

 public:
  [[nodiscard]] size_t getStartPosition() const {
    return startPosition;
  }

 public:
  virtual ~Board() = default;
  [[nodiscard]] virtual size_t getNFields() const final {
    return fields.size();
  }
  [[nodiscard]] virtual std::shared_ptr<Field> getField(
      size_t index) const final {
    return fields.at(index);
  }
};

// Domyślna plansza, czyli plansza zgodna z treścią zadania.
class DefaultBoard : public Board {
 public:
  DefaultBoard()
      : Board({
            // początek sezonu;
            std::make_shared<BeginningOfTheSeasonField>("początek sezonu"),

            // mecz z San Marino, szansa na wygraną, towarzyski, opłata za
            // rozegranie meczu to 160 zdzisławów;
            std::make_shared<MatchField>(
                "mecz z San Marino", MatchField::MatchWeight::FRIENDLY, 160),

            // dzień wolny od treningu; odpoczywasz i popijasz napoje wedle
            // wyboru, nic się nie dzieje, trener może Ci skoczyć;
            std::make_shared<DayOffField>("dzień wolny od treningu"),

            // mecz z Liechtensteinem, no tu już trudniej, towarzyski, opłata za
            // rozegranie meczu to 220 zdzisławów;
            std::make_shared<MatchField>("mecz z Liechtensteinem",
                                         MatchField::MatchWeight::FRIENDLY,
                                         220),

            // żółta kartka, skosiłeś brutalnie Lewandowskiego, dostajesz
            // cytrynę i czekasz trzy kolejki;
            std::make_shared<YellowCardField>("żółta kartka", 3),

            // mecz z Meksykiem, dawniej otwarcia, o punkty, opłata za
            // rozegranie meczu to 300 zdzisławów;
            std::make_shared<MatchField>(
                "mecz z Meksykiem", MatchField::MatchWeight::FOR_POINTS, 300),

            // mecz z Arabią Saudyjską, dawniej o wszystko, ale dziś o punkty,
            // opłata za rozegranie meczu to 280 zdzisławów;
            std::make_shared<MatchField>("mecz z Arabią Saudyjską",
                                         MatchField::MatchWeight::FOR_POINTS,
                                         280),

            // bukmacher, przy zatrzymaniu się co trzeci gracz wygrywa 100
            // zdzisławów za zakład, pozostali przegrywają 100 zdzisławów;
            std::make_shared<BookmakerField>("bukmacher", 100, 100),

            // mecz z Argentyną, zwykle mecz o honor, ale jest szansa na wygraną
            // 0:2, o punkty, opłata za rozegranie meczu 250 zdzisławów;
            std::make_shared<MatchField>(
                "mecz z Argentyną", MatchField::MatchWeight::FOR_POINTS, 250),

            // gol, po weryfikacji VAR sędzia uznaje gola i dostajesz premię 120
            // zdzisławów;
            std::make_shared<GoalField>("gol", 120),

            // mecz z Francją, 1/8 finału, i to by było na tyle, jednak finał,
            // opłata za rozegranie meczu 400 zdzisławów;
            std::make_shared<MatchField>("mecz z Francją",
                                         MatchField::MatchWeight::FINAL, 400),

            // rzut karny, tym razem skosiłeś Lewandowskiego w polu karnym,
            // płacisz Szczęsnemu za obronę karniaka 180 zdzisławów.
            std::make_shared<PenaltyKickField>("rzut karny", 180),
        }) {
  }
};

#endif